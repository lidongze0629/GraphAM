#include "graph/worker.h"

#include <dlfcn.h>
#include <string>
#include <regex>

#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string/classification.hpp"

#include "graph/flags.h"
#include "graph/utils.h"

namespace graph {

void worker::Start() {

  InitTimers();

  StartTime(LoadGraphTime);
  LoadGraph();
  StopTime(LoadGraphTime);
  worker_helper_.set_time_load_graph(GetTimer(LoadGraphTime));

  LoadAlgoDynamicLib();

  StartTime(RunAlgorithmTime); // this time include write result file
  Query();
  StopTime(RunAlgorithmTime);
  worker_helper_.set_time_run_algorithm(GetTimer(RunAlgorithmTime));
}

void worker::LoadGraph() {
  graph_spec_.SetProperty("vertex_file", FLAGS_vfile);
  graph_spec_.SetProperty("edge_file", FLAGS_efile);
  graph_spec_.SetProperty("load_strategy", "EVformat");
  graph_spec_.SetProperty("algoDynamicLib", FLAGS_algo_dynamic_lib);
  graph_spec_.SetProperty("query", FLAGS_query);

  fragment_loader_ = FragmentLoaderFactory::CreateFragmentLoader(graph_spec_);
  fragment_loader_->LoadFragment(fragment_, graph_spec_);
  LOG(INFO) << "worker finished loading graph...";
}

void worker::LoadAlgoDynamicLib() {
  // TODO ADD EXCEPTION
  void *dynamic_application = dlopen(graph_spec_.algo_dynamic_lib().c_str(), RTLD_LAZY);

  if (!dynamic_application) {
    LOG(ERROR) << "load algo dynamic lib error: " << dlerror();
  }

  // reset error
  dlerror();

  create_t *create_app = reinterpret_cast<create_t *>(dlsym(dynamic_application, "Create"));

  const char *dlsym_error = dlerror();

  if (dlsym_error) {
    LOG(ERROR) << "load algo dynamic lib error: " << dlsym_error;
  }

  dlsym_error = dlerror();
  if (dlsym_error) {
    LOG(ERROR) << "load algo dynamic lib error: " << dlsym_error;
  }

  // create an instance of the class
  app_ = unique_ptr<IApp>(create_app());
}

void worker::Query() {
  Vector<String> query;
  ParseQueryString(graph_spec_.query(), query);

  {
    // init presult_on_vertex_
    vid_t tvnum = fragment_->GetVerticesNum();
    fragment_->init_presult_on_vertex(tvnum);
  }

  {
    app_->ExecAlgorithm(fragment_, query);
    LOG(INFO) << "Exec algorithm successful!";
  }

  {
    //todo: Reasonable output parse
    app_->WriteToFileResult(fragment_, FLAGS_output, query);
  }
}

void worker::Finalize() {
  worker_helper_.PrintSummary(worker_helper_);
}

void worker::ParseQueryString(const String &query_str, Vector<String> &query) {
  std::smatch matches;
  if (std::regex_match(query_str, matches, std::regex(RegexQuery))) {
    String query_info = matches[1].str();
    worker_helper_.set_queru_info_(query_info);

    Vector<String> segments;
    ::boost::split(segments, query_info, ::boost::is_any_of("\t\n\r "), boost::token_compress_on);
    for (auto q : segments) {
      query.push_back(q);
    }
  }else {
    LOG(ERROR) << "Regex Match Failed";
  }
}
}  // namespace graph
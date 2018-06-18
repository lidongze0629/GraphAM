#include "graph/worker.h"

#include <dlfcn.h>
#include <regex>
#include <string>

#include "boost/algorithm/string/classification.hpp"
#include "boost/algorithm/string/split.hpp"

#include "graph/flags.h"
#include "graph/utils.h"

namespace graph {

void worker::Start() {
  InitTimers();

  distributor_.Init(this);
  distributor_.ParseAndRunAlgorithmFromFile(FLAGS_command_file);

  /*StartTime(RunAlgorithmTime); // this time include write result file
  Query();
  StopTime(RunAlgorithmTime);
  worker_helper_.set_time_run_algorithm(GetTimer(RunAlgorithmTime));*/
}

void worker::LoadGraph() {
  StartTime(LoadGraphTime);
  fragment_loader_ = FragmentLoaderFactory::CreateFragmentLoader(graph_spec_);
  fragment_loader_->LoadFragment(fragment_, graph_spec_);
  StopTime(LoadGraphTime);
  worker_helper_.set_time_load_graph(GetTimer(LoadGraphTime));
  LOG(INFO) << "worker finished loading graph...";
}

void worker::LoadAlgoDynamicLib(const String &app_name) {
  // TODO ADD EXCEPTION
  void *dynamic_application =
      dlopen(graph_spec_.algo_dynamic_lib().c_str(), RTLD_LAZY);

  if (!dynamic_application) {
    LOG(ERROR) << "load algo dynamic lib error: " << dlerror();
  }

  // reset error
  dlerror();

  create_t *create_app =
      reinterpret_cast<create_t *>(dlsym(dynamic_application, "Create"));

  const char *dlsym_error = dlerror();

  if (dlsym_error) {
    LOG(ERROR) << "load algo dynamic lib error: " << dlsym_error;
  }

  dlsym_error = dlerror();
  if (dlsym_error) {
    LOG(ERROR) << "load algo dynamic lib error: " << dlsym_error;
  }

  // create an instance of the class
  unique_ptr<IApp> app_ptr = unique_ptr<IApp>(create_app());
  apps_.insert(std::make_pair(app_name, std::move(app_ptr)));
}

void worker::UnLoadAlgoDynamicLib(const String &app_name) {
  apps_.erase(app_name);
  LOG(INFO) << "unload application " << app_name << " successful.";
}

void worker::UnLoadGraph() {
  fragment_.reset();
  LOG(INFO) << "unload graph successful. ";
}

void worker::Query(const String &app_name, const String &prefix) {
  LOG(INFO) << app_name;
  Vector<String> query;
  ParseQueryString(graph_spec_.query(), query);

  {
    // init presult_on_vertex_
    vid_t tvnum = fragment_->GetVerticesNum();
    fragment_->init_presult_on_vertex(tvnum);
  }

  StartTime(RunAlgorithmTime);
  {
    apps_.at(app_name)->ExecAlgorithm(fragment_, this->ud_context(), query);
    LOG(INFO) << "Exec algorithm successful!";
  }
  StopTime(RunAlgorithmTime);
  worker_helper_.set_time_run_algorithm(GetTimer(RunAlgorithmTime));

  {
    // todo: Reasonable output parse
    apps_.at(app_name)->WriteToFileResult(fragment_, this->ud_context(), prefix,
                                          query);
  }
}

void worker::Finalize() { worker_helper_.PrintSummary(worker_helper_); }

void worker::ParseQueryString(const String &query_info, Vector<String> &query) {
  worker_helper_.set_query_info_(query_info);
  Vector<String> segments;
  ::boost::split(segments, query_info, ::boost::is_any_of("\t\n\r "),
                 boost::token_compress_on);
  for (auto q : segments) {
    query.push_back(q);
  }
}
}  // namespace graph
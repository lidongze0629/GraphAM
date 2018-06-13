#include "graph/worker.h"

#include <dlfcn.h>
#include <string>

#include "graph/flags.h"
#include "graph/utils.h"

namespace graph {

void worker::Start() {

  InitTimers();

  StartTime(LoadGraphTime);
  LoadGraph();
  StopTime(LoadGraphTime);
  LOG(INFO) << "Load Graph Time: " << GetTimer(LoadGraphTime) << "s";

  LoadAlgoDynamicLib();

  StartTime(RunAlgorithmTime); // this time include write result file
  Query();
  StopTime(RunAlgorithmTime);
  LOG(INFO) << "Run Algorithm Time: : " << GetTimer(RunAlgorithmTime) << "s";
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
    app_->WriteToFileResult(fragment_, graph_spec_.algo_dynamic_lib(), query);
  }

}

void worker::ParseQueryString(const String &query_str, Vector<String> &query) {
  // todo replace with boost split and regex
  // todo var location is not fianl
  int pos = query_str.find('(');
  if (pos != -1) {
    String location = query_str.substr(pos + 1, query_str.find(')') - 1);
    query.push_back(location);
  }
}
}  // namespace graph
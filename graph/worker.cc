#include "graph/worker.h"

#include "graph/flags.h"

namespace graph {

void worker::Start() {
  LoadGraph();
}

void worker::LoadGraph() {
  graph_spec_.SetProperty("vertex_file", FLAGS_vfile);
  graph_spec_.SetProperty("edge_file", FLAGS_efile);
  graph_spec_.SetProperty("load_strategy", "EVformat");

  fragment_loader_ = FragmentLoaderFactory::CreateFragmentLoader(graph_spec_);
  fragment_loader_->LoadFragment(fragment_, graph_spec_);
  LOG(INFO) << "worker finished loading graph...";
}

} // namespace graph
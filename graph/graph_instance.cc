#include "graph/graph_instance.h"

namespace graph {

void GraphInstance::InitWorker() {
  worker_ptr_ = unique_ptr<worker>(new worker());
  LOG(INFO) << "Init Worker Finished.";
}

void GraphInstance::RunWorker() {
  // ToDo: add try catch
  worker_ptr_->Start();
}

void GraphInstance::FinalizeWorker() { worker_ptr_->Finalize(); }
}  // namespace graph
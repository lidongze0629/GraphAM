#include "graph/graph_instance.h"

namespace graph {

void GraphInstance::InitWorker() {
  LOG(INFO) << "InitWorker";
  worker_ptr_ = unique_ptr<worker>(new worker());
}

void GraphInstance::RunWorker() {
  // ToDo: add try catch
  worker_ptr_->Start();
}

void GraphInstance::FinalizeWorker() {

}
} // namespace graph
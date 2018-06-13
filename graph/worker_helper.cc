#include "graph/worker_helper.h"

namespace graph {

void WorkerHelper::PrintSummary(const WorkerHelper &worker_helper) {
  LOG(INFO) << "-----------------------------------";
  LOG(INFO) << "query info: " << worker_helper.get_query_info_();
  LOG(INFO) << "load graph time: " << worker_helper.get_time_load_graph() << "s";
  LOG(INFO) << "run algorithm time: " << worker_helper.get_time_run_algorithm() << "s";
  LOG(INFO) << "-----------------------------------";
}
} // namespace graph
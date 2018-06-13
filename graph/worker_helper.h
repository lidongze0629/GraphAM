#ifndef GRAPH_WORKER_HELPER_H_
#define GRAPH_WORKER_HELPER_H_

#include "graph/utils.h"

namespace graph {

class WorkerHelper {
 public:
  WorkerHelper() {}

  ~WorkerHelper() {}

  inline void set_time_load_graph(const double t) { time_load_graph_ = t; }

  inline void set_time_run_algorithm(const double t) { time_run_algorithm_ = t; }

  inline void set_queru_info_(const String q) { query_info_ = q; }

  inline double get_time_load_graph() const { return time_load_graph_; }

  inline double get_time_run_algorithm() const { return time_run_algorithm_; }

  inline String get_query_info_() const { return query_info_; }

  void PrintSummary(const WorkerHelper &worker_helper);

 private:
  double time_load_graph_;
  double time_run_algorithm_;
  String query_info_;
};
}
#endif // GRAPH_WORKER_HELPER_H_
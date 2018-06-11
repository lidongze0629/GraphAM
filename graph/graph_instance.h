#ifndef GRAPH_GRAPH_INSTANCE_H_
#define GRAPH_GRAPH_INSTANCE_H_

#include <memory>

#include "graph/utils.h"
#include "graph/worker.h"

namespace graph {

class GraphInstance {
 public:
  /** Init worker
   *
   *  now just init worker, do nothing
   */
  void InitWorker();

  /** Run worker
   *
   *  load data, init graph architecture and run algorithm
   */
  void RunWorker();

  /** Finalize worker
   *
   *  output the result
   */
  void FinalizeWorker();

 private:
  unique_ptr<worker> worker_ptr_;
};
}  // namespace graph

#endif  // GRAPH_GRAPH_INSTANCE_H_
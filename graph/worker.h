#ifndef GRAPH_WORKER_H_
#define GRAPH_WORKER_H_

#include <memory>

#include "graph/fragment/fragment_loader_factory.h"
#include "graph/fragment/i_fragment_loader.h"
#include "graph/graph_spec.h"
#include "graph/utils.h"

namespace graph {

class worker {
 public:
  /** Default constructor */
  worker() {}

  /** Default destructor */
  ~worker() {}

  void LoadGraph();

  void Start();

 private:
  GraphSpec graph_spec_;
  unique_ptr<IFragmentLoader> fragment_loader_;
  unique_ptr<IFragment> fragment_;
};

}  // namespace graph

#endif  // GRAPH_WORKER_H_
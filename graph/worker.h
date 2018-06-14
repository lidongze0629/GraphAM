#ifndef GRAPH_WORKER_H_
#define GRAPH_WORKER_H_

#include <memory>

#include "graph/worker_helper.h"
#include "graph/app/i_app.h"
#include "graph/app/i_ud_context.h"
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

  void LoadAlgoDynamicLib();

  void Start();

  void Query();

  void Finalize();

  void ParseQueryString(const String &query_str, Vector<String> &query);

  inline shared_ptr<IUDContext> &ud_context() { return ud_contexts; }

 private:
  GraphSpec graph_spec_;
  unique_ptr<IFragmentLoader> fragment_loader_;
  unique_ptr<IFragment> fragment_;

  shared_ptr<IUDContext> ud_contexts;

  unique_ptr<IApp> app_;

  WorkerHelper worker_helper_;
};

}  // namespace graph

#endif  // GRAPH_WORKER_H_
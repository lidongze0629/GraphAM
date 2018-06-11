#ifndef GRAPH_FRAGMENT_I_FRAGMENT_LOADER_H_
#define GRAPH_FRAGMENT_I_FRAGMENT_LOADER_H_

#include "graph/fragment/i_fragment.h"
#include "graph/graph_spec.h"
#include "graph/utils.h"
namespace graph {

class IFragmentLoader {
 public:
  virtual void LoadFragment(unique_ptr<IFragment> &fragment,
                            const GraphSpec &graph_spec) = 0;
};
}  // namespace graph
#endif  // GRAPH_FRAGMENT_I_FRAGMENT_LOADER_H_
#ifndef GRAPH_FRAGMENT_EV_FRAGMENT_LOADER_H_
#define GRAPH_FRAGMENT_EV_FRAGMENT_LOADER_H_

#include "graph/fragment/i_fragment_loader.h"
#include "graph/utils.h"

namespace graph {
class EVFragmentLoader : public IFragmentLoader {

 public:
  /** Default Constructor .*/
  EVFragmentLoader() {}

  void LoadFragment(unique_ptr<IFragment> &fragment, const GraphSpec &graph_spec);

};
} // namespace graph
#endif // GRAPH_FRAGMENT_EV_FRAGMENT_LOADER_H_

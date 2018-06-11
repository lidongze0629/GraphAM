#ifndef GRAPH_FRAGMENT_EV_FRAGMENT_LOADER_H_
#define GRAPH_FRAGMENT_EV_FRAGMENT_LOADER_H_

#include "graph/fragment/edge.h"
#include "graph/fragment/i_fragment_loader.h"
#include "graph/fragment/vertex.h"
#include "graph/graph_spec.h"
#include "graph/utils.h"

namespace graph {
class EVFragmentLoader : public IFragmentLoader {
 public:
  /** Default Constructor .*/
  EVFragmentLoader() {}

  /** Constructor . */
  EVFragmentLoader(const GraphSpec &graph_spec) : graph_spec_(graph_spec) {}

  void LoadFragment(unique_ptr<IFragment> &fragment,
                    const GraphSpec &graph_spec);

  void LoadVfile(Vector<Vertex> &vertices, const String &vfile);

  void LoadEfile(Vector<Edge> &edges, const String &efile);

 private:
  GraphSpec graph_spec_;
};
}  // namespace graph
#endif  // GRAPH_FRAGMENT_EV_FRAGMENT_LOADER_H_

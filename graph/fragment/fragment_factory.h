#ifndef GRAPH_FRAGMENT_FRAGMENT_FACTORY_H_
#define GRAPH_FRAGMENT_FRAGMENT_FACTORY_H_

#include <memory>

#include "graph/fragment/immutable_edgecut_fragment.h"
#include "graph/utils.h"

namespace graph {
class FragmentFactory {
 public:
  static unique_ptr<IFragment> CreateFragment(const GraphSpec& graph_spec) {
    String loadStragety = graph_spec.loadStrategy();
    if (loadStragety == "EVformat") {
      return unique_ptr<IFragment>(new ImmutableEdgecutFragment(graph_spec));
    } else {
      LOG(FATAL) << "unSupport fragment loader format.";
      return nullptr;
    }
  }
};
}  // namespace graph

#endif  // GRAPH_FRAGMENT_FRAGMENT_FACTORY_H_
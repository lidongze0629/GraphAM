#ifndef GRAPH_FRAGMENT_FRAGMENT_LOADER_FACTORY_H_
#define GRAPH_FRAGMENT_FRAGMENT_LOADER_FACTORY_H_

#include <memory>

#include "graph/utils.h"
#include "graph/fragment/ev_fragment_loader.h"

namespace graph {

class FragmentLoaderFactory {
 public:
  static unique_ptr<IFragmentLoader> CreateFragmentLoader(const GraphSpec& graph_spec) {
    String loadStragety = graph_spec.loadStrategy();
    LOG(INFO) << loadStragety;
    if (loadStragety == "EVformat") {
      return unique_ptr<IFragmentLoader>(new EVFragmentLoader());
    } else {
      LOG(FATAL) << "unSupport fragment loader format.";
      return nullptr;
    }
  }
};
} // namespace graph
#endif // GRAPH_FRAGMENT_FRAGMENT_LOADER_FACTORY_H_
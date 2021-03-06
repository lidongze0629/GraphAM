#include "graph/graph_spec.h"

namespace graph {

void GraphSpec::SetProperty(const String &key, const String &value) {
  if (key == "vertex_file") {
    vertex_file_ = value;
  } else if (key == "edge_file") {
    edge_file_ = value;
  } else if (key == "load_strategy") {
    load_strategy_ = value;
  } else if (key == "algoDynamicLib") {
    algo_dynamic_lib_ = value;
  } else if (key == "query") {
    query_ = value;
  } else if (key == "graph_name") {
    graph_name_ = value;
  } else {
    LOG(ERROR) << "unsupport key_value pair.";
  }
}

}  // namespace graph
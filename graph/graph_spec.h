#ifndef GRAPH_GRAPH_SPEC_H_
#define GRAPH_GRAPH_SPEC_H_

#include "graph/utils.h"

namespace graph {

class GraphSpec {
 public:
  /** Default constructor .*/
  GraphSpec() {
    edge_file_ = "";
    vertex_file_ = "";
    load_strategy_ = "";
  }

  /** Constructor.
   *
   * @param loadStrategy the format of file to load graph.
   * @param vertex_file the location of vertex file.
   * @param edge_file he location of edge file.
   */
  GraphSpec(String loadStrategy, String vertex_file, String edge_file)
      : vertex_file_(vertex_file),
        edge_file_(edge_file),
        load_strategy_(loadStrategy) {}

  /** Default destructor. */
  ~GraphSpec() {}

  void SetProperty(const String &key, const String &value);

  inline const String &vertex_file() const { return vertex_file_; }

  inline const String &edge_file() const { return edge_file_; }

  inline const String &loadStrategy() const { return load_strategy_; }

 private:
  String vertex_file_;
  String edge_file_;
  String load_strategy_;  // ADJ or EVR SNAP
};
}  // namespace graph

#endif  // GRAPH_GRAPH_SPEC_H_
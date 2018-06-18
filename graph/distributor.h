#ifndef GRAPH_DIRTRIBUTOR_H_
#define GRAPH_DIRTRIBUTOR_H_

#include <vector>

#include "graph/utils.h"

namespace graph {

class worker;

#define LINESIZE 65536

class Distributor {
 public:
  Distributor() {}

  ~Distributor() { worker_ptr_ = nullptr; }

  void Init(worker *worker);

  void ParseAndRunAlgorithmFromFile(const String &command_file);

  void RunBatchFile(const String &line);

 private:
  worker *worker_ptr_;

  char buff[LINESIZE];

  Set<String> load_graph_vertexs_;
  Set<String> load_graph_edges_;
  Set<String> load_algorithms_;

  const String RegexLoadVertexFile =
      R"regex(([^\s]*)\s*=\s*loadvfile\(\"([^\"]*)\"\))regex";
  const String RegexLoadEdgeFile =
      R"regex(([^\s]*)\s*=\s*loadefile\(\"([^\"]*)\"\))regex";
  const String RegexLoadStragety =
      R"regex(([^\s]*)\s*=\s*loadstrategy\(\"([^\"]*)\"\))regex";
  const String RegexLoadAlgorithm =
      R"regex(([^\s]*)\s*=\s*loadalgorithm\(\"([^\"]*)\"\))regex";
  const String RegexQuery = R"regex((.*)\.query\((.*)\))regex";
};

}  // namespace graph

#endif  // GRAPH_DIRTRIBUTOR_H_
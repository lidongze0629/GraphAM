#include "graph/flags.h"

DEFINE_string(vfile, "./graph_test/twitter.v", "graph vertex file");
DEFINE_string(efile, "./graph_test/twitter.e", "graph edge file");
DEFINE_string(output, "default_output_file", "result output file");
DEFINE_string(algo_dynamic_lib, "libapp_mst_prim.so",
              "algorithm dynamic library location");
DEFINE_string(query, "()", "algorithm query. eg: sssp source vertex");

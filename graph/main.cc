#include <iostream>

#include "graph/graph_instance.h"
#include "graph/utils.h"

using graph::GraphInstance;

int main(int argc, char *argv[]) {
  FLAGS_stderrthreshold = 0;
  graph::gflags::SetUsageMessage("Usage: ./graph [graph_opts]");
  graph::gflags::ParseCommandLineFlags(&argc, &argv, true);
  graph::gflags::ShutDownCommandLineFlags();

  google::InitGoogleLogging("GRAPH");

  LOG(INFO) << "Welcome to Graph Algorithm!";
  GraphInstance instance;
  instance.InitWorker();
  instance.RunWorker();

  google::ShutdownGoogleLogging();
}
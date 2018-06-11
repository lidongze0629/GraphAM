#include <iostream>

#include "graph/utils.h"

int main(int argc, char *argv[]) {

  FLAGS_stderrthreshold = 0;
  graph::gflags::SetUsageMessage("Usage: ./graph [graph_opts]");
  graph::gflags::ParseCommandLineFlags(&argc, &argv, true);
  graph::gflags::ShutDownCommandLineFlags();

  google::InitGoogleLogging("GRAPH");

  LOG(INFO) << "Welcome to Graph Algorithm!";

  google::ShutdownGoogleLogging();
}
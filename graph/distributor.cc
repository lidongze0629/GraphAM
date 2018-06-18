#include "graph/distributor.h"

#include <fstream>
#include <regex>

#include "boost/algorithm/string.hpp"
#include "graph/worker.h"

namespace graph {

void Distributor::Init(worker *worker) { worker_ptr_ = worker; }

void Distributor::ParseAndRunAlgorithmFromFile(const String &command_file) {
  // todo add try catch
  Vector<String> batch_file;

  FILE *fin = fopen(command_file.c_str(), "r");
  if (!fin) {
    LOG(INFO) << "file " << command_file << " open failed!";
  }

  while (fgets(buff, LINESIZE, fin) != NULL) {
    String line(buff);
    boost::trim(line);
    if (!line.empty() && line[0] != '#') {
      batch_file.push_back(line);
    }
  }
  fclose(fin);

  batch_file.push_back("exit");
  for (auto &line : batch_file) {
    RunBatchFile(line);
    if (line == "exit") break;
  }
}

void Distributor::RunBatchFile(const String &line) {
  // todo add try catch
  assert(worker_ptr_ != nullptr);
  std::smatch matches;
  if (std::regex_match(line, matches, std::regex(RegexLoadVertexFile))) {
    if (matches.size() == 3) {
      String vertex_file = matches[1];
      String vertex_path = matches[2];
      if (load_graph_vertexs_.find(vertex_file) != load_graph_vertexs_.end()) {
        LOG(ERROR) << "graph vertex file " << vertex_file
                   << " already exists. ";
      }
      worker_ptr_->graphSpec().SetProperty(
          "vertex_file", ParseWithEnvironmentVariable(vertex_path));
      load_graph_vertexs_.emplace(vertex_file);
    }
  } else if (std::regex_match(line, matches, std::regex(RegexLoadEdgeFile))) {
    if (matches.size() == 3) {
      String edge_file = matches[1];
      String edge_path = matches[2];
      if (load_graph_edges_.find(edge_file) != load_graph_edges_.end()) {
        LOG(ERROR) << "graph edge file " << edge_file << " already exists. ";
      }
      worker_ptr_->graphSpec().SetProperty(
          "edge_file", ParseWithEnvironmentVariable(edge_path));
      load_graph_edges_.emplace(edge_file);
    }
  } else if (std::regex_match(line, matches, std::regex(RegexLoadStragety))) {
    if (matches.size() == 3) {
      String loadStragety = matches[2];
      worker_ptr_->graphSpec().SetProperty("load_strategy", loadStragety);
      worker_ptr_->LoadGraph();
    }
  } else if (std::regex_match(line, matches, std::regex(RegexLoadAlgorithm))) {
    if (matches.size() == 3) {
      String algo_name = matches[1];
      String algo_location = matches[2];
      if (load_algorithms_.find(algo_name) != load_algorithms_.end()) {
        LOG(ERROR) << "Algorithm name " << algo_name << " already exists. ";
      }
      worker_ptr_->graphSpec().SetProperty(
          "algoDynamicLib", ParseWithEnvironmentVariable(algo_location));
      worker_ptr_->LoadAlgoDynamicLib(algo_name);
      load_algorithms_.emplace(algo_name);
    }
  } else if (std::regex_match(line, matches, std::regex(RegexQuery))) {
    String app_name = matches[1];
    String query_info = matches[2];
    String prefix = matches[3];
    worker_ptr_->graphSpec().SetProperty("query", query_info);
    worker_ptr_->Query(app_name, prefix);
  }
}

}  // namespace graph
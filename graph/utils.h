#ifndef GRAPH_UTIL_H_
#define GRAPH_UTIL_H_

#include <string>
#include <ctime>
#include <memory>

#include "glog/logging.h"

#include "graph/flags.h"

namespace graph {

#ifdef GFLAGS_NAMESPACE
namespace gflags = GFLAGS_NAMESPACE;
#else
namespace gflags = google;
#endif

typedef unsigned vid_t;

template <typename T>
using unique_ptr = std::unique_ptr<T>;

template <typename T>
using Vector = std::vector<T>;

typedef std::string String;

inline std::string GetResultFileName(const String &prefix) {
  std::string path;
  std::time_t t = std::time(0);

  auto pos = prefix.find('.');
  if (pos != 0) {
    path = prefix.substr(0, pos) + "-" + std::to_string(t);
  } else {
    path = "default_prefix-" + std::to_string(t);
  }
  return path;
}

}  // namespace graph

#endif  // GRAPH_UTIL_H_
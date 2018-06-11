#ifndef GRAPH_UTIL_H_
#define GRAPH_UTIL_H_

#include <memory>
#include <string.h>

#include "glog/logging.h"

#include "graph/flags.h"

namespace graph {

#ifdef GFLAGS_NAMESPACE
namespace gflags = GFLAGS_NAMESPACE;
#else
namespace gflags = google;
#endif

template <typename T>
using unique_ptr = std::unique_ptr<T>;

typedef std::string String;

} // namespace graph

#endif // GRAPH_UTIL_H_
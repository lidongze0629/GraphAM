#ifndef GRAPH_UTIL_H_
#define GRAPH_UTIL_H_

#include "glog/logging.h"

namespace graph {

#ifdef GFLAGS_NAMESPACE
namespace gflags = GFLAGS_NAMESPACE;
#else
namespace gflags = google;
#endif

}

#endif // GRAPH_UTIL_H_
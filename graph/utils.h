#ifndef GRAPH_UTIL_H_
#define GRAPH_UTIL_H_

#include <string>
#include <ctime>
#include <memory>
#include <sys/time.h>

#include "glog/logging.h"

#include "graph/flags.h"

namespace graph {

#ifdef GFLAGS_NAMESPACE
namespace gflags = GFLAGS_NAMESPACE;
#else
namespace gflags = google;
#endif

enum Timer {
  LoadGraphTime = 0,
  RunAlgorithmTime = 1,
};

typedef unsigned vid_t;

template <typename T>
using unique_ptr = std::unique_ptr<T>;

template <typename T>
using shared_ptr = std::shared_ptr<T>;

template <typename T>
using Vector = std::vector<T>;

typedef std::string String;

const String RegexQuery = R"regex(\((.*)\))regex";

inline std::string GetResultFileName(const String &prefix) {
  std::string path;
  std::time_t t = std::time(0);
  path = prefix + "_" + std::to_string(t);

  return path;
}

const int timer_number = 4; // currently, only 2 timer is available
static double timers[timer_number];
static double accumulate_time[timer_number];

inline double GetCurrentTime() {
  timeval t;
  gettimeofday(&t, 0);
  return static_cast<double>(t.tv_sec)
      + static_cast<double>(t.tv_usec) / 1000000;
}

inline void InitTimers() {
  for (int t = 0; t < timer_number; t++) {
    accumulate_time[t] = 0;
    timers[t] = 0;
  }
}

inline void StartTime(Timer i) {
  timers[i] = GetCurrentTime();
}

inline void StopTime(Timer i) {
  double t = GetCurrentTime();
  accumulate_time[i] = t - timers[i];
}

inline double GetTimer(Timer i) {
  return accumulate_time[i];
}

}  // namespace graph

#endif  // GRAPH_UTIL_H_
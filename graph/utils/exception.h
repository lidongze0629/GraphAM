#ifndef GRAPH_UTILS_EXCEPTION_H_
#define GRAPH_UTILS_EXCEPTION_H_

#include <exception>
#include <sstream>

#include "graph/utils.h"

namespace graph {

#define RAISE(msg)                       \
  \
{                                    \
    std::ostringstream oss;               \
    oss << "error: " << msg;              \
    throw(Exception(__FUNCTION__, __FILE__, __LINE__, oss.str())); \
  \
}
class Exception : public std::exception {
 public:
  Exception(const String &func, const String &file, const unsigned &line, const String description):
      func_(func), file_(file), line_(line), description_(description) {
  }

  ~Exception() throw() {}

  inline String display() {
    std::ostringstream detail;
    detail << description_ << " [ " << file_<< " in" << func_ << " at line " << line_ << " ]";
    return detail.str();
  }
 protected:
  String func_;
  String file_;
  unsigned line_;
  String description_;

};

} // namespace graph

#endif // GRAPH_UTILS_EXCEPTION_H_
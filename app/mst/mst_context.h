#ifndef APP_MST_MST_CONTEXT_H_
#define APP_MST_MST_CONTEXT_H_

#include <utility>
#include <vector>

#include "graph/app/i_ud_context.h"
#include "graph/fragment/edge.h"

using graph::IUDContext;
using graph::Edge;

class MSTContext : public IUDContext {
 public:
  std::vector<Edge> result;
};

#endif // APP_MST_MST_CONTEXT_H_

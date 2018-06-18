#ifndef APP_MST_MST_HELPER_H_
#define APP_MST_MST_HELPER_H_

#include <utility>
#include <vector>

#include "graph/app/i_app_helper.h"
#include "graph/fragment/edge.h"

using graph::IAppHelper;
using graph::Edge;

class MstHelper : public IAppHelper {
 public:
  std::vector<Edge> result;
};

#endif  // APP_MST_MST_HELPER_H_

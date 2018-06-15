#ifndef APP_WCC_WCC_HELPER_H_
#define APP_WCC_WCC_HELPER_H_

#include <utility>
#include <memory>
#include <vector>

#include "graph/app/i_app_helper.h"

using graph::IAppHelper;
using graph::Edge;

class WccHelper : public IAppHelper {
 public:
  std::vector<std::pair<unsigned, int32_t >> result;
};

#endif // APP_WCC_WCC_HELPER_H_

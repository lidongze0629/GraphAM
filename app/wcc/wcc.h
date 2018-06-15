#ifndef APP_WCC_WCC_H_
#define APP_WCC_WCC_H_

#include <memory>

#include "graph/app/i_app.h"

namespace graph {

class WCC : public IApp {
 public:
  WCC() {}
  ~WCC() {}

  void ExecAlgorithm(unique_ptr<IFragment> &fragment,
                     shared_ptr<IAppHelper> &app_helper_ptr,
                     const Vector<String> &query);

  void WriteToFileResult(unique_ptr<IFragment> &fragment,
                         shared_ptr<IAppHelper> &app_helper_ptr,
                         const String prefix, const Vector<String> &query);
};

extern "C" IApp *Create() {
  LOG(INFO) << "Create a instance of WCC.";
  return new WCC;
}
extern "C" void Destroy(IApp *p) {
  LOG(INFO) << "Destroy a instance of WCC.";
  delete p;
}

}  // namespace graph
#endif  // APP_WCC_WCC_H_

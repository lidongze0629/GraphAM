#ifndef APP_SSSP_SSSP_H_
#define APP_SSSP_SSSP_H_

#include <memory>

#include "graph/app/i_app.h"

namespace graph {

class SSSP : public IApp {
 public:
  SSSP() {}
  ~SSSP() {}

  void ExecAlgorithm(unique_ptr<IFragment> &fragment,
                     shared_ptr<IAppHelper> &app_helper_ptr,
                     const Vector<String> &query);

  void WriteToFileResult(unique_ptr<IFragment> &fragment,
                         shared_ptr<IAppHelper> &app_helper_ptr,
                         const String prefix, const Vector<String> &query);
};

extern "C" IApp *Create() {
  LOG(INFO) << "Create a instance of SSSP.";
  return new SSSP;
}
extern "C" void Destroy(IApp *p) {
  LOG(INFO) << "Destroy a instance of SSSP.";
  delete p;
}

}  // namespace graph
#endif  // APP_SSSP_SSSP_H_

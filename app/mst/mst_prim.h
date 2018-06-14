#ifndef APP_MST_MST_PRIM_H_
#define APP_MST_MST_PRIM_H_

#include <memory>

#include "graph/app/i_app.h"

namespace graph {

class PrimMST : public IApp {
 public:
  PrimMST() {}
  ~PrimMST() {}

  void ExecAlgorithm(unique_ptr<IFragment> &fragment, const Vector<String> &query);

  void WriteToFileResult(unique_ptr<IFragment> &fragment,
                         const String prefix, const Vector<String> &query);
};

extern "C" IApp *Create() {
  LOG(INFO) << "Create a instance of PrimMST.";
  return new PrimMST;
}
extern "C" void Destroy(IApp *p) {
  LOG(INFO) << "Destroy a instance of PrimMST.";
  delete p;
}

}  // namespace graph
#endif  // APP_MST_MST_PRIM_H_

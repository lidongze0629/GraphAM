#ifndef APP_BFS_BFS_H_
#define APP_BFS_BFS_H_

#include <memory>

#include "graph/app/i_app.h"

namespace graph {

class BFS : public IApp {
 public:
  BFS() {}
  ~BFS() {}

  void ExecAlgorithm(unique_ptr<IFragment> &fragment, const Vector<String> &query);

  void WriteToFileResult(unique_ptr<IFragment> &fragment,
                         const String prefix, const Vector<String> &query);
};

extern "C" IApp *Create() {
  LOG(INFO) << "Create a instance of BFS.";
  return new BFS;
}
extern "C" void Destroy(IApp *p) {
  LOG(INFO) << "Destroy a instance of BFS.";
  delete p;
}

}  // namespace graph
#endif  // APP_BFS_BFS_H_

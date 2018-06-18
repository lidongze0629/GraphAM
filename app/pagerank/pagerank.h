#ifndef APP_PAGRRANK_PAGERANK_H_
#define APP_PAGRRANK_PAGERANK_H_

#include <memory>

#include "graph/app/i_app.h"

namespace graph {

class PageRank : public IApp {
 public:
  PageRank() {}
  ~PageRank() {}

  void ExecAlgorithm(unique_ptr<IFragment> &fragment,
                     shared_ptr<IAppHelper> &app_helper_ptr,
                     const Vector<String> &query);

  void WriteToFileResult(unique_ptr<IFragment> &fragment,
                         shared_ptr<IAppHelper> &app_helper_ptr,
                         const String prefix, const Vector<String> &query);
};

extern "C" IApp *Create() {
  LOG(INFO) << "Create a instance of PageRank.";
  return new PageRank;
}
extern "C" void Destroy(IApp *p) {
  LOG(INFO) << "Destroy a instance of PageRank.";
  delete p;
}

}  // namespace graph
#endif  // APP_PAGRRANK_PAGERANK_H_
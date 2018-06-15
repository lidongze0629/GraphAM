#include "app/wcc/wcc.h"

#include <memory>
#include <fstream>
#include <unordered_set>
#include <queue>
#include <vector>
#include <iostream>

#include "graph/utils.h"
#include "app/wcc/wcc_helper.h"
#include "graph/fragment/immutable_edgecut_fragment.h"

namespace graph {

void WCC::ExecAlgorithm(unique_ptr<IFragment> &fragment,
                            shared_ptr<IAppHelper> &app_helper_ptr,
                            const Vector<String> &query) {
  // constraint component is the minimum of the vertex id

  ImmutableEdgecutFragment *frag = dynamic_cast<ImmutableEdgecutFragment *>(fragment.get());
  vid_t tvnum = frag->GetVerticesNum();

  app_helper_ptr = std::shared_ptr<IAppHelper>(new WccHelper());

  auto &rt = std::dynamic_pointer_cast<WccHelper>(app_helper_ptr)->result;

  std::priority_queue<std::pair<int32_t, vid_t >> heap;
  std::vector<bool> visited(tvnum, false);

  for (unsigned i = 0; i < tvnum; i++) {
    if(visited[i]) continue;

    heap.push(std::make_pair(-i, i));
    while (!heap.empty()) {
      vid_t u = heap.top().second;
      int32_t min_component = -(heap.top().first);

      heap.pop();
      if (visited[u]) continue;

      visited[u] = true;
      rt.push_back(std::make_pair(u, min_component));

      auto es = frag->GetOutgoingEdges(u);
      for (auto &iter : es) {
        vid_t v = iter.dst();
        heap.push(std::make_pair(-min_component, v));
      }

      auto es2 = frag->GetIncomingEdges(u);
      for (auto &iter : es2) {
        vid_t v = iter.src();
        heap.push(std::make_pair(-min_component, v));
      }
    }
  }
}

void WCC::WriteToFileResult(unique_ptr<IFragment> &fragment,
                                shared_ptr<IAppHelper> &app_helper_ptr,
                                const String prefix, const Vector<String> &query) {
  std::string path = GetResultFileName(prefix);
  std::ofstream fout;
  fout.open(path.c_str());

  auto &rt = std::dynamic_pointer_cast<WccHelper>(app_helper_ptr)->result;
  for (auto iter : rt) {
    fout << iter.first << "\t" << iter.second << "\n";
  }

  fout.close();
  LOG(INFO) << "result output: " << path;
}

} // namespace graph
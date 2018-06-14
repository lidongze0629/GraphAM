#include "app/mst/mst_prim.h"

#include <memory>
#include <fstream>
#include <unordered_set>
#include <queue>
#include <vector>
#include <set>

#include "graph/utils.h"
#include "graph/fragment/immutable_edgecut_fragment.h"

namespace graph {

void PrimMST::ExecAlgorithm(unique_ptr<IFragment> &fragment,
                            const Vector<String> &query) {
  /*ImmutableEdgecutFragment *frag = dynamic_cast<ImmutableEdgecutFragment *>(fragment.get());
  vid_t tvnum = frag->GetVerticesNum();

  std::vector<bool> visited(tvnum, false);
  std::priority_queue<std::pair<double, vid_t >> heap;
  std::unordered_set<vid_t > vertices_set;

  for (unsigned vid = 0; vid < tvnum; vid++) {
    if (visited[vid]) continue;

    heap.push(std::make_pair(0.0, vid));
    while (!heap.empty()) {
      vid_t u = heap.top().second;
      unsigned distance = heap.top().first;

      heap.pop();

    }
  }*/
}

void PrimMST::WriteToFileResult(unique_ptr<IFragment> &fragment,
                                const String prefix, const Vector<String> &query) {

}

} // namespace graph
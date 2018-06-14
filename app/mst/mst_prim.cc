#include "app/mst/mst_prim.h"

#include <memory>
#include <fstream>
#include <unordered_set>
#include <queue>
#include <vector>
#include <iostream>

#include "graph/utils.h"
#include "app/mst/mst_context.h"
#include "graph/fragment/immutable_edgecut_fragment.h"

namespace graph {

void PrimMST::ExecAlgorithm(unique_ptr<IFragment> &fragment,
                            shared_ptr<IUDContext> &context_ptr,
                            const Vector<String> &query) {
  ImmutableEdgecutFragment *frag = dynamic_cast<ImmutableEdgecutFragment *>(fragment.get());
  vid_t tvnum = frag->GetVerticesNum();

  context_ptr = std::shared_ptr<IUDContext>(new MSTContext());

  auto &rt = std::dynamic_pointer_cast<MSTContext>(context_ptr)->result;

  std::vector<bool> visited(tvnum, false);
  std::priority_queue<std::pair<double, std::pair<vid_t, vid_t >>> heap;
  std::unordered_set<vid_t > vertices_set;

  for (unsigned i = 0; i < tvnum; i++) {
    if (visited[i]) continue;

    heap.push(std::make_pair(0.0, std::make_pair(i,i)));
    while (!heap.empty()) {
      vid_t u = heap.top().second.second;
      vid_t direct_to_u = heap.top().second.first; // only for record result
      double distance = -(heap.top().first);

      heap.pop();
      if (vertices_set.find(u) == vertices_set.end()) {
        vertices_set.insert(u);
        visited[u] = true; // for mst forest
        rt.emplace_back(direct_to_u, u, distance);

        auto es = frag->GetOutgoingEdges(u);
        for (auto &iter : es) {
          vid_t v = iter.dst();
          double len = iter.getData();
          heap.push(std::make_pair(-len, std::make_pair(u, v)));
        }
      }
    } // while
  }
}

void PrimMST::WriteToFileResult(unique_ptr<IFragment> &fragment,
                                shared_ptr<IUDContext> &context_ptr,
                                const String prefix, const Vector<String> &query) {
  std::string path = GetResultFileName(prefix);
  std::ofstream fout;
  fout.open(path.c_str());

  auto &rt = std::dynamic_pointer_cast<MSTContext>(context_ptr)->result;
  for (auto iter : rt) {
    fout << iter << "\n";
  }

  fout.close();
  LOG(INFO) << "result output: " << path;
}

} // namespace graph
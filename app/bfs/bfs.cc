#include "app/bfs/bfs.h"

#include <memory>
#include <limits>
#include <queue>
#include <vector>
#include <fstream>

#include "graph/utils.h"
#include "graph/fragment/immutable_edgecut_fragment.h"

namespace graph {

void BFS::ExecAlgorithm(unique_ptr<IFragment> &fragment,
                        shared_ptr<IUDContext> &app_helper_ptr,
                        const Vector<String> &query) {

  // (4 100) means source = 4, depth = 100
  ImmutableEdgecutFragment *frag = dynamic_cast<ImmutableEdgecutFragment *>(fragment.get());
  vid_t tvnum = frag->GetVerticesNum();

  auto vertices = frag->vertices();
  for (auto &v : vertices) {
    frag->SetPResult(v, std::numeric_limits<double>::max());
  }

  vid_t source = atoi(query[0].c_str());
  unsigned depth = atoi(query[1].c_str());

  std::priority_queue<std::pair<unsigned, vid_t >> queue;
  std::vector<bool> visited(tvnum, false);
  queue.push(std::make_pair(depth, source));

  while (!queue.empty()) {
    vid_t u = queue.top().second;
    unsigned u_depth = queue.top().first;
    queue.pop();

    if (visited[u]) continue;
    visited[u] = true;
    frag->SetPResult(u, u_depth);

    if (u_depth > 0) {
      auto es = frag->GetOutgoingEdges(u);
      for (auto &iter : es) {
        vid_t v = iter.dst();
        queue.push(std::make_pair(u_depth - 1, v));
      }
    }
  } // while
}

void BFS::WriteToFileResult(unique_ptr<IFragment> &fragment,
                            shared_ptr<IUDContext> &app_helper_ptr,
                            const String prefix, const Vector<String> &query) {
  std::string path = GetResultFileName(prefix);
  std::ofstream fout;
  fout.open(path.c_str());

  ImmutableEdgecutFragment *frag = dynamic_cast<ImmutableEdgecutFragment *>(fragment.get());
  vid_t tvnum = frag->GetVerticesNum();
  for (unsigned i = 0; i < tvnum; i++) {
    if (frag->GetPResult(i) != std::numeric_limits<double>::max()) {
      fout << i << "\t" <<frag->GetPResult(i) << "\n";
    }
  }
  fout.close();
  LOG(INFO) << "result output: " << path;
}

} // namespace graph
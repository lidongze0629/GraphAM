#include "app/sssp/sssp.h"

#include <limits>
#include <queue>
#include <vector>
#include <fstream>
#include <iostream>

#include "graph/utils.h"
#include "graph/fragment/immutable_edgecut_fragment.h"

namespace graph {

void SSSP::ExecAlgorithm(unique_ptr<IFragment> &fragment,
                         shared_ptr<IAppHelper> &app_helper_ptr,
                         const Vector<String> &query) {

  ImmutableEdgecutFragment *frag = dynamic_cast<ImmutableEdgecutFragment *>(fragment.get());
  auto vertices = frag->vertices();
  for (auto &v : vertices) {
    frag->SetPResult(v, std::numeric_limits<double>::max());
  }

  vid_t source = atoi(query[0].c_str());
  frag->SetPResult(source, 0);

  vid_t tvnum = frag->GetVerticesNum();
  std::priority_queue<std::pair<double, vid_t>> heap;
  std::vector<bool> visited(tvnum, false);
  heap.push(std::make_pair(0, source));

  int i = 0;

  while (!heap.empty()) {
    vid_t u = heap.top().second;
    i++;
    heap.pop();

    if (visited[u]) continue;
    visited[u] = true;

    auto es = frag->GetOutgoingEdges(u);
    for (auto &iter : es) {
      double len = iter.getData();
      vid_t v = iter.dst();
      double vdist = frag->GetPResult(v);
      double udist = frag->GetPResult(u);
      if(vdist > udist + len) {
        vdist = udist + len;
        frag->SetPResult(v, vdist);
        heap.push(std::make_pair(-vdist, v));
      }
    }
  }
}

void SSSP::WriteToFileResult(unique_ptr<IFragment> &fragment,
                             shared_ptr<IAppHelper> &app_helper_ptr,
                             const String prefix, const Vector<String> &query) {
  std::string path = GetResultFileName(prefix);
  std::ofstream fout;
  fout.open(path.c_str());

  ImmutableEdgecutFragment *frag = dynamic_cast<ImmutableEdgecutFragment *>(fragment.get());
  vid_t tvnum = frag->GetVerticesNum();
  for (unsigned i = 0; i < tvnum; i++) {
    fout << i << "\t" << frag->GetPResult(i) << "\n";
  }
  fout.close();
  LOG(INFO) << "result output: " << path;
}

}  // namespace graph

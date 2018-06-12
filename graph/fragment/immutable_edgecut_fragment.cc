#include "graph/fragment/immutable_edgecut_fragment.h"

#include <algorithm>

namespace graph {
void ImmutableEdgecutFragment::Init(Vector<Vertex> &vertices,
                                    Vector<Edge> &edges) {
  InitVertices(vertices);
  InitEdges(edges);
}

void ImmutableEdgecutFragment::InitVertices(Vector<Vertex> &vertices) {
  tvnum_ = vertices.size();
  vlist_.resize(tvnum_);
  for (auto &v : vertices) {
    vid_t vid = v.vid();
    vlist_[vid].SetInfo(vid, v.getData());
  }
}

void ImmutableEdgecutFragment::InitEdges(Vector<Edge> &edges) {
  std::vector<int> oenum(tvnum_, 0);
  std::vector<int> ienum(tvnum_, 0);

  for (auto &e : edges) {
    vid_t u = e.src();
    vid_t v = e.dst();
    oenum[u]++;
    ienum[v]++;
  }

  oe_.resize(edges.size());
  ie_.resize(edges.size());

  ieoffset_.resize(tvnum_ + 1);
  oeoffset_.resize(tvnum_ + 1);

  ieoffset_[0] = 0;
  oeoffset_[0] = 0;

  for (vid_t i = 0; i < tvnum_; i++) {
    ieoffset_[i + 1] = ieoffset_[i] + ienum[i];
    oeoffset_[i + 1] = oeoffset_[i] + oenum[i];
  }

  std::vector<std::vector<Edge>::iterator> ieiter(tvnum_), oeiter(tvnum_);

  for (vid_t i = 0; i < tvnum_; i++) {
    ieiter[i] = ieoffset_[i] + ie_.begin();
    oeiter[i] = oeoffset_[i] + oe_.begin();
  }

  for (auto &e : edges) {
    unsigned u = e.src();
    unsigned v = e.dst();

    oeiter[u]->SetInfo(u, v, e.getData());
    ieiter[v]->SetInfo(u, v, e.getData());

    oeiter[u]++;
    ieiter[v]++;
  }

  for (vid_t i = 0; i < tvnum_; i++) {
    std::sort(
        ie_.begin() + ieoffset_[i], ie_.begin() + ieoffset_[i + 1],
        [](const Edge &e1, const Edge &e2) { return e1.src() < e2.src(); });
    std::sort(
        oe_.begin() + oeoffset_[i], oe_.begin() + oeoffset_[i + 1],
        [](const Edge &e1, const Edge &e2) { return e1.dst() < e2.dst(); });
  }
}
}  // namespace graph
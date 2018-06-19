#ifndef GRAPH_FRAGMENT_IMMUTABLE_EDGECUT_FRAGMENT_H_
#define GRAPH_FRAGMENT_IMMUTABLE_EDGECUT_FRAGMENT_H_

#include <fstream>

#include "graph/fragment/edge.h"
#include "graph/fragment/i_fragment.h"
#include "graph/fragment/vertex.h"
#include "graph/graph_spec.h"
#include "graph/iterator_pair.h"
#include "graph/utils.h"

namespace graph {

class ImmutableEdgecutFragment : public IFragment {
 private:
  /** @inherit */
  class IMEItImpl : public EItImpl {
   public:
    /** @inherit */
    explicit IMEItImpl(Vector<Edge>::iterator it) : iter(it) {}
    /** @inherit */
    IMEItImpl *clone() { return new IMEItImpl(iter); }
    /** @inherit */
    void increment() { iter++; }
    /** @inherit */
    void add(int right) { iter += right; }
    /** @inherit */
    Edge &deref() { return *iter; }
    /** @inherit */
    Edge *pointer() { return &(*iter); }

   private:
    Vector<Edge>::iterator iter;
  };

 public:
  /** Constructor. */
  explicit ImmutableEdgecutFragment(const GraphSpec &graph_spec)
      : graph_spec_(graph_spec) {}

  vid_t GetVerticesNum() { return tvnum_; }

  void Init(Vector<Vertex> &vertices, Vector<Edge> &edges);

  void init_presult_on_vertex(const vid_t verticesNum) {
    presult_on_vertex_.resize(verticesNum);
  }

  IteratorPair<vertex_iterator> vertices() {
    return IteratorPair<vertex_iterator>(vlist_.begin(), vlist_.end());
  }

  IteratorPair<edge_iterator> GetOutgoingEdges(const vid_t lid) {
    return IteratorPair<edge_iterator>(
        edge_iterator(new IMEItImpl(oe_.begin() + oeoffset_[lid])),
        edge_iterator(new IMEItImpl(oe_.begin() + oeoffset_[lid + 1])));
  }

  IteratorPair<edge_iterator> GetIncomingEdges(const vid_t lid) {
    return IteratorPair<edge_iterator>(
        edge_iterator(new IMEItImpl(ie_.begin() + ieoffset_[lid])),
        edge_iterator(new IMEItImpl(ie_.begin() + ieoffset_[lid + 1])));
  }

  void SetPResult(const Vertex &v, const double &r) {
    presult_on_vertex_.at(v.vid()) = r;
  }

  void SetPResult(const vid_t lid, const double &r) {
    presult_on_vertex_.at(lid) = r;
  }

  double GetPResult(const vid_t lid) { return presult_on_vertex_.at(lid); }

  void Serialize(const String &prefix);

  void WriteStorage(InStorage &inStorage, FILE *fin);

 private:
  void InitVertices(Vector<Vertex> &vertices);
  void InitEdges(Vector<Edge> &edges);

  vid_t tvnum_;
  Vector<Vertex> vlist_;

  Vector<Edge> ie_, oe_;
  Vector<int> ieoffset_, oeoffset_;

  Vector<double> presult_on_vertex_;

  GraphSpec graph_spec_;
};
}  // namespace graph
#endif  // GRAPH_FRAGMENT_IMMUTABLE_EDGECUT_FRAGMENT_H_

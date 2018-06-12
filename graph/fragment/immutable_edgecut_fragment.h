#ifndef GRAPH_FRAGMENT_IMMUTABLE_EDGECUT_FRAGMENT_H_
#define GRAPH_FRAGMENT_IMMUTABLE_EDGECUT_FRAGMENT_H_

#include "graph/fragment/edge.h"
#include "graph/fragment/i_fragment.h"
#include "graph/fragment/vertex.h"
#include "graph/graph_spec.h"
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

  void init_presult_on_vertex(Vector<double> *presult) {
    presult_on_vertex_ = presult;
  }

 private:
  void InitVertices(Vector<Vertex> &vertices);
  void InitEdges(Vector<Edge> &edges);

  vid_t ivnum_, ovnum_, tvnum_;
  Vector<Vertex> vlist_;

  Vector<Edge> ie_, oe_;
  Vector<int> ieoffset_, oeoffset_;

  Vector<double> *presult_on_vertex_;

  GraphSpec graph_spec_;
};
}  // namespace graph
#endif  // GRAPH_FRAGMENT_IMMUTABLE_EDGECUT_FRAGMENT_H_
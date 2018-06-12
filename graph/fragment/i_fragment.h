#ifndef GRAPH_FRAGMENT_I_FRAGMENT_H_
#define GRAPH_FRAGMENT_I_FRAGMENT_H_

#include "graph/fragment/edge.h"
#include "graph/fragment/vertex.h"
#include "graph/utils.h"

namespace graph {

class IFragment {
 protected:
  /** Edge iterator
   *
   * A iterator for <Edge>.
   */
  class EItImpl {
   public:
    /** Default destructor. */
    virtual ~EItImpl() {}

    /** Clone a Edge iterator.
     *
     * @return a copy of Edge iterator.
     */
    virtual EItImpl *clone() = 0;

    /** Iterator increment. */
    virtual void increment() = 0;

    /** Iterator add
     * @param right the offset.
     *
     * The position of iterator add @right.
     */
    virtual void add(int right) = 0;

    /** Obtain edge by iterator.
     *
     * @return the edge located by iterator.
     */
    virtual Edge &deref() = 0;

    /** Obtain pointer of edge by iterator.
     *
     * @return the pointer of edge located by iterator.
     */
    virtual Edge *pointer() = 0;
  };

 public:
  /** An iterator of Vertex. */
  typedef Vector<Vertex>::iterator vertex_iterator;

  /** An iterator of Edge. */
  class edge_iterator {
   public:
    edge_iterator() : impl() {}
    explicit edge_iterator(EItImpl *impl) : impl(impl) {}
    edge_iterator(edge_iterator const &right) : impl(right.impl->clone()) {}
    ~edge_iterator() { delete impl; }
    edge_iterator &operator=(edge_iterator const &right) {
      delete impl;
      impl = right.impl->clone();
      return *this;
    }
    edge_iterator &operator+=(int right) {
      impl->add(right);
      return *this;
    }
    edge_iterator &operator++() {
      impl->increment();
      return *this;
    }
    edge_iterator operator++(int) {
      edge_iterator it(*this);
      impl->increment();
      return it;
    }
    Edge &operator*() { return impl->deref(); }
    Edge *operator->() { return impl->pointer(); }
    bool operator==(const edge_iterator &it) {
      return (impl->pointer() == it.impl->pointer());
    }

    bool operator!=(const edge_iterator &it) {
      return !(impl->pointer() == it.impl->pointer());
    }

   private:
    EItImpl *impl;
  };

  virtual void init_presult_on_vertex(Vector<double> *presult) = 0;

  virtual vid_t GetVerticesNum() = 0;

  virtual void Init(Vector<Vertex> &vertices, Vector<Edge> &edges) = 0;
};
}  // namespace graph
#endif  // GRAPH_FRAGMENT_I_FRAGMENT_H_
#ifndef GRAPH_FRAGMENT_EDGE_H
#define GRAPH_FRAGMENT_EDGE_H

#include "graph/utils.h"
#include "graph/utils/InStorage.h"

namespace graph {

class InStorage;

class Edge {
 public:
  /** Default constructor **/
  Edge() {}

  Edge(vid_t src, vid_t dst, const double data)
      : src_(src), dst_(dst), data_(data) {}

  inline const vid_t src() const { return src_; }

  inline const vid_t dst() const { return dst_; }

  inline const double &getData() const { return data(); }

  void set_data(const double &data) { data_ = data; }

  void SetInfo(vid_t src, vid_t dst, const double &data) {
    src_ = src;
    dst_ = dst;
    data_ = data;
  }

  Edge &operator=(const Edge &edge) {
    this->src_ = edge.src();
    this->dst_ = edge.dst();
    this->data_ = edge.data();
    return *this;
  }

 private:
  inline const double &data() const { return data_; }

  vid_t src_, dst_;
  double data_;

  friend std::ostream &operator<<(std::ostream &out, const Edge &e);
  friend std::istream &operator>>(std::istream &in, const Edge &e);

  friend InStorage &operator<<(InStorage &inStorage, const Edge &e);
};

inline std::ostream &operator<<(std::ostream &out, const Edge &e) {
  out << e.src() << "->" << e.dst() << "(" << e.getData() << ")";
  return out;
}

inline InStorage &operator<<(InStorage &inStorage, const Edge &e) {
  inStorage << e.src_<< e.dst_ << e.data_;
  return inStorage;
}
}

#endif  // GRAPH_FRAGMENT_EDGE_H
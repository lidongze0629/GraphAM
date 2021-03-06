#ifndef GRAPH_FRAGMENT_VERTEX_H_
#define GRAPH_FRAGMENT_VERTEX_H_

#include "graph/utils.h"
#include "graph/utils/InStorage.h"
#include "graph/utils/OutStorage.h"

namespace graph {

class InStorage;
class OutStorage;

class Vertex {
 public:
  Vertex() {}

  Vertex(vid_t vid, double data) : vid_(vid), data_(data) {}

  ~Vertex() {}

  inline const vid_t vid() const { return vid_; }
  inline const double &getData() const { return data(); }

  void set_vid(const vid_t vid) { vid_ = vid; }
  void set_data(const double &data) { data_ = data; }

  void SetInfo(const vid_t vid, const double &data) {
    vid_ = vid;
    data_ = data;
  }

 private:
  inline const double &data() const { return data_; }

  vid_t vid_;
  double data_;

  friend std::ostream &operator<<(std::ostream &out, const Vertex &v);
  friend std::istream &operator>>(std::istream &in, const Vertex &v);

  friend InStorage &operator<<(InStorage &storagem, const Vertex &v);
  friend OutStorage &operator>>(OutStorage &outStorage, Vertex &v);
};

inline InStorage &operator<<(InStorage &storage, const Vertex &v) {
  storage << v.vid_;
  storage << v.data_;
  return storage;
}

inline OutStorage &operator>>(OutStorage &storage, Vertex &v) {
  storage >> v.vid_;
  storage >> v.data_;
  return storage;
}

inline std::ostream &operator<<(std::ostream &out, const Vertex &v) {
  out << v.vid() << "(" << v.getData() << ")";
  return out;
}

}  // namespace graph

#endif  // GRAPH_FRAGMENT_VERTEX_H_
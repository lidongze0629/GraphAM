#ifndef GRAPH_UTILS_INSTORAGE_H_
#define GRAPH_UTILS_INSTORAGE_H_

#include "graph/utils.h"

namespace graph {
/**
 * It include a char type vector to maintains Any Object bytes
 */
class InStorage {
 public:
  InStorage() {}

  ~InStorage() {}

  inline void AddByte(char c) { buffer_.push_back(c); }

  inline void AddBytes(const void *begin, const int size) {
    buffer_.insert(buffer_.end(), (const char *)begin,
                   (const char *)begin + size);
  }

  inline void Clear() { buffer_.clear(); }

  inline size_t BufferSize() { return buffer_.size(); }

  inline char *GetBuffer() { return &buffer_[0]; }

 private:
  Vector<char> buffer_;
};

inline InStorage &operator<<(InStorage &inStorage, size_t st) {
  inStorage.AddBytes(&st, sizeof(st));
  return inStorage;
}

inline InStorage &operator<<(InStorage &inStorage, unsigned u) {
  inStorage.AddBytes(&u, sizeof(unsigned));
  return inStorage;
}

inline InStorage &operator<<(InStorage &inStorage, double d) {
  inStorage.AddBytes(&d, sizeof(double));
  return inStorage;
}

inline InStorage &operator<<(InStorage &inStorage, int i) {
  inStorage.AddBytes(&i, sizeof(int));
  return inStorage;
}

template <class T>
inline InStorage &operator<<(InStorage &inStorage, const std::vector<T> &vect) {
  size_t size = vect.size();
  inStorage << size;
  for (auto &iter : vect) {
    inStorage << iter;
  }
  return inStorage;
}

}  // namespace graph

#endif  // GRAPH_UTILS_INSTORAGE_H_
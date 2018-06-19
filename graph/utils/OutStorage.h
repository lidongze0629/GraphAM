#ifndef GRAPH_UTILS_OUTSTORAGE_H_
#define GRAPH_UTILS_OUTSTORAGE_H_

#include "graph/utils.h"

namespace graph {

class OutStorage {
 public:
  OutStorage() : buffer_(nullptr), size_(0), index_(0) {}

  ~OutStorage() {
    if (buffer_ != nullptr) delete[] buffer_;
  }

  inline void Clear() {
    if (buffer_ != nullptr) delete[] buffer_;
    buffer_ = nullptr;
    size_ = 0;
    index_ = 0;
  }

  inline char GetByte() { return buffer_[index_++]; }

  inline void *GetBytes(unsigned int size) {
    char *result = buffer_ + index_;
    index_ += size;
    return result;
  }

  inline void SetBuf(char *buffer, size_t size) {
    buffer_ = buffer;
    size_ = size;
    index_ = 0;
  }

 private:
  char *buffer_;
  size_t size_;
  size_t index_;
};

inline OutStorage &operator>>(OutStorage &outStorage, unsigned &u) {
  u = *reinterpret_cast<unsigned *>(outStorage.GetBytes(sizeof(unsigned)));
  return outStorage;
}

inline OutStorage &operator>>(OutStorage &outStorage, double &d) {
  d = *reinterpret_cast<double *>(outStorage.GetBytes(sizeof(double)));
  return outStorage;
}

inline OutStorage &operator>>(OutStorage &outStorage, int &i) {
  i = *reinterpret_cast<int *>(outStorage.GetBytes(sizeof(int)));
  return outStorage;
}

inline OutStorage &operator>>(OutStorage &outStorage, size_t &st) {
  st = *reinterpret_cast<size_t *>(outStorage.GetBytes(sizeof(size_t)));
  return outStorage;
}

template <class T>
inline OutStorage &operator>>(OutStorage &outStorage, std::vector<T> &vect) {
  size_t size;
  outStorage >> size;
  vect.resize(size);
  for (size_t i = 0; i < size; i++) {
    outStorage >> vect[i];
  }
  return outStorage;
}

} // namespace graph

#endif // GRAPH_UTILS_OUTSTORAGE_H_
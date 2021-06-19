#ifndef NANO_CEREAL_STREAM_HPP
#define NANO_CEREAL_STREAM_HPP

#include "etl/deque.h"

namespace nanocereal {
using streambuf = etl::ideque<uint8_t>;

class istream {
 public:
  istream(streambuf *buf) : buf(buf) {}

  void read(uint8_t *const data, size_t size) {
    for (size_t i = 0; i < size; i++) data[i] = buf->at(i);
    buf->erase(buf->begin(), buf->begin() + size);
  }

 private:
  streambuf *buf;
};

class ostream {
 public:
  ostream(streambuf *buf) : buf(buf) {}

  void write(const uint8_t *const data, size_t size) {
    for (size_t i = 0; i < size; i++) buf->push_back(data[i]);
  }

 private:
  streambuf *buf;
};
}  // namespace nanocereal

#endif  // NANO_CEREAL_STREAM_HPP
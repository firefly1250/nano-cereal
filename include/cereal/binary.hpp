#ifndef NANO_CEREAL_BINARY_HPP
#define NANO_CEREAL_BINARY_HPP

#include <istream>
#include <ostream>

namespace cereal {
class ArchiveBase {
 public:
  template <class... Types>
  void operator()(Types &&...args) {
    process(std::forward<Types>(args)...);
  }

 protected:
  virtual void archive_binary(void *const data, std::streamsize size) = 0;

 private:
  template <class T, class... Other>
  void process(T &&head, Other &&...tail) {
    process(std::forward<T>(head));
    process(std::forward<Other>(tail)...);
  }

  template <class T>
  void process(T &&head) {
    archive(std::forward<T>(head));
  }

  // arithmetic
  template <class T>
  typename std::enable_if<std::is_arithmetic<T>::value, void>::type archive(
      T &t) {
    archive_binary(std::addressof(t), sizeof(t));
  }

  // class or struct
  template <class T>
  typename std::enable_if<std::is_class<T>::value, void>::type archive(T &t) {
    t.serialize(*this);
  }

  // array
  template <class T>
  typename std::enable_if<std::is_array<T>::value, void>::type archive(T &t) {
    for (auto &e : t) archive(e);
  }
};

class BinaryOutputArchive : public ArchiveBase {
 public:
  BinaryOutputArchive(std::ostream &stream) : stream(stream) {}

 private:
  void archive_binary(void *const data, std::streamsize size) override {
    stream.write(reinterpret_cast<const char *>(data), size);
  }

  std::ostream &stream;
};

class BinaryInputArchive : public ArchiveBase {
 public:
  BinaryInputArchive(std::istream &stream) : stream(stream) {}

 private:
  void archive_binary(void *const data, std::streamsize size) override {
    stream.read(reinterpret_cast<char *>(data), size);
  }

  std::istream &stream;
};
}  // namespace cereal

#endif  // NANO_CEREAL_BINARY_HPP
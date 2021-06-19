nano-cereal - cereal for embedded systems
==========================================
[cereal](https://github.com/USCiLab/cereal) is a header-only C++11 serialization library.

nano-cereal is cereal compatible minimal implementation for embedded systems.

nano-cereal only supports BinaryInputArchive / BinaryOutputArchive.

To serialize class/struct, you must define member function named `serialize` like below example.


### usage
```cpp
#include <nano-cereal/binary.hpp>
#include <fstream>

struct MyRecord {
  uint8_t  x, y;
  float z;

  template <class Archive>
  void serialize(Archive &ar) {
    ar(x, y, z);
  }
};

int main() {
  namespace cereal = nanocereal;
  std::ofstream os("out.cereal", std::ios::binary);
  cereal::BinaryOutputArchive archive(os);

  MyRecord data1;
  int data2
  archive(data1, data2);

  return 0;
}
```

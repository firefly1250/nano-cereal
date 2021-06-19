#include <nano-cereal/binary.hpp>
#include <sstream>
#include <iostream>

struct MyRecord {
  int x, y;
  float z;

  template <class Archive>
  void serialize(Archive &ar) {
    ar(x, y, z);
  }
};

int main() {
  namespace cereal = nanocereal;
  std::stringstream ss;

  // output
  {
    cereal::BinaryOutputArchive archive(ss);

    int int_data = 5;
    MyRecord struct_data{1, 2, -5.5};
    double array_data[5]{1, 2, 3, 4, 5};
    archive(int_data, struct_data, array_data);
  }

  // input
  {
    cereal::BinaryInputArchive archive(ss);

    int int_data = 0;
    MyRecord struct_data{0, 0, 0};
    double array_data[5]{0};
    archive(int_data, struct_data, array_data);

    std::cout << "int_data: " << int_data << std::endl;
    std::cout << "data: " << struct_data.x << ", " << struct_data.y << ", "
              << struct_data.z << std::endl;
    std::cout << "array: ";
    for (const auto &e : array_data) std::cout << e << ",";
    std::cout << std::endl;
  }
  return 0;
}
#include <nano-cereal/binary.hpp>
#include <cereal/archives/binary.hpp>
#include <iostream>

struct MyRecord {
  uint8_t x;
  int y[5];
  enum E { a, b, c, d, e, f } z;

  template <class Archive>
  void serialize(Archive &ar) {
    ar(x, y, z);
  }

  bool operator==(const MyRecord &m) {
    if (x != m.x) return false;
    for (int i = 0; i < 5; i++)
      if (y[i] != m.y[i]) return false;
    if (z != m.z) return false;

    return true;
  }
};

int main() {
  etl::deque<uint8_t, 100> buf;
  MyRecord output_data;
  MyRecord input_data;

  // output
  {
    output_data.x = 24;
    output_data.y[3] = 5;
    output_data.z = MyRecord::E::d;
    nanocereal::ostream os(&buf);
    nanocereal::BinaryOutputArchive archive(os);
    archive(output_data);
  }

  std::string str;
  std::copy(buf.begin(), buf.end(), std::back_inserter(str));
  std::stringstream ss;
  ss << str;

  // input
  {
    cereal::BinaryInputArchive archive(ss);
    archive(input_data);
  }

  const auto result = output_data == input_data;
  std::cout << result << std::endl;
  return 0;
}
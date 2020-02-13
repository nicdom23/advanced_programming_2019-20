#include <fstream>
#include <sstream>//i create a base name string and for a for loop i construct a string using the to to operator

int main() {
  std::string base_name{"file_"};
  for (auto i = 0; i < 10; ++i) {
    std::stringstream ss;
    ss << base_name << i << ".txt";
    std::ofstream f{ss.str()};//retruns a string
    f << i << std::endl;
  }

  return 0;
}

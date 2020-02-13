#include <iostream>
#include <memory>  // std::uniqe_ptr

#include "ap_error.h"

class Vector {
  std::unique_ptr<double[]> elem;

 public:
  Vector(const unsigned int l) : elem{new double[l]} {
    std::cout << "Vector ctor\n";
  }
  double& operator[](const unsigned int i) noexcept {
    return elem[i];
  }  // you can use smart pointers almost like raw pointers
  ~Vector() noexcept { std::cout << "~Vector\n"; }
};
/*slower than raw pointers
shared pointers, people can share, someone is responsible for the address
No need for adding the delete[]
use smart pointers ::: one is responsible with deleting the resources

No two unique pointers that share in the same pointer

there are software penalties for this
if a function doesn't throw an exception point it as noexcept, no excption handling, call will be faster, else if exception you abort::::faster code >>no except C++11
*/
class ManyResources {
  std::unique_ptr<double[]> ptr;
  Vector v;

 public:
  ManyResources() : ptr{new double[5]}, v{3} {
    std::cout << "ManyResources ctor\n";
    AP_ERROR(false) << "I am simulating something wrong.\n";
  }//no except new in c++
  ~ManyResources() noexcept { std::cout << "~ManyResources\n"; }
};

int main() {
  try {
    std::unique_ptr<int[]> up{new int[7]};
    ManyResources mr;

  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;

  } catch (...) {
    std::cerr << "Unknown exception. Aborting.\n" << std::endl;
    return 2;
  }

  return 0;
}

#include <iostream>
#include <vector>

#include "ap_error.h"

class Foo {
 public:
  Foo() { std::cout << "Foo" << std::endl; }
  ~Foo() { std::cout << "~Foo" << std::endl; }
};

class Bar {
 public:
  Bar() { std::cout << "Bar" << std::endl; }
  ~Bar() { std::cout << "~Bar" << std::endl; }
};

class Vector {
  double* elem;

 public:
  Vector(const unsigned int l) : elem{new double[l]} {
    std::cout << "Vector" << std::endl;
  }
  ~Vector() noexcept {
    delete[] elem;
    std::cout << "~Vector" << std::endl;
  }
};

class ManyResources {
  double* ptr;
  Vector v;

 public:
  ManyResources() : ptr{nullptr}, v{3} {//if vector runs an exception inside the constructor body i delete my pointer, then i tìrethrow the ball
    std::cout << "Manyresources" << std::endl;
    try {
      ptr = new double[5];  // new(std::nothrow) double[5] could be better
      AP_ERROR(false) << "Error in ManyResources ctor." << std::endl;//new launches an exception //force error in constructoe of manyresources: what if ram is finished, new will throw an exception.if the memory cant be allocated returnd nul l piunter in C: here we retunr a nexcetption  
//RUN
    } catch (...) {
      delete[] ptr;  // <----
      throw;//rethrow the catch
/*DOnt use raw pointers it is a mess we have to take care of all the paths, solutions is to use smart pointer >>unique pointer ownership
               >> shared pointer, i acceot that ther might be multipel to shares the memory adress, the last one to have
  */  }
  }

  ~ManyResources() noexcept {
    std::cout << "Manyresources" << std::endl;
    delete[] ptr;  // <----
  }
};

int main() {
  Foo f;
  int* raw_ptr = new int[7];//delete raw pter must be repeatded not to have memory leaks
  try {
    // int * raw_ptr=new int[7]; // wrong because raw_ptr would not be visible
    // inside the catch-clause
    ManyResources mr;//here fails
    Bar b;



  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;

    delete[] raw_ptr;  // <--- try to comment this and run valgrind or use the
                       // sanitize library
    return 1;

  } catch (...) {
    std::cerr << "Unknown exception. Aborting.\n" << std::endl;

    delete[] raw_ptr;  // <---
    return 2;
  }

  delete[] raw_ptr;  // <---
  return 0;
}

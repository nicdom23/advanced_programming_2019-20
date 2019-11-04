#include <iostream>

struct X {
  int a = 5;  // in-class initialization (not slways rthe three cosntructors will be genearted by the compiler, to do so you can use default codename
  double b;
  char c = 'a'; //we do initialize the variables with or withoout curly braces if they are specified here
  X() = default;  // in-class initializers are used by the constructors: 
};

struct Y {
  int a = 77;
  double b;
  char c = 'a';
  Y() : a{5} {a=7;}  // what it is written here wins the in-class initialization of the variables
      // a->5->7 b->uninit c->a
  Y(const Y&) = delete;
};//custom types are always initialized

int main() {
  X x1;    // compiler-generated default ctor
  X x2{};  // compiler-generated default ctor calls {} on uninitialized vars
  std::cout << x1.a << "--" << x1.b << "--" << x1.c << "\n";
  std::cout << x2.a << "--" << x2.b << "--" << x2.c << "\n\n";

  Y y1;    // default ctor
  Y y2{};  // default ctor
  std::cout << y1.a << "--" << y1.b << "--" << y1.c << "\n";
  std::cout << y2.a << "--" << y2.b << "--" << y2.c << "\n";

  // Y y3{y2}; // error: call to a deleted function

  return 0;
}//STD:vector as the class of reference: we can copy one vector into the other, copy is done elementwise,they implement a copy constructor and a copy assinments..copy semantics

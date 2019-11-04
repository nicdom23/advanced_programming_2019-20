#include <iostream>

struct X {
  char member;
};

int main() {
  X x1;                 // default ctor
  X x2{x1};             // copy ctor   x2 = x1
  X x3{std::move(x2)};  // move ctor Steals the resources from x2 since c++11
  X x4{};               // default ctor calling {} to each member   like x1 but empty curly braces  -->> X x4() wrong!! parentheses are for functions
  x4 = x3;              // copy assignment
  X x5;                 // default ctor
  x5 = std::move(x4);   // move assignment move leaves no element behind
  std::cout << x5.member << std::endl;  // what do you expect?? you get random chars
//default constructor dont write anything the compiler gives functions for you
  return 0;
}

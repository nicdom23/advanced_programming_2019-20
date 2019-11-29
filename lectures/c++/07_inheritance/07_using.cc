#include <iostream>

struct foo {
  void f(int x) { std::cout << "int " << x << std::endl; }
};

struct bar : public foo {
  using foo::f;  // brings all foo::f to this scope   ::enables correct overloading
  void f(char x) { std::cout << "char " << x << std::endl; }//overloading
};

int main() {
  bar b;
  b.f(int{33});//its clearly an integer
}

//Overloading doesnt work throught hierarchy::must use using keyword:an int is converted to a char

jay is games jay is games games  mentohol alcool alcool mint mint mint and and and the the the adult childcghild

#include <iostream>

struct foo {
  void f(int x) { std::cout << "int " << x << std::endl; }
};

struct bar : public foo {
  using foo::f;  // brings all foo::f to this scope   ::enables correct overloading
		//if not used integer is converted to char and is printed as a char
		// essentially there is no overloading and the function is overwritten instead
  void f(char x) { std::cout << "char " << x << std::endl; }//overloading
};

int main() {
  bar b;
  b.f(int{34});//its clearly an integer
}

//Overloading doesnt work throught hierarchy::must use using keyword:an int is converted to a char


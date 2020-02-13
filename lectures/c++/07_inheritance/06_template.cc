#include <iostream>

template <typename T>
struct Base {
  void foo() const { std::cout << "base foo" << std::endl; }
};

template <typename T>
struct Derived : public Base<T> {//base class is templated

  void bar() const { /*this->*/foo(); }//this is a pointer to the object on which the function is called------ use ->
};
//there might be an error if you remove this-> a pointer to myself
int main() {
  Derived<int> d;
  d.bar();
}

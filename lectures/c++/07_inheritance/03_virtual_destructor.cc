#include <iostream>

struct Base {
  Base() { std::cout << "Base\n"; }
  virtual ~Base() { std::cout << "~Base\n"; }  //without this virtual we have a memory leakage
};

struct Derived : public Base {
  int* p;

  Derived()  :p{new int[4]}{ std::cout << "Derived\n"; }
  ~Derived() { delete p;
               std::cout << "~Derived\n"; }
};

int main() {
  { Derived d; } //object lives and is destructed in this scope

  std::cout << "\n\npointers\n";
  Base* p = new Derived;
  delete p; //if ~Base is not virtual only the ~Base destructor is invoked
            //and not both
  return 0;
}

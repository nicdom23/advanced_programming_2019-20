#include <iostream>

void swap(int a, int b);

int main() {
  int x{3}, y{7};
  std::cout << "before\t" << x << " " << y << std::endl;
  swap(x, y);
  std::cout << "after\t" << x << " " << y << std::endl;
  return 0;
}

void swap(int a, int b) {//once again we pass by value two variables, so they do not change
  int t{a};
  a = b;
  b = t;
  std::cout<<"inside\t"<< a <<" "<< b <<std::endl;//added by me
}

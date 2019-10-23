#include <iostream>

void buggy_swap(int a, int b);
void swap_c(int *a, int *b);
void swap_cxx(int &a, int &b);

int main() {
  int a = {3.2}
  int b = {7};
  buggy_swap(a, b);
  std::cout << "buggy:\texpected 7 3 --> " << a << " " << b << "\n";

  a = 3;
  b = 7;
  swap_c(&a, &b);//adresses are passed
  std::cout << "c:\texpected 7 3 --> " << a << " " << b << "\n";

  a = 3;
  b = 7;
  swap_cxx(a, b);
  std::cout << "cxx:\texpected 7 3 --> " << a << " " << b << "\n";
}

void buggy_swap(int a, int b) { //cant access to the variables
  int tmp = b;
  b = a;
  a = tmp;
}

void swap_c(int *a, int *b) { //pointers
  int tmp = *b;
  *b = *a;
  *a = tmp;
}

void swap_cxx(int &a, int &b) { //references
  int tmp = b;
  b = a;
  a = tmp;
}

#include <cstring>  // strcmp
#include <iostream>

int func1(const char* a);
int func2(const char* a);
void func3(const char* a);

int main() {
  int a{8};// a variable
  int* pi{&a}; //a pointer to a variable
	std::cout<<"pointer pi"<<pi<<std::endl;
  char** ppc; //a pointer to a pointer
  std::cout<<"pointer ppc"<<ppc<<std::endl;
  int* ap[7];//a pointer to an array(also a double pointer)
 std::cout<<"pointer ap"<<ap<<std::endl;


  void* pv{pi};//a pointer to a pointer
  // *pv; // we cannot dereference void*
  // ++pv; // we cannot increment. Why?
  int* pi2{static_cast<int*>(pv)};//we cast the pointer to a new pointer
	std::cout<<"pointer pv by himself"<<pv<<std::endl;
  pv = ppc;
std::cout<<"pointer pv after ppc"<<pv<<std::endl;
  pv = ap;
std::cout<<"pointer pv after ap"<<pv<<std::endl;
  pv = pi;
std::cout<<"pointer pv after pi"<<pv<<std::endl;


  pi = nullptr;
  ppc = nullptr;
  // ap = nullptr;  // error, why?
  ap[0] = nullptr;
  int** bbb;
  bbb = ap;
  pv = nullptr;
  pi2 = 0;  // older codes. gets the nullptr

  // pi = NULL; // please don't do this

  double* da{new double[5]{}};
  delete[] da;  // dangling pointer
	std::cout<<"dangling pointer da"<<da<<std::endl;
  da = nullptr;
 std::cout<<"dangling pointer da"<<da<<std::endl;
  //equivalent ways of determining if a pointer is a nullpointer

  if (pi != nullptr)
    std::cout << "pi is not nullptr and I can dereference it " << *pi
              << std::endl;

  if (pi)
    std::cout << "pi is not nullptr and I can dereference it " << *pi
              << std::endl;

  if (pi == nullptr)
    std::cout << "pi is nullptr and I CANNOT dereference it \n";

  if (!pi)
    std::cout << "pi is nullptr and I CANNOT dereference it \n";

  // strings are special type of char[]
  char word[]{"Hello"};
  char word2[]{'H', 'e', 'l', 'l', 'o', 0};
  if (strcmp(word, word2) == 0)  // word == word2 is
                                 // implementation-dependent (it might
                                 // compare the two pointers, i.e. the
                                 // two addresses of word and word2)
    std::cout << "same\n";
  else
    std::cout << "different\n";

//using pointers to reference at functions

  int (*fp)(const char*);
  fp = func1;

  fp("hello");

  fp = &func2;
  fp("world");

  // fp = func3; // error: wrong signature
  auto xx = func3;

  xx("auto");

  decltype(&func3) x = func3;
  x("decltype");

  return 0;
}

int func1(const char* a) {
  std::cout << "1111: " << a << std::endl;
  return 1;
}

int func2(const char* a) {
  std::cout << "2222: " << a << std::endl;
  return 2;
}

void func3(const char* a) {
  std::cout << "3333: " << a << std::endl;
}

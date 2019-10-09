#include <iostream>

template <typename T,typename OT> //specify as <int,double>
T dwim(const T a, const T b);

int main() {
  int a{5}, b{7};
  double c{3.332}, d{7.7};
  float e{23.4}, f{3.34e2};
  char g{'0'}, h{'6'};

  std::cout << dwim<int>(a, b) << '\n' //specify the type of template
            << dwim(c, d) << '\n'//can be omitted cause it can deduce it from the parameters in the function call 
            << dwim(e, f) << '\n'
            << dwim(g, h) << std::endl;
  return 0;
}

template <typename T> //also work for <class T>
T dwim(const T a, const T b) {
  return a + b;
}

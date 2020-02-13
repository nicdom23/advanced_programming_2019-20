#include <iostream>

// forward declaration
int dwim(const int a, const int b);
double dwim(const double a, const double b); //i defined here the functions declarations so the compiler knows the types, the definitions will go after the main body
float dwim(const float a, const float b);
int dwim(const int a, const float b);




int main() {
  int a{5}, b{7};
  double c{3.332}, d{7.7};
  float e{23.4}, f{3.34e2};

  std::cout << dwim(a, b) << '\n'
            << dwim(c, d) << '\n'
            << dwim(e, f) << std::endl;

	std::cout<<"test:  "<<dwim(a,e)<<std::endl;
  return 0;
}

int dwim(const int a, const int b) {
  std::cout << "int ------ ";
  return a + b;
}

double dwim(const double a, const double b) {
  std::cout << "double --- ";
  return a + b;
}
float dwim(const float a, const float b) {
  std::cout << "float ---- ";
  return a + b;
}

int dwim(const int a, const float b) {
  std::cout << "float to int---- ";
  
      return a + b;
}


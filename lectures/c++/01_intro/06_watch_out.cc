#include <iomanip>
#include <iostream>

int main() {
  // size matters!
  int a = 1;
  for (int i = 0; i < 33; ++i) {
    a *= 2;
    std::cout << a << std::endl;
  }

  // never ever use == (or !=) with floating point numbers

   //for (double d = 0.1; d != 1.0; d += 0.1) //It is an endless cycle
    //std::cout << d << std::endl;

    std::cout << std::setprecision(50);
   double d = 0;
   for (int i = 0; i < 10; ++i) { //we see that the printed numbers are
    d += 0.1;			//not precise enough
    std::cout << d << std::endl;
   }
  return 0;
}

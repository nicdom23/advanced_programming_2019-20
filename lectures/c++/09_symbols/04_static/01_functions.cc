#include <iostream>

void dwim() {
  static int i = 0;  // this line is executed only once  //remembers the value for all the executions, and survives until the end of the program
  ++i;
  std::cout << i << std::endl;
}

int main() {
  dwim();
  dwim();
  dwim();//all variables are static by default in FORTRAN
  dwim();//if we execute then i remembers how many times the function was invoked
  dwim();
  return 0;
}

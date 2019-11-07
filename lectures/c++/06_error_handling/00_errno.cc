#include <cmath>
#include <iostream>
//errno is a macro a global variable that assumes a different value from 0 to a value int
// /*
a varia
what counts is that it is not reset to zero!!
an error happened and you dont know how the user wants to develop the error

Once the error is detected that should be given to the user,,you chioose ehat to do , eventually 
you reset errno = 0 saying you handled that

you have to chaeck the values,what does it mean you need to know. You better know the typer of the error, to see. this is what exceptions do >>NEXT
*/
int main() {
  double d = std::sqrt(4);
  std::cout << d << " " << errno << std::endl;

  d = std::sqrt(-4);
  std::cout << d << " " << errno << std::endl;



  return 0;
}

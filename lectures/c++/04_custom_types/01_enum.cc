#include <iostream>
//color is a new type
enum color { red, yellow, green }; //Used to avoid magic numbers, you have constants with the same value.You have to check if color is equal to certain constants 1,2,3etc 
//trying name clashing
///enum apples{ yellow, green, red};//error conflicts with previous declaration

// enum color{red=0, yellow=1, green=2}; // equivalent
//do not add magic numbers_use const expression instead
void dwim(const color c) {
  switch (c) {//name of the variable,case the value of this variable, and then break, to avoid doing the lines of the next cases
    case red:
      std::cout << "option 1: red\n";
      break;
    case yellow:
      std::cout << "option 2: yellow\n";
      break;
    case green:
      std::cout << "option 3: green\n";
      break;
    default: //defaut options error handling
      std::cout << "unknown option\n";  // should I exit the program?
      break;
  }
}

int main() {
  color opt{red};
  // opt = 3; // cannot assign int to enum
  int a{opt};  // but they implicitly converts to integers!!

  dwim(opt);

  dwim(yellow);

  // dwim(2); // error,because of what we said above
  dwim(color(2));  // works but why you may want to write this?

  dwim(color(6));  // ??? It works! But wedont have 6 colours, it goes to default options.

  return 0;
}

#include <iostream>
extern "C"{   //if you use nm name of the program in .o you will get c++ symbols
  void hello(){
    std::cout << "Hello, World" << std::endl;
  }
}

int main(){
  hello();
  printf("Hello World");
}

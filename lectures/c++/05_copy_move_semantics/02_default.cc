#include <iostream>
#include <string>

struct S {
  int a;
  double b;
  std::string s;  // default ctor of string set s to empty string
};

int main() { 
  S s1;  // calls default constructor(compiler generqted deqfault constructor) ---> uninitialized built in types

  S s2{1, 2.3, "alberto"};  // if there are no custom ctors I can
                            // directly initialize the members. Note
                            // that I need access (i.e. they must be
                            // public) like in C
  // it is called aggregate initialization (see
  // https://en.cppreference.com/w/cpp/language/aggregate_initialization)

  S s3{};  // calls {} on each member: S s3 { {}, {}, {} }; default constructor for each member
//use as a main constructor in your code initialize built in type
  std::cout << s1.a << "--" << s1.b << "--" << s1.s << "\n"; //random values,string = empty, for the default constructor
  std::cout << s2.a << "--" << s2.b << "--" << s2.s << "\n"; //already initialized
  std::cout << s3.a << "--" << s3.b << "--" << s3.s << "\n"; //initialized values to initial values

  return 0;
}

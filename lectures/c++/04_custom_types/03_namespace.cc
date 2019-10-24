#include <iostream>
//why we use scoped enum
namespace choose_a_name {
  int variable;//inside choose_a_name
//prepend the name of the space itself
  namespace nested {

    void hello1();
    void hello2();
    void hello3();

  }  // namespace nested
}  // namespace choose_a_name

int main() {
  // variable = 42; // error
  choose_a_name::variable = 42;
  // hello1(); // error
  choose_a_name::nested::hello1();//result of nested namespaces
  choose_a_name::nested::hello2();//fully qualified name
  // we group functions object related to something and avoid namecrashing, especially to avoid people wo call a function with the same name
  choose_a_name::nested::hello3();
  return 0;
}

void choose_a_name::nested::hello1() {//fucntion definition
  std::cout << "hello1 from nested\n"
            << "variable is " << choose_a_name::variable << std::endl;
}

namespace choose_a_name {//we try by entering namespaces
  namespace nested {
    void hello2() {
      std::cout << "hello2 from nested\n"
                << "variable is " << variable << std::endl;//variable is visible now
    }
  }  // namespace nested
}  // namespace choose_a_name

using namespace choose_a_name;//importing namespaces in the program

void nested::hello3() {
  std::cout << "hello3 from nested\n"
            << "variable is " << variable << std::endl;
}

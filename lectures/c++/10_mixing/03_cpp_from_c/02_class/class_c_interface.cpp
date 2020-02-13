#include "class_c_interface.h"  //it is a c++ implementation of the functions defined
#include "class.hpp"

//in the end we will link c-main.c with class.o and class
extern "C" {

Foo_c create_foo(int b) {  //we will use a constructor that is defined only in a c++ compilere
  return new Foo(b);
}//we must specify Foo<int>(b) if Foo was templated, we need to write create_foo_int create_foo_double,and specifically instantiate them
void free_foo(Foo_c f) {
  delete static_cast<Foo*>(f); //do a static cast to foo* (from void*)so i do know the type of the object, so i know that the data is in class.hpp // here in c++ you have to call a destructor
}
void print_foo(Foo_c f) {
  static_cast<Foo*>(f)->print();
}
void set_a(Foo_c f, int v) {
  static_cast<Foo*>(f)->get_a() = v;
};
int get_a(Foo_c f) {
  return static_cast<Foo*>(f)->get_a();
}
}

//with templates you cannot export functions that are templated

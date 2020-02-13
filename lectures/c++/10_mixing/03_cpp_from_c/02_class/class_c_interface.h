#ifndef _CLASS_C_INTERFACE_H_
#define _CLASS_C_INTERFACE_H_

typedef void* Foo_c;  //create a new type that is a pointer that points to whatever

#ifdef __cplusplus  //this is for the preprocessor if this symbol is defined then this code is processed by a c++ compiler // this happens for every c library
extern "C" {//needed because this file is included by class_c_interface.cpp
#endif

Foo_c create_foo(int b);
void free_foo(Foo_c);
void print_foo(Foo_c);
void set_a(Foo_c, int v);//You don't have references, you need to change by a function
int get_a(Foo_c);//return by value

#ifdef __cplusplus
}
#endif

#endif /* _CLASS_C_INTERFACE_H_ */

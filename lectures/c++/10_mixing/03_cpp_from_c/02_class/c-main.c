#include "class_c_interface.h"
#include <stdio.h>

int main() {//i have new functions
  Foo_c f = create_foo(11);//creates a pointer crated in another function that points to a heap memory location(that's why i have to free
  print_foo(f);
  set_a(f, 7);
  print_foo(f);
  set_a(f, 9);
  printf("hello from c! a is %d\n", get_a(f));
  free_foo(f);
  return 0;
}

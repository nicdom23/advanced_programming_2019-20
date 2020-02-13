#include <dlfcn.h>

int main(int argc, char* argv[]) {
  void* handle; /* handle for dynamic object */
  void (*hi)(); /* function pointer for symbol */
  int (*rep)(char*);
  handle = dlopen("./libhello.so", RTLD_LAZY);
  if (handle) {
    hi = (void (*)())dlsym(handle, "hello");
    (*hi)(); //invoke the function
    rep = (int (*)(char*))dlsym(handle, "repeat");
    rep("I dont't care what fox says");//invoke the funciton
    dlclose(handle);
  }
  return 0;
}//do it if we want to enrich functions without changing their implementations

#include <cmath>
#include <iostream>

#if __cplusplus > 201103L//preprocessor macro to check if i support c++ 11

template <class T>
auto init(const std::size_t l) {
  return new T[l]{};//{}means zero inizialization
}

#else //no more auto in an outdated version of c++

template <class T>
T* init(const std::size_t l) {
  return new T[l]{};
}

#endif

template <class T> //safe error to query the type of a function
void debug(T);	
	//c++ is a strong type language and a statically typed language
int main() {//automatic type assignation
  auto b = true;          // a bool
  auto ch = 'x';          // a char
  auto i = 123;           // an int  the standard is just that
  auto d = 1.2;           // a double not a float
  auto z = std::sqrt(d);  // z has the type of whatever sqrt(d) returns
  auto ui = 0u;           // unsigned int  here is a suffix
  auto llui = 0llu;       // long long unsigned int
  // ::scope resolution estimator
  // universal and uniform initializer is not used here
  for (auto i = 0; i < 7; ++i)
    std::cout << i << std::endl;


  auto pb = &b;  // guess what.. How can I know? We ask the compiler througth a compile erroro
   //pointer to a boolean	
// debug(pb);//i call an undefined function that willsend me an informative error
/*/usr/bin/ld: /tmp/cc1KLAQb.o: in function `main':
/home/nd23/aprogramming/advanced_programming_2019-20/lectures/c++/03_more_on_pointers_and_vectors/01_auto.cc:39: undefined reference to `void debug<bool*>(bool*)'
collect2: error: ld returned 1 exit status
make: *** [Makefile:26: 01_auto.x] Error 1
*/  

auto ps = init<double>(11); //pointer to a double
  delete[] ps;
  return 0;
}

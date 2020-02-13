#include <iostream>

template <typename T>
void print_sentinel(const T* a, const std::size_t l);

int main() {
  int a{8}, b{7};
  int* pi{&a};//pointers are variables that point to other variables 
//you can make constant the value of the pointer or also the value that the pointer refers to it

  const int* pc{&a}; //defines a pointer that cannot be changed when dereferenced
	//points to const int
  // *pc = 7; 	// error
  a = 15;  // I can obviously change a

  int* const cp{&a}; //i can change the value to which it points to
			//i cannt change the value of the pointer
  a = b;
  *cp = 33;
  // cp = &b;   // error

  const int* const cpc{&a};  //both cases are here present cant change the value of the referenced ariable or the value of the pointere

  // *cpc = 0;  // error
  // cpc = &b;  // error
  a = 99;

  int aa[4]{1,2,2,1};
  print_sentinel(aa, 4);

  return 0;
}

template <typename T>
void print_sentinel(const T* a, const std::size_t N) {//print values of an array
  const T* const end{a + N};//points to N past the last element of the array//in this case we have  a good candidate for double constant
  for (; a != end; ++a)
    std::cout << *a << std::endl;//I print th first N elements of the array, then i compare the pointers
}

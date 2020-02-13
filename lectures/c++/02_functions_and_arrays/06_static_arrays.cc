#include <iostream>

void surprise(double a[], const std::size_t n) { //size_t stands for long long unsigned integer
  for (auto i = 0llu; i < n; ++i) {  //auto doesnt want curly braces
    a[i] = 77;
  }
}

int main() {
	size_t size;
	std::cout<<"insert partial size";

	std::cin>>size;
   

  int ai[size];
  float af[9];//value is undefined
  ai[0] = 9;    // first element  []subscripting operator
  af[8] = 3.3;  // last element
  ai[88] = 7;   // undefined behavior, no range checking : dont know where we are reading

  for (std::size_t k{0}; k < size; ++k)  //size_t is a nonnegative number,so we avoid negative numbers ,It helps documenting
    std::cout << "ai[" << k << "] = " << ai[k] << '\n';

  std::cout << "\n-------------------------------\n\n";

  for (std::size_t k{0}; k < 9; ++k)
    std::cout << "af[" << k << "] = " << af[k] << '\n';

  std::cout << "\n how is an array in memory?\n\n";

  for (std::size_t k{0}; k < 9; ++k)
    std::cout << "&af[" << k << "] = " << &af[k] << '\n';

  std::cout << "\n-------------------------------\n\n";

  double ad[7]{1.1, 2.2, 3.3};  // syntax to compose an array,it starts with 3 doubles and the rest is set to 0

  *ad = 9.9;  // an array is implicitly converted to    this works as ad[0] = 9.9
  *(ad+1) = 8.8;// a pointer to its first element;      this works as ad[1] = 8.8
  for (std::size_t k{0}; k < 7; ++k)
    std::cout << ad[k] << std::endl;

  // double ad2[2] {1,2,3,4}; // error

  surprise(ad, 7);
  std::cout << "after surprise()" << std::endl;
  for (std::size_t k{0}; k < 7; ++k)
    std::cout << ad[k] << std::endl;   //well the array is changed!! array name is not a normal variable.
				//we point by value an array yet it is passed as a reference

  return 0;
}

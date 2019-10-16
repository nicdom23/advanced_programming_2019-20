#include <array>//new in c++ 11
#include <iostream>

// template <class T, std::size_t N>
// struct array;
 // std::arrays are static arrays that live in the stack
int main() {
  std::array<int, 4> a{1, 2, 3, 4};
  std::array<int, 4> b{a};  // I can copy element-wise from another std::array
                            // this is not possible with plain built-in arrays
				//you copy a into b
  b = a;//still valid syntax to copy
  for (auto x : a)//new in c++11 print each element in a
    std::cout << x << " ";
  std::cout << std::endl;

  for (auto x : b)
    std::cout << x << " ";
  std::cout << std::endl;

  a[0] = 0;  // same subscripting operator without bound checking

  for (const auto x : a)//x is scoped just inside the for loop
    std::cout << x << " ";
  std::cout << std::endl;

  for (const auto x : b)
    std::cout << x << " ";
  std::cout << std::endl;

  for (auto& x : a)//i get a reference for each element
    x *= 10;    //i multiply by 10 each element of a

  for (auto i = 0u; i < a.size(); ++i)//array.size() is unsigned integer
    std::cout << "a[" << i << "] = " << a[i] << std::endl;

  b.at(90);  // bound checking at run-time for element 90//returns the element if 90 is into the bounds //you cant have them in built in arrays,exceot if saintize=adress, that lowers the code.  function .at()

//Faster, better , more performant

  return 0;
}

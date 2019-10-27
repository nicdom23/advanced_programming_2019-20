#include <iostream>

int main() {
  std::cout << "Please insert array lenght: ";
  std::size_t n;
  std::cin >> n;
  int* da{new int[n]};  // allocated on the HEAP, or free-store    //"new" is like malloc of size n 
				//NEW returnd a pointer to first element of memory stack   
			//a big file needs space in the heap, a stack overflow gives a segmentation fault 

  for (std::size_t i{0}; i < n; ++i)
    da[i] = i * 10;

  for (std::size_t i{0}; i < n; ++i)
    std::cout << "da[" << i << "] = " << da[i] << std::endl;

  delete[] da; //memory needs to be deleted
  return 0;
}

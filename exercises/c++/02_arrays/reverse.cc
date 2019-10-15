#include <iostream>
template <typename T>
T * initialize(size_t n){
	T* memory{new T[n]};  
  	for (std::size_t i{0}; i < n; ++i){
    		std::cout << "Please insert next number: ";
  		T numb;
  		std::cin >> numb;
		memory[i] = numb;}
return memory;			
	}
template <typename T>
void reverse_print(size_t n,T * array){
	for (std::size_t i{0}; i < n; ++i){
    	std::cout << "array[" << n-i-1 << "] = " << array[n-i-1] << std::endl;}

}
  	
int main() {
	std::cout << "Please insert array lenght: ";
  std::size_t n;
  std::cin >> n;
	int * array = initialize<int>(n);
  
	reverse_print(n,array);
   

  

  delete[] array; //memory needs to be deleted

	double * double_array = initialize<double>(n);
  
	reverse_print(n,double_array);
   

  

  delete[] double_array;
  return 0;



return 0;
}

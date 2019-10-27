#include <iostream>
int * array_add(int prime, size_t size , int * array);
int main(){
	//since we won't have more than a 100 prime numbers, i initialized a 100 integers long array
	int * array{new int[100]};
	size_t size{0};
	int max_int = 100;
	
	for(int i{2};i<max_int;i++){
		bool flag = true;
		for (int k{2};k<i;k++){
			if (i%k == 0)	
				flag = false;
		}
		if (flag == true){
			array[size] = i;
			size ++;		
		}
	}
		for(size_t i{0};i< size;i++) std::cout << array[i] << " is prime. " << std::endl;
		std::cout<< "size is:" << size << std::endl;
		delete [] array;


//Here is the same file but with an increase of the dynamic memory size
	int * array_2{new int[1]};
	size_t size_2{0};
	
	for(int i{2};i<max_int;i++){
		bool flag = true;
		for (int k{2};k<i;k++){
			if (i%k == 0)	
				flag = false;
		}
		if (flag == true){
			array_2 = array_add(i,size_2,array_2);
			size_2++;
		}
	}
		for(size_t i{0};i< size;i++) std::cout << array_2[i] << " is prime. " << std::endl;
		std::cout<< "size is:" << size << std::endl;
		delete [] array_2;
}
int * array_add(int prime, size_t size , int * array){

		int * new_array{new int[size+1]};		
		for(size_t i{0};i<size;i++)     
			new_array[i]=array[i];  
		new_array[size] = prime;
		delete[] array;
		return new_array;
	}


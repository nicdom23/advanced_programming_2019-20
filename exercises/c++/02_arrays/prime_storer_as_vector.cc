#include <iostream>
#include <vector>
//std::vector vector_add(int prime, size_t size , std::vector vector);
int main(){
	//since we won't have more than a 100 prime numbers, i initialized a 100 integers long array
	std::vector <int> v(100);
	size_t size{0};
	int max_int = 100;
	
	for(int i{2};i<max_int;i++){
		bool flag = true;
		for (int k{2};k<i;k++){
			if (i%k == 0)	
				flag = false;
		}
		if (flag == true){
			v[size] = i;
			size ++;		
		}
	}
		for(size_t i{0};i< size;i++) std::cout << v[i] << " is prime. " << std::endl;
		std::cout<< "size is:" << size << std::endl;


//Here is the same file but with an increase of the dynamic memory size
	std::vector <int> v2;
	size_t size_2{0};
	
	for(int i{2};i<max_int;i++){
		bool flag = true;
		for (int k{2};k<i;k++){
			if (i%k == 0){	
				flag = false;
				break;				
				}
		}
		if (flag == true){	
			//v2.reserve(size_2+1);
			v2.push_back(i);
			std::cout<<"in array is:"<<v2[size_2]<<std::endl;	
			size_2++;
		}
	}
		for(size_t i{0};i< size_2;i++) std::cout << v2[i] << " is prime. " << std::endl;
		std::cout<< "size is:" << size_2 << std::endl;
}
/*std::vector vector_add(int prime, size_t size , std::vector vector){

		std::vector <int> new_vector(size+1)		
		for(size_t i{0};i<size;i++)     
			new_vector[i]=vector[i];  
		new_vector[size] = prime;
	
		return new_vector;
	}
*/

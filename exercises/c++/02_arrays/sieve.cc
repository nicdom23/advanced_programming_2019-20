#include <iostream>
#include <cmath>

int main(){

std::cout<<"insert integer:"<<std::endl;
int n{0};
std::cin >> n;
bool * isPrime{new bool[n+1]};
//for(size_t i{2};i<n;i++)
 //	isPrime[i] = true;

for(size_t i{2};i<std::sqrt(n);i++)
	if(isPrime[i] == true)
		for(size_t j{2*i};j<n;j=j+i)
			isPrime[j] = false;


for(size_t i{2};i<n+1;i++) 
	if(isPrime[i] == true) std::cout << i << std::endl; 

delete[] isPrime;
return 0;
}

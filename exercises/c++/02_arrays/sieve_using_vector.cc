#include <iostream>
#include <cmath>
#include <vector>

int main(){

std::cout<<"insert integer:"<<std::endl;
int n{0};
std::cin >> n;
std::vector <bool> v(n+1);
for(size_t i{2};i<n+1;i++)
	v[i] = true;

for(size_t i{2};i<std::sqrt(n);i++)
	if(v[i] == true)
		for(size_t j{2*i};j<n;j=j+i)
			v[j] = false;


for(size_t i{2};i<n+1;i++) 
	if(v[i] == true) std::cout << i << std::endl; 

return 0;
}

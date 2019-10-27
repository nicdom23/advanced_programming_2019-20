#include <iostream>
#include <vector>

int main(){
std::vector<std::string> v;
std::string line;
std::string ss;
while(std::cin >> ss)
{
bool present = false; 
for (int i{0};i<v.size();i++)
	if(v[i]==ss)
		present = true;	
if(!present)
	v.push_back(ss);
}
for (int i{0};i<v.size();i++)
	std::cout<<v[i]<<" ";
std::cout<<std::endl;
return 0;

}

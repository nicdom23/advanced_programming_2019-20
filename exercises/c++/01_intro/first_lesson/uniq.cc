#include <iostream>
#include <string>
int main(){

std::string s1;	
int size{1};
int first{0}; //this variable is used to skip the first check of the first line

for(std::string line; std::getline(std::cin,line);)
{ 	
		if(first == 0){
			first++;
			}
		else if(s1 == line){
			size++;	
			}
		else if(s1 != line){
			std::cout<< size <<" "<< s1 <<std::endl;
			size = 1;
			}
		
//std::cout<< size <<" "<< line <<std::endl;
s1 = line;
}

//std::string line;
//while(std::getline(std::cin,line))
//{std::cout<<line;}
//for(j = 0;j<size;j++)
//std::cout<<i[j]<<" "<<output[j]<<std::endl;
return 0;
}

#include <iostream>
#include <string.h>

int main() {

std::string s1 = "Geeks";
std::string r = s1.substr(1,1);
std::cout<<"String is:"<< r;
int n{};
std::cout << "Insert lines dimension:";
std::cin >> n;

std::string line;
std::string delimier = " ";
while(std::getline(std::cin,line))
{
 if (line.length()<= n) std::cout<<" "<<line;
 else {
	std::string word{""};
	int counter{};	
        int length{};	
	for (auto x : line)
	{ 
	   if (length == n)
		{		   
			std::cout<<std::endl<<word<<" ";
			word = "";
			length = 0;
		}
		else
		{
 			word = word+x;
			length ++;
		}
		
         }
       }
}



return 0;
}

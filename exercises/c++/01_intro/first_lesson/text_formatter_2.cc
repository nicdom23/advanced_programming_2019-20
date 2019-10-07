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
		
       
       }
}
std::string str = "geeksforgeeks a computer science"; 
    std::string str1 = "geeks"; 
  
    // Find first occurrence of "geeks" 
    size_t found = str.find(str1); 
    if (found != std::string::npos) 
        std::cout << "First occurrence is " << found << std::endl; 
  
    // Find next occurrence of "geeks". Note here we pass 
    // "geeks" as C style string. 
    char arr[] = "geeks"; 
    found = str.find(arr, found+1); 
    if (found != std::string::npos) 
        std::cout << "Next occurrence is " << found << std::endl; 


return 0;
}

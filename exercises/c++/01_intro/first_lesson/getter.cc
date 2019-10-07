#include <iostream>

void getInt();
void getDouble();

int main(){

getInt();
getDouble();
return 0;
}

void getInt(){
int i{};
//for(;;){
std::cout << "Please insert a number!"<< std::endl;
while(!(std::cin >> i))
{
std::cout << "Wrong. Please insert a number!"<< std::endl;
std::cin.clear();
std::cin.ignore();

}
std::cout <<"Correct. Input number is :"<< i << std::endl;
};

void getDouble(){
double i{};
//for(;;){
std::cout << "Please insert a float number!"<< std::endl;
while(!(std::cin >> i))
{
std::cout << "Wrong. Please insert a float number!"<< std::endl;
std::cin.clear();
std::cin.ignore();

}
std::cout <<"Correct. Input number is :"<< i << std::endl;
};

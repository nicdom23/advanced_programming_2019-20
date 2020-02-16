#include <iostream>
#include <functional>
/*
template<typename T , typename U = std::less<T>>
bool f(T a,T b, U u = U())
{
	return u(a,b);
}*/
int main(){


int a = 1;
int b = 2;
std::less<int> op;

std::cout << std::boolalpha;
std::cout << op(2,3)<<std::endl;



}

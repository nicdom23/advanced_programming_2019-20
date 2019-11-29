#include<iostream>
#include "find_if_hardcoded.hpp"
#include <vector>
#include<numeric>
#include <chrono>

template<typename T>
class predicate_template{
T value;//value does not change among two invocations of this function
public:
 bool operator()(const T& x) const noexcept {return x == value}
};

template<class T>
class predicate_virtual: public predicate_base<T>{
T value;
public:
predicate_virtual(const T& x): value{x} {}
bool operator()
}




int main(){
constexpr std::size_t N = 1024*1024*100;
constexpr int target = 99'000'000;//99 million

std::vector<int>v(N);
//iota assigns to each element fills the vector with -1024 -1023 -1024 and so on
std::iota(v.begin(),v.end(),0);
//a class that has a public call operator is called a function object::there will be no function
auto t0 =std::chrono::high_resolution_clock::now();
auto it = find_if_hardcoded(v.begin(),v.end(),target);
auto t1 =std::chrono::high_resolution_clock::now();

std::cout<<"hard coded"<< std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count()<<std::endl;


if(it!=v.end())
std::cout<< "found"<<*it<<"at position"<<std::distance(v.begin(),it)<<std::endl;
//templated version as fast as the hardcoded one



//templated version as with lambda function
	//[capture](arguments){body;}
						//auto in c++ 14 				
it =find_if_template(v.begin(),v.end(),[target](int x){return x == target;}//the compiler does the same thing of defining a function object
//we expecti it to be as fast as the templated and the hardcoded version


//virtual version is much slower for clang there is a call to the function





}

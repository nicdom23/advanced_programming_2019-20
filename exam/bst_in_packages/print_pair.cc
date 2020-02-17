// std::iterator example
#include <iostream>     // std::cout
#include <iterator>     // std::iterator, std::input_iterator_tag
#include <vector>       // std::vector

template<class T>
class Node;

template<class key,class value,typename cmp >
class bst;

/



//custom function to print the content of a pair
template<typename T1,typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1,T2>& x)
{
	os<<x.first<<"_"<<x.second;
	return os;
}




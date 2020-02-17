//*************************************NODE  //first class to include
#include "node.h"

template<class key,class value,typename cmp >
class bst;
//******************************* ITERATORs
#include "iterators.h"
//custom function to print the content of a pair
template<typename T1,typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1,T2>& x)
{
	os<<x.first<<"_"<<x.second;
	return os;
}
#include "bst.h"

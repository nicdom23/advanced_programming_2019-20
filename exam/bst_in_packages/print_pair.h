#ifndef PRINT_PAIR
#define PRINT_PAIR

//custom function to print the content of a pair
template<typename T1,typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1,T2>& x)
{
	os<<x.first<<"_"<<x.second;
	return os;
}

#endif


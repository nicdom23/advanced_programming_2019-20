//this is a ìn header
//like #pragma once
#ifndef __find_if_hardcoded
#define __find_if_hardcoded

template <typename I,typename T>  //iterators, generalizations of pointers
//requires I is Iterator
//*I is of type T

I find_if_hardcoded(I first,const I last,const T& value)//is a value present
{
        //precondition  [first,last) is a valid range first not greater than last

        while (first != last && first != value) ++first;//this is linear search hardcoded  

	return first;
}




template <typename I,typename P> 
I find_if_template(I first,const I last,P predicate)//check for something different;;  Function pointer
{
        //precondition  [first,last) is a valid range first not greater than last

        while (first != last && !predicate(*first)) ++first;

	return first;
}
//we can pass a function , we can pass an object,or a class or a lambda function
//P must be known at compile time
// without relying on templates: i can have a function pointer but i have to obey the signature, but i have to pass a pointer

//
template<typename T>
struct predicate_base{
	virtual bool operator()(const T&) const =0;  //pure virtual: an abstract class::force the user to implement and override the function
};


template <typename I> 
//*I is iterator, is compatible with predicate
I find_if_virual(I first,const I last,const predicate_base<T>& predicate)//check for something different;;  Function pointer
{
        //precondition  [first,last) is a valid range first not greater than last

        while (first != last && !predicate(*first)) ++first;

	return first;
}



//inherits the predicate base



#endif

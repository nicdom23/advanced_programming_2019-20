#ifndef header
#define header
#include <iostream>     // std::cout
#include <iterator>     // std::iterator, std::input_iterator_tag
#include <vector>       // std::vector
#endif

#ifdef NODE
#define NODE
#include "node.h"
#endif


//*************************************NODE

template<class T>
class Node{
/**
	A node for the class bst
*/
	T value;
	Node<T>* left;
	Node<T>* right;
	Node<T>* parent;
public:
	//custom constructor
	Node(T element)
	:value{element},left{nullptr},right{nullptr},parent{nullptr}{}

	//default destructor
	//~Node()=default;

	//friend classes that can access node parameters
	template<class key,class value,typename cmp>
	friend class bst;

	template<class S>
	friend class MyIterator;

	template<class S>
	friend class const_MyIterator;

	//friend function to print the content of the node
	/*friend
	std::ostream& operator<<(std::ostream& os, const Node<T>& x){
		os<<x.value;
		return os;
	}*/
};

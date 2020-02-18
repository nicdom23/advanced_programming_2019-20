#ifndef NODE_H
#define NODE_H

//*************************************NODE

template<class T>
class Node{
/**
	A node for the class bst
*/
	
	Node<T>* left;
	Node<T>* right;
	Node<T>* parent;
	
public:
	T value;

private:
	//custom constructor
	explicit Node<T>(T element)
	:left{nullptr},right{nullptr},parent{nullptr},value{element}{}
public:
	
	//default destructor
	//~Node();

	//friend classes that can access node parameters
	template<class key,class value,typename cmp>
	friend class bst;

	template<class S>
	friend class MyIterator;

	template<class S>
	friend class const_MyIterator;

	//friend function to print the content of the node
	friend
	std::ostream& operator<<(std::ostream& os, const Node<T>& x){
		os<<x.value;
		return os;
	}
};

#endif

#ifndef headers

#include <iostream>     // std::cout
#include <iterator>     // std::iterator, std::input_iterator_tag
#include <vector>       // std::vector

#endif


//*******************************NORMAL ITERATOR
template<class T>
class MyIterator : public std::iterator<std::forward_iterator_tag, Node<T>>
{/**
	Regular iterator for the class bst
 */
  	Node<T>* pointer;
  	Node<T>* last;//pointer to the last element of the bst, to recognize when to return nullptr(!!!!!!THIS COULD BE A SOURCE OF PROBLEM!!!!!!BECAUSE THE ITERATOR IS NOT UPDATED WHEN THE LAST ELEMENT OF THE TREE WALK CHANGES)
public:
	//custom constructor  	
	MyIterator(Node<T>* x,Node<T>* last_element);
	//copy constructor
	MyIterator(const MyIterator<T>& mit) ;
	//copy assignment
	MyIterator& operator=(const MyIterator& x);
	//++
  	MyIterator& operator++();
	

	//==
	bool operator==(const MyIterator& rhs)const;
	//!=  
	bool operator!=(const MyIterator& rhs) const;
  	//dereferencing operator
	Node<T>& operator*();

//*******************CONST ITERATOR
template<class T>
class const_MyIterator : public std::iterator<std::forward_iterator_tag, const Node<T>>
{/**
	const_iterator for class bst
 */
  	Node<T>* pointer;//pointer to the pointed node
  	Node<T>* last;//pointer to the last element of the bst, to recognize when to return nullptr(!!!!!!THIS COULD BE A SOURCE OF PROBLEM!!!!!!BECAUSE THE ITERATOR IS NOT UPDATED WHEN THE LAST ELEMENT OF THE TREE WALK CHANGES)
public:
	//custom constructor  	
	const_MyIterator(Node<T>* x,Node<T>* last_element) ;
	//copy constructor  	
	const_MyIterator(const const_MyIterator<T>& mit) ;
	//copy assinment
	const_MyIterator& operator=(const const_MyIterator& x){
		pointer = x.pointer;
		last = x.last;
		return *this;	
	}
	//++
  	const_MyIterator& operator++() ;

  	//==
  	bool operator==(const const_MyIterator& rhs) const ;
	//!=  	
	bool operator!=(const const_MyIterator& rhs) const ;
	//dereferencing operator  	
	const Node<T>& operator*() ;//HERE IS THE DIFFERENCE	
};

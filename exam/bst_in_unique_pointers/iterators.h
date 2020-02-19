#ifndef ITERATORS
#define ITERATORS


//*******************************BASE ITERATOR
template<class type>
class BaseIterator : public std::iterator<std::forward_iterator_tag, type>
{/**
	Regular iterator for the class bst
 */
public:
  	type* pointer;//pointer to the pointed node
  	type* last;//pointer to the last element of the bst, to recognize when to return nullptr(!!!!!!THIS COULD BE A SOURCE OF PROBLEM!!!!!!BECAUSE THE ITERATOR IS NOT UPDATED WHEN THE LAST ELEMENT OF THE TREE WALK CHANGES)

	//custom constructor  	
	BaseIterator(type* x,type* last_element)noexcept :pointer(x),last{last_element} {}
  	
	//copy constructor
	BaseIterator(const BaseIterator& mit)noexcept : pointer(mit.pointer), last{mit.last} {}

	//copy assignment
	BaseIterator& operator=(const BaseIterator& x) noexcept{
		pointer = x.pointer;
		last = x.last;
		return *this;	
	}


	//++
  	BaseIterator& operator++() noexcept{
	
		if(pointer == last) {//this was an implementation that I found online and that seemed sensible enough
			pointer = nullptr;
        		return *this;
		}
		if (pointer->right != nullptr){
			
			pointer = (pointer->right).get();
                        while (pointer->left != nullptr)
				pointer = (pointer->left).get();
			return *this;
		}

		type* y = (pointer->parent).get();
		while(y != nullptr && pointer == (y->right).get()){
			pointer = y;
			y = (y->parent).get();
			}
		pointer = y;
		return *this;
	}

	//==
	bool operator==(const BaseIterator& rhs) const {return pointer==rhs.pointer;}
	//!=  
	bool operator!=(const BaseIterator& rhs) const {return pointer!=rhs.pointer;}
  	//dereferencing operator
	//We defined it below	
};


//***********************NORMAL ITERATOR
template <typename T>
class MyIterator : public BaseIterator<Node<T>>{
/**
	regular iterator for class bst
*/
public:
MyIterator(Node<T>* a, Node<T>* b): BaseIterator<Node<T>>{a,b} {}
Node<T>& operator*() {return *BaseIterator<Node<T>>::pointer;}

};

//*******************CONST ITERATOR
template <typename T>
class const_MyIterator : public BaseIterator<Node<T>>{
/**
	const_iterator for class bst
*/
public:
const_MyIterator(Node<T>* a, Node<T>* b): BaseIterator<Node<T>>{a,b} {}

const Node<T>& operator*() {return *BaseIterator<Node<T>>::pointer;}
};

	
#endif

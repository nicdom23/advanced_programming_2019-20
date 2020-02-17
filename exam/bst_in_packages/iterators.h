#ifndef ITERATORS
#define ITERATORS


//*******************************NORMAL ITERATOR
template<class T>
class MyIterator : public std::iterator<std::forward_iterator_tag, Node<T>>
{/**
	Regular iterator for the class bst
 */
  	Node<T>* pointer;
  	Node<T>* last;
public:
	//custom constructor  	
	MyIterator(Node<T>* x,Node<T>* last_element) :pointer(x),last{last_element} {}
  	
	//copy constructor
	MyIterator(const MyIterator<T>& mit) : pointer(mit.pointer), last{mit.last} {}

	//copy assignment
	MyIterator& operator=(const MyIterator& x){
		pointer = x.pointer;
		last = x.last;
		return *this;	
	}


	//++
  	MyIterator& operator++() {
	
		if(pointer == last) {
			pointer = nullptr;
        		return *this;
		}
		if (pointer->right != nullptr){
			
			pointer = pointer->right;
                        while (pointer->left != nullptr)
				pointer = pointer->left;
			return *this;
		}

		Node<T>* y = pointer->parent;
		while(y != nullptr && pointer == y->right){
			pointer = y;
			y = y->parent;
			}
		pointer = y;
		return *this;
	}

	//==
	bool operator==(const MyIterator& rhs) const {return pointer==rhs.pointer;}
	//!=  
	bool operator!=(const MyIterator& rhs) const {return pointer!=rhs.pointer;}
  	//dereferencing operator
	Node<T>& operator*() {return *pointer;}	
};

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
	const_MyIterator(Node<T>* x,Node<T>* last_element) :pointer(x),last{last_element} {}
	//copy constructor  	
	const_MyIterator(const const_MyIterator<T>& mit) : pointer(mit.pointer), last{mit.last} {}
	//copy assinment
	const_MyIterator& operator=(const const_MyIterator& x){
		pointer = x.pointer;
		last = x.last;
		return *this;	
	}
	//++
  	const_MyIterator& operator++() {
		if(pointer == last) {//here we use the knowledge of last(I THINK I FOUND THIS IMPLEMENTATION ONLINE, AND I JUST TOOK THE IDEA I GUESS ... -_- )
			pointer = nullptr;
        		return *this;
		}
		if (pointer->right != nullptr){
			pointer = pointer->right;
                        while (pointer->left != nullptr)
				pointer = pointer->left;
			return *this;
			}
		Node<T>* y = pointer->parent;
		while(y != nullptr && pointer == y->right){
			pointer = y;
			y = y->parent;
		}
		pointer = y;
		return *this;
	}

  	//==
  	bool operator==(const const_MyIterator& rhs) const {return pointer==rhs.pointer;}
	//!=  	
	bool operator!=(const const_MyIterator& rhs) const {return pointer!=rhs.pointer;}
	//dereferencing operator  	
	const Node<T>& operator*() {return *pointer;}//HERE IS THE DIFFERENCE	
};
#endif

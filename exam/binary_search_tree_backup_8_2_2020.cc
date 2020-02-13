#include <iostream>
#include <cassert>
#include <string>

template<typename kT,typename vT,typename cmp>
class bst;



template<typename T>
class Node{
private:
	Node<T>* left_child;
	Node<T>* right_child;
	Node<T>* parent;
	T value;
 public:
	Node(Node<T>* parent, Node<T>* left, Node<T>* right, T element)
	: parent{parent}, left_child{left}, right_child{right},value{element} {std::cout <<"node created"<<std::endl;}
Node(T element)
: parent{nullptr}, left_child{nullptr}, right_child{nullptr},value{element} {std::cout <<"first node created"<<std::endl;}
	~Node() = default;
    
    template<typename kT,typename vT,typename cmp>
    friend class bst;
    friend class iterator;
    friend class const_iterator;
};
template<typename T>
class iterator{
T* current;

iterator{T* pointed_element}
:current{pointed_element}  {}

void operator++(const iterator<T>);
//here it has to move to the next pointer according to the wanted order

};
class const_iterator{};


template<typename kT,typename vT,typename cmp = std::less<kT>>
class bst{
using pair_type = std::pair<const kT,vT>;
private:
Node<pair_type>* root;

public://let's see what functions we need to implement
//constructor destructor and copy and move semantics

bst()//creates an empy tree
:root{nullptr}{std::cout<<"bst created"<<std::endl;}

~bst()=default;

bst(const bst& a);//copy constructor
bst& operator=(const bst & a);//copy assignment

bst(bst&& a) noexcept;//move constructor
bst& operator=(bst&& a) noexcept;//move assignment




//insert a new element and return an iterator pointing at the element with the same key: bool is true if a new node has been allocated
std::pair<iterator, bool> insert(const pair_type& x){


}
std::pair<iterator, bool> insert(pair_type&& x);

//ADD EMPLACE

//clears the content of the tree
void clear();

//returns the begin iterator
iterator begin();
const_iterator begin() const;
const_iterator cbegin() const;

//returns the end iterator
iterator end();
const_iterator end() const;
const_iterator cend() const;

iterator find(const kT& x);
const_iterator find(const kT& x) const;

//balances the tree
void balance();


//Returns a reference to the value that is mapped to a key equivalent to x , performing an insertion if such key does not already exist.
	vT& operator[](const kT& x);
	vT& operator[](kT&& x);

	friend//implement it into the function(print the tree as a sequence of ordered elements)
	std::ostream& operator<<(std::ostream& os, const bst& x){
	return os;
	}

	void erase(const kT& x);


};

int main(){
//test of std::pair
using treepair = std::pair<int,std::string>;
treepair pair{4,"thomas"};
std::cout<< pair.first<<" "<<pair.second<<std::endl;

using BST = bst<int,std::string>;
BST b_s_t = BST{};
 
Node<treepair> node(pair);
Node<treepair> secondnode(&node, nullptr, nullptr,pair);
//Node<treepair>* test_node = &node;
}

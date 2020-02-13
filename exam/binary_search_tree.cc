#include <iostream>
#include <cassert>
#include <string>
#include <iterator>     // std::iterator, std::input_iterator_tag
template<typename T>
class Node;

template<typename kT,typename vT,typename cmp>
class bst;

template <typename T>
class iterator ;

////////////////////////////////NODE
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
    //template<T>
    friend class iterator<T>;
    //friend class const_iterator;
};
/****************/
////////////////////////ITERATOR
template <typename T>
class iterator : public std::iterator<std::forward_iterator_tag, Node<T>>
{
  Node<T>* p;
public:
  iterator<T>(Node<T>* x) //regular constructor from pointer
  :p(x) {}
  iterator<T>(const iterator<T>& mit) //copy constructor
  : p(mit.p) {}

  iterator<T>& operator++() //next constructor
  {
   if (p->right_child != nullptr)
		return tree_minimum(p->right_child);
   iterator<T> y = p->parent;
   while  (y !=nullptr && p == y->right_child)
   {
   	p=y;
	y = y->parent;
   }
   return y;
  }
  
  /*
  iterator<T> operator++(int) 
  {
   iterator<T> tmp(*this); 
   operator++(); 
   return tmp;
   }
  */
  bool operator==(const iterator& rhs) const {return p==rhs.p;}
  bool operator!=(const iterator& rhs) const {return p!=rhs.p;}
  int& operator*() {return *p;}
};



/************/
/*
template<typename T>
class iterator{
T* current;

iterator{T* pointed_element}
:current{pointed_element}  {}

void operator++(const iterator<T>);
//here it has to move to the next pointer according to the wanted order

};
*/

class const_iterator{};


template<typename kT,typename vT,typename cmp = std::less<kT>>
class bst{
using pair_type = std::pair<const kT,vT>;
private:
Node<pair_type>* root;

//template <T>
//void debug(T value);

iterator<pair_type> tree_minimum(const Node<pair_type>* x)
{

while (x->left_child != nullptr)
	x = x->left_child;
return x;
}

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
std::pair<iterator<pair_type>, bool> insert(const pair_type& x){
	
	Node<pair_type>* newnode = new Node<pair_type>(x);
	Node<pair_type>* y = nullptr;
	Node<pair_type>* z = root;
	while (z != nullptr)
	{
	   y = z;
	   if(newnode->value.first < z->value.first)
		z = z->left_child;
           else z = z->right_child;
	}
	newnode->parent = y;
	if (y ==nullptr)
		root = newnode; //tree was empty
	else if (newnode->value.first < y->value.first)
		y->left_child = newnode;
	else y->right_child = newnode;
	return std::pair<iterator<pair_type>,bool>{nullptr, true};
}
std::pair<iterator<pair_type>, bool> insert(pair_type&& x)
{
    return std::pair<iterator<pair_type>,bool>{nullptr, true};
}

//ADD EMPLACE

//clears the content of the tree
void clear();

//returns the begin iterator
iterator<pair_type> begin()
{
std::cout << "begin_used";
iterator<pair_type> x= root;
return tree_minimum(root);
}
//const_iterator begin() const;
const_iterator cbegin() const;

//returns the end iterator
iterator<pair_type> end()
{
 return nullptr;
}
//const_iterator end() const;
const_iterator cend() const;

iterator<pair_type> find(const kT& x);
const_iterator find(const kT& x) const;

//balances the tree
void balance();


//Returns a reference to the value that is mapped to a key equivalent to x , performing an insertion if such key does not already exist.
	vT& operator[](const kT& x);
	vT& operator[](kT&& x);

	friend//implement it into the function(print the tree as a sequence of ordered elements)
	std::ostream& operator<<(std::ostream& os, const bst& x){
	for(iterator<pair_type> i = x.begin(); i != x.end(); ++i)
		os << *i << " ";
        os <<std::endl;
        return os;
	}

	void erase(const kT& x);


};

int main(){
//using treepair = std::pair<int,std::string>;

//test of std::pair
//treepair pair{4,"thomas"};
//std::cout<< pair.first<<" "<<pair.second<<std::endl;
//******************
/*
treepair pairA{5,"thomas"};
treepair pairB{22,"alice"};
treepair pairC{4,"timothy"};
treepair pairD{74,"vincent"};
treepair pairE{9,"Isabelle"};
using BST = bst<int,std::string>;
BST b_s_t = BST{};//created bst

b_s_t.insert(pairA);*/
using treepair = std::pair<const int,int>;

treepair pairA{5,44};
treepair pairB{22,44};
treepair pairC{4,44};
treepair pairD{74,44};
treepair pairE{9,44};
using BST = bst<const int,int>;
BST b_s_t = BST{};//created bst

b_s_t.insert(pairA);
b_s_t.insert(pairB);
b_s_t.insert(pairC);
b_s_t.insert(pairD);
b_s_t.insert(pairE);

iterator<treepair> start = b_s_t.begin();
iterator<treepair> finale = b_s_t.end();




std::cout << b_s_t ;
//Node<treepair> node(pair);
//Node<treepair> secondnode(&node, nullptr, nullptr,pair);
//Node<treepair>* test_node = &node;
}

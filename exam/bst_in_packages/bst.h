#ifndef headers

#include <iostream>     // std::cout
#include <iterator>     // std::iterator, std::input_iterator_tag
#include <vector>       // std::vector

#endif


/////////////BINARY SEARCH TREE CLASS

template<class key,class value,typename cmp = std::less<key>>
class bst{
/**
	Class that implements a binary search tree, as described in the book "Introduction to algorithms" by Cormen,Leiserson,Rivest,Stein; chapter 12 pages 286 to 298
*/
	using treepair = std::pair<key,value>;//pair used in tree
	
	cmp op;//this is the comparison operator

	Node<treepair>* root;//pointer to the root node


public:
	//custom creator
	bst();

//************copy semantics
	//copy constructor -- deep copy
	bst(const bst& bintree);
  	// copy assignment -- deep copy
	bst& operator=(const bst& bintree);
	
	//accessory function to perform the deep-copy
	void copy_part(Node<treepair>* x);


//**************************MOVE SEMANTICS(done as default)
	//move constructor
	bst(bst&& bintree);
	// move assignment
 	bst& operator=(bst&& bintree);
//**************************TREE MIN and TREE MAX


 Node<treepair>* tree_minimum( Node<treepair>* y) const;
/**
	Accessory function that finds the most left sided node of tree that has the argument as a root
	(The first one in the tree walk)		
*/
	

Node<treepair>* tree_maximum(Node<treepair>* y) const;
/**
	Accessory function to find the most right sided node of the tree that has the argument as the root node
	(The last one in the tree walk)
*/
	

Node<treepair>* tree_minimum() const{
/**
	when called with no argument tree_minimum finds the most left sided node of the whole bst
*/	
	Node<treepair>* root_node{root};
	//check if applied on an empty bst	
	if (isEmpty()) return nullptr;
	return tree_minimum(root_node);
}


Node<treepair>* tree_maximum() const;
/**
	when called with no argument tree_maximum finds the most right sided node of the whole bst
*/	


//*********************BEGIN AND END

MyIterator<treepair> begin();
/**
	retuns a regular iterator pointing at the first element of the tree walk
*/
	
  
const_MyIterator<treepair> begin() const;
/**
	retuns a cons_iterator pointing at the first element of the tree walk
*/



const_MyIterator<treepair> cbegin() const;
/**
	retuns a cons_iterator pointing at the first element of the tree walk
*/





MyIterator<treepair> end();
/**
	retuns a regular iterator pointing at the past-the-last-element of the tree walk
*/
	


const_MyIterator<treepair> end() const;
/**
	retuns a cons_iterator pointing at the past-the-last-element of the tree walk
*/
	


const_MyIterator<treepair> cend() const;
/**
	retuns a cons_iterator pointing at the past-the-last-element of the tree walk
*/



//**************************INSERTION
std::pair<MyIterator<treepair>,bool> insert(const treepair& z);
/**
	Inserts a new element of the type treepair into the bst. It works with lvalues.
	-If the key is not present it creates a new node and inserts it into the bst keeping intact the binary-search-tree property then it just returns am std::pair containing an iterator to the new node and a boolean saying "true"	
	- If the key is already present it just returns an iterator to that element and a boolean saying "false"

*/

	
	


std::pair<MyIterator<treepair>,bool> insert(treepair&& z);
/**
	Inserts a new element of the type treepair into the bst. It works with rvalues.
	-If the key is not present it creates a new node and inserts it into the bst keeping intact the binary-search-tree property then it just returns am std::pair containing an iterator to the new node and a boolean saying "true"	
	- If the key is already present it just returns an iterator to that element and a boolean saying "false"
	The code is the same as the above example
*/

//**********************************EMPLACE
template< class... Types >//could launch an exception
std::pair<MyIterator<treepair>,bool> emplace(Types&&... args);


//***********************************FIND

MyIterator<treepair> find(const key& x);
/**
	Finds the element whose key is the given argument
	Returns a regular iterator pointing to that element
*/



MyIterator<treepair> tree_search(Node<treepair>* x, const key& y);
/**
	Accessory function that performs the bt search exploiting the binary-search-tree property
	Returns a regular iterator
*/	

	



const_MyIterator<treepair> find(const key& x) const;
/**
	Finds the element whose key is the given argument
	Returns a const_iterator pointing to that element
*/




const_MyIterator<treepair> tree_search(Node<treepair>* x, const key& y) const;
/**
	Accessory function that performs the bt search exploiting the binary-search-tree property
	Returns a const_iterator
*/
	


//****************************DELETE

void transplant(Node<treepair>* a, Node<treepair>* b);
/**
	Accessory function that serves to rearreange the nodes before and after deletion
	a 's place is exchanged with b's place
*/
 
	

void erase(const key& x);
/**
	Removes the element from the tree with the corresponding key. If the key is not present nothing is done.
	The removal leaves the binary-search-tree property intact. The space in the memory is freed

*/
	

//****************************CLEAR
void clear();
/**
	Clears and empties the whole tree. Leaves an empty tree.
*/
	

void clear_part(Node<treepair>* x);
/**
	Accessory function that sweeps the whole tree and deletes all the nodes
*/
	
bool isEmpty() const;
/**
	Checks if the bst is empty
*/

//***********************SUBSCRIPTING OPERATOR
value& operator[](const key& x);
/**
	Returns the value of a pair given the key as an argument.Works with lvalues
	If the key is not present, it inserts a new pair with the inputted key and a default conostructed value(since it has not been specified what to insert)
*/



value& operator[](key&& x);
/**
	Returns the value of a pair given the key as an argument. Works with rvalues.
	If the key is not present, it inserts a new pair with the inputted key and a default conostructed value(since it has not been specified what to insert)

	It just calls the lvalue function
*/

//************************************************BALANCE
void balance();
/**
	Reshapes the bst to become balanced

*/
	

void balance_recursion(std::vector<Node<treepair>> to_split);
/**
	Accessory function to fill the binary search tree in a balanced fashion

*/
//************************SIZE
size_t size() const;
/**
	Returns the size of the bst
*/	

//************************************************* PRINT

friend
std::ostream& operator<<(std::ostream& os,const bst& x);
/**
	Prints the bst in tree walk order
*/

};//END OF CLASS BST


// std::iterator example
#include <iostream>     // std::cout
#include <iterator>     // std::iterator, std::input_iterator_tag
#include <vector>       // std::vector

//*************************************NODE  //first class to include

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
	~Node()=default;

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

template<class key,class value,typename cmp >
class bst;

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



//custom function to print the content of a pair
template<typename T1,typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1,T2>& x)
{
	os<<x.first<<"_"<<x.second;
	return os;
}

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
	bst()
	:root{nullptr} {std::cout<<"binary tree created"<<std::endl;}

//************copy semantics
	//copy constructor -- deep copy
	bst(const bst& bintree)
	:root{new Node<treepair>{bintree.root->value}} {
		copy_part(bintree.root);//calls a recursive function that fills the new bst	
	} 

  	// copy assignment -- deep copy
	bst& operator=(const bst& bintree){
		if(&bintree == this)//check for self reference
        	    return *this;
		clear();//empties the lhs bst	
		insert(bintree.root->value);//inserts the root of the bst to copy
		copy_part(bintree.root);//calls a recursive function that fills the new bst	
		return *this;
	}
	
	//accessory function to perform the deep-copy
	void copy_part(Node<treepair>* x){
		//inserts first the left children of the node and all its children
		if(x->left!=nullptr){
			insert(x->left->value);		
		        copy_part(x->left);//recusive call
		}
		//and then inserts the right children of the node and all its children
		if(x->right!=nullptr){
			insert(x->right->value);		
		        copy_part(x->right);//recursive call
		}
	}



	//**************************MOVE SEMANTICS(done as default)
	//move constructor
	bst(bst&& bintree) : root{std::move(bintree.root)}{}
	// move assignment
 	bst& operator=(bst&& bintree) {
    		root = std::move(bintree.root);
   		return *this;
  	}

//**************************TREE MIN and TREE MAX


 Node<treepair>* tree_minimum( Node<treepair>* y) const{
/**
	Accessory function that finds the most left sided node of tree that has the argument as a root
	(The first one in the tree walk)		
*/
	//check if the argument is nullptr	
	if (y == nullptr ) return y;	

	Node<treepair>* x = nullptr;
	//check if argument has left child
	if(y->left!=nullptr)
		x = y->left;
	else return y;//else the argument is the most left sided node	
	
	//now we find the most left sided node
	while (x->left != nullptr)
	{
		x = x->left;		
	}	
	return x;//return the found node
}


Node<treepair>* tree_maximum(Node<treepair>* y) const{
/**
	Accessory function to find the most right sided node of the tree that has the argument as the root node
	(The last one in the tree walk)
*/
	//check if the argument is nullptr
	if (y == nullptr ) return y;

	Node<treepair>* x = nullptr;
	
	//check if the argument has right child	
	if(y->right!=nullptr)
		 x= y->right;
	else return y;//else the argument is the most right sided node		
	
	//now we find the most right sided node
	while (x->right != nullptr){
		x = x->right;
	}
	return x;//we return the found node
}

Node<treepair>* tree_minimum() const{
/**
	when called with no argument tree_minimum finds the most left sided node of the whole bst
*/	
	Node<treepair>* root_node{root};
	//check if applied on an empty bst	
	if (isEmpty()) return nullptr;
	return tree_minimum(root_node);
}


Node<treepair>* tree_maximum() const{
/**
	when called with no argument tree_maximum finds the most right sided node of the whole bst
*/	
	Node<treepair>* root_node{root};
	//check if applied on an empty bst
	if (isEmpty()) return nullptr;
	return tree_maximum(root_node);
}

//*********************BEGIN AND END

MyIterator<treepair> begin(){
/**
	retuns a regular iterator pointing at the first element of the tree walk
*/
	return MyIterator<treepair>{tree_minimum(),tree_maximum()};
}
  
const_MyIterator<treepair> begin() const{
/**
	retuns a cons_iterator pointing at the first element of the tree walk
*/
	return const_MyIterator<treepair>{tree_minimum(),tree_maximum()};
}


const_MyIterator<treepair> cbegin() const{
/**
	retuns a cons_iterator pointing at the first element of the tree walk
*/
	return const_MyIterator<treepair>{tree_minimum(),tree_maximum()};
}




MyIterator<treepair> end(){
/**
	retuns a regular iterator pointing at the past-the-last-element of the tree walk
*/
	return MyIterator<treepair>{nullptr,tree_maximum()};

}


const_MyIterator<treepair> end() const{
/**
	retuns a cons_iterator pointing at the past-the-last-element of the tree walk
*/
	return const_MyIterator<treepair>{nullptr,tree_maximum()};
}


const_MyIterator<treepair> cend() const{
/**
	retuns a cons_iterator pointing at the past-the-last-element of the tree walk
*/
	return const_MyIterator<treepair>{nullptr,tree_maximum()};
}


//**************************INSERTION
std::pair<MyIterator<treepair>,bool> insert(const treepair& z){
/**
	Inserts a new element of the type treepair into the bst. It works with lvalues.
	-If the key is not present it creates a new node and inserts it into the bst keeping intact the binary-search-tree property then it just returns am std::pair containing an iterator to the new node and a boolean saying "true"	
	- If the key is already present it just returns an iterator to that element and a boolean saying "false"

*/

	MyIterator<treepair> found = find(z.first);//searches for the key

	if(found !=end()){//if it is already present
	 	std::pair<MyIterator<treepair>,bool> x{found,false};//creates the output pair
 		return x;//returns the wanted pair
	}
	//else creates a new node and inserts it
	Node<treepair>* newnode_z = new Node<treepair>{z};
	
	if(isEmpty())//empty tree
	{	
		root = newnode_z;//inserted node is the root
		MyIterator<treepair> x_root {root,root};//creates the pointer to the root
		std::pair<MyIterator<treepair>,bool> to_return ={x_root,true};//creates the output pair
        	return to_return;//returns the wanted pair
	}
	//**
	//We apply the algorithm from the book
	//**
	Node<treepair>* y = nullptr;//this will be the parent of x
	Node<treepair>*	x = root;//this will be one of the children of y
	while(x != nullptr){//until we find an empty space
		y = x;
		if (op((*newnode_z).value.first,(*x).value.first))//here we apply the operator on the key of the element to insert and the key of the element we are inspecting
			x = (*x).left;
		else x= (*x).right;
		}
	(*newnode_z).parent = y; //so y is the parent of the new node
	
	if (y == nullptr){
		root = newnode_z;
		}
	else if(op(   (*newnode_z).value.first,(*y).value.first  ))//key check using the comparison operator		
		(*y).left = newnode_z;//now we identify the correct position of the new node accordingly to the parent
	else (*y).right = newnode_z;
	//Now we have to return the iterator to the node we inserted
	MyIterator<treepair> x_ret{newnode_z,tree_maximum()};//create iterator
	std::pair<MyIterator<treepair>,bool> to_return ={x_ret,true};//create pair
        return to_return;//return pair
}


std::pair<MyIterator<treepair>,bool> insert(treepair&& z){
/**
	Inserts a new element of the type treepair into the bst. It works with rvalues.
	-If the key is not present it creates a new node and inserts it into the bst keeping intact the binary-search-tree property then it just returns am std::pair containing an iterator to the new node and a boolean saying "true"	
	- If the key is already present it just returns an iterator to that element and a boolean saying "false"
	The code is the same as the above example
*/
	return insert(z);//it just invokes the lvalue function

}


//**********************************EMPLACE
template< class... Types >
std::pair<MyIterator<treepair>,bool> emplace(Types&&... args){
treepair newelement{args...};
std::pair<MyIterator<treepair>,bool> x = insert(newelement);
return x;
}
//***********************************FIND

MyIterator<treepair> find(const key& x){
/**
	Finds the element whose key is the given argument
	Returns a regular iterator pointing to that element
*/
	return tree_search(root,x);	
}


MyIterator<treepair> tree_search(Node<treepair>* x, const key& y){
/**
	Accessory function that performs the bt search exploiting the binary-search-tree property
	Returns a regular iterator
*/	

	if(x == nullptr)//element not found,we have reached a dead end
	{
		return end();
	}
	else if ( !op(y,x->value.first)&&!op(x->value.first,y))//equality among the comparison operators, if true the element is found
	{
		MyIterator<treepair> i{x,tree_maximum()};
		return i;
	}
	
	//element yet to be found, here the keys are compared and the wanted left or right sub-tree is choosen
	if(op(y , x->value.first) )
		return tree_search(x->left,y);
	else 
		return tree_search(x->right,y);
}



const_MyIterator<treepair> find(const key& x) const
{
/**
	Finds the element whose key is the given argument
	Returns a const_iterator pointing to that element
*/
	return tree_search(root,x);	
}



const_MyIterator<treepair> tree_search(Node<treepair>* x, const key& y) const{
/**
	Accessory function that performs the bt search exploiting the binary-search-tree property
	Returns a const_iterator
*/
	if(x == nullptr)//element not found, we have reached a dead end
	{
		return end();
	}
	else if ( !op(y,x->value.first)&&!op(x->value.first,y))//equality among the comparison operators, if true the element is found
	{
		const_MyIterator<treepair> i{x,tree_maximum()};
		return i;
	}

	//element yet to be found, here the keys are compared and the wanted left or right sub-tree is choosen
	if(op(y , x->value.first)) 
		return tree_search(x->left,y);
	else	
		return tree_search(x->right,y);
}


//****************************DELETE

void transplant(Node<treepair>* a, Node<treepair>* b){
/**
	Accessory function that serves to rearreange the nodes before and after deletion
	a 's place is exchanged with b's place
*/
 
	if (a->parent == nullptr)//a is the root, then b becomes the root
		root = b;
	
	else if (a == a->parent->left)//a is noot the root, a is the left child of his parent
		a->parent->left = b;//then b becomes the new left child of a's parent
	
	else a->parent->right = b;//else b becomes the new right child of a's parent
	
	if (b != nullptr)
		b->parent = a->parent; //if b is an actual node, then b's parent becomes a's parent
}

void erase(const key& x){
/**
	Removes the element from the tree with the corresponding key. If the key is not present nothing is done.
	The removal leaves the binary-search-tree property intact.

*/
	MyIterator<treepair> to_remove = find(x);//finds the element to remove, if present
	Node<treepair>* remove = &(*to_remove);//we change the type of the element to remove from iterator to regular pointer;

	if (remove == nullptr)//The key has not been found
	{
		std::cout<<"Key not found"<<std::endl;
		return;//nothing is done
	}
	
	if (remove->left == nullptr){//first case, the node to remove doesn't have a left child
		transplant(remove,remove->right);//just attach the right child to the parent(if it's nullpointer then the node to remove has no children and is just deleted)
	}
	else if (remove->right == nullptr){//second case, the node to remove doesn't have a right child
		transplant(remove,remove->left);//just attach the left child to the parent
	}
	else{//third case, the node to remove has both left and right child
		//we find the node with the smallest key in the right subtree of the node to remove
		Node<treepair>* y_ = tree_minimum(remove->right);
		
		if(y_->parent != remove){//this handles the harder case when the node we found above is not the direct child of the node to delete: in practice we turn that node INTO the direct child of the node to delete while assuring the binary-search-tree property
			transplant(y_,y_->right);
			y_->right = remove->right;
			y_->right->parent = y_;
			}

		transplant(remove,y_);//we swap the node to remove and its direct child(which is its right child)
		
		y_->left=remove->left; //the left child and its subtree is inherited without changes
		y_->left->parent= y_; //we adjust the left child of the node to remove with its new parent
		
	}
	delete remove;//we delete the node we removed to free the memory

}

//****************************CLEAR
void clear(){
/**
	Clears and empties the whole tree. Leaves an empty tree.
*/
	clear_part(root);
	root = nullptr;//ensures that there is no root
}

void clear_part(Node<treepair>* x){
/**
	Accessory function that sweeps the whole tree and deletes all the nodes
*/
	if(x != nullptr){
		clear_part(x->left);
		clear_part(x->right);
		delete x;
	}
}

bool isEmpty() const{//NOT TESTED; CAN BE INSERTED INSIDE THE PREVIOUS FUNCTIONS TO PREVENT CODE DUPLICATION
/**
	Checks if the bst is empty
*/
	return root == nullptr;
}
//***********************SUBSCRIPTING OPERATOR
value& operator[](const key& x){
/**
	Returns the value of a pair given the key as an argument.Works with lvalues
	If the key is not present, it inserts a new pair with the inputted key and a default conostructed value(since it has not been specified what to insert)
*/

	value newitem = value{};//create default new value
	treepair newpair = treepair{x,newitem};//create new pair to insert		
	std::pair<MyIterator<treepair>,bool> v = insert(newpair);//we insert the new pair anyway. If the key is already present nothing will happen and the output will still be a valid iterator
	return (*(v.first)).value.second;//returns the value of the inserted(or already present) pair
}

value& operator[](key&& x){
/**
	Returns the value of a pair given the key as an argument. Works with rvalues.
	If the key is not present, it inserts a new pair with the inputted key and a default conostructed value(since it has not been specified what to insert)

	It just calls the lvalue function
*/
	return (*this)[x];
}
//************************************************BALANCE
void balance(){
/**
	Reshapes the bst to become balanced

*/
	//create a std::vector
	std::vector<Node<treepair>> container = std::vector<Node<treepair>>{};

	//fills the new vector with the nodes of the bst in tree walk order
	for(auto& beginning : *this)
	{
		container.push_back(beginning);
	}

	clear();//empties the old bst
	balance_recursion(container);//calls a recursive function to refill the bst in a balanced fashion
}

void balance_recursion(std::vector<Node<treepair>> to_split){
/**
	Accessory function to fill the binary search tree in a balanced fashion

*/
	if (to_split.size()<2){//if vector has 1 element
		Node<treepair> temp1 =*(to_split.begin());//create temp node
		insert(temp1.value);//add the node to the bst
	}else if(to_split.size()==2){//if vector has 2 elements
		Node<treepair> temp1 =*(to_split.begin());
		insert(temp1.value);//add first element
		Node<treepair> temp2 =*(to_split.begin()+1);
		insert(temp2.value);//add second element(order not important)
	}else{//in the other cases
	Node<treepair> temp = *(to_split.begin()+to_split.size()/2);//use iterators of vector to find middle node
	insert(temp.value);//insert middle value
	
	//divide et impera
	//create two new vectors	
	std::vector<Node<treepair>> one{};
	std::vector<Node<treepair>> two{};
	//fill them with the first half and the second half of the argument vector respectively
	for(size_t i = 0; i<to_split.size()/2;i++)
		one.push_back(to_split[i]);	
	for(size_t i = (to_split.size()/2)+1; i<to_split.size();i++)
		two.push_back(to_split[i]);
	//recursively call the function        
	balance_recursion(one);
	balance_recursion(two);
	}
}
//************************SIZE
size_t size() const {
/**
	Returns the size of the bst
*/

	size_t counter{0};
	for ( auto& i : *this ){
		(void)i;
		++counter;	
	}
	return counter;
}

//************************************************* PRINT

friend
std::ostream& operator<<(std::ostream& os,const bst& x){
/**
	Prints the bst in tree walk order
*/
	//we use the auto keyword
        for ( auto& i : x )
		os<<i<<" ";
	return os;
}

};//END OF CLASS BST

int main () {
  /*int numbers[]={10,20,30,40,50};
  MyIterator from(numbers);
  MyIterator until(numbers+5);
  for (MyIterator it=from; it!=until; it++)
    std::cout << *it << ' ';
  std::cout << '\n';
   */
	using treepair = std::pair<int,int>;
	treepair pairA = treepair{5,34};
	treepair pairB = treepair{17,88};
	treepair pairC = treepair{45,2};
	treepair pairD = treepair{1,5};
	treepair pairE = treepair{6,12};
	
        using b_t_INT = bst<int,int>;
	b_t_INT bintree = b_t_INT();
	

	
	bintree.emplace(3,4);
	bintree.emplace(2,2);
	bintree.emplace(1,4);
	bintree.emplace(5,5);
	bintree.emplace(5,45);
	bintree.emplace(5,34);
	bintree.emplace(4,6);
	bintree.emplace(6,7);
	
	std::cout<<"FIRST PRINT:"<<std::endl;
	std::cout<<bintree<<std::endl;
	
	bintree.erase(3);
	MyIterator<treepair> beginning = bintree.begin();
	std::cout<<bintree<<std::endl;	

	
	bintree.insert(pairA);
	bintree.insert(pairB);
	bintree.insert(pairC);
        bintree.insert(pairD);
	bintree.insert(pairE);
	
	treepair pairF = treepair{70,33};
	
	bintree.insert(std::move(pairF));//TEST FOR RVALUE INSERTION
	bintree.insert(treepair{71,6});
	bintree.insert({72,77});
	bintree.emplace(4,6);
	bintree.emplace(8,9);
	bintree.emplace(27,7);
	bintree.emplace(34,8);
	bintree.emplace(99,99);//TEST FOR SUBSCRIPTION
	//std::cout<< "Max key is: "<< bintree.tree_maximum()<<" Min key is: "<<	bintree.tree_minimum()<<std::endl;
	
	MyIterator<treepair> inizio = bintree.begin();
        MyIterator<treepair> fine = bintree.end();
	int counter{0};	
	for(;inizio!=fine;++inizio){
		counter++;
		//std::cout<< bintree;
		//std::cout<<"contati "<<counter<<" nodi."<<std::endl;
		std::cout<<(*inizio)<< " ";		
			
	}
	std::cout<<"contati "<<counter<<" nodi."<<std::endl;  
	
	std::cout << bintree<<std::endl;

	bintree.find(34);
	bintree.find(2);
	bintree.find(7);
	bintree.find(5);
	std::cout<<"rimozione nodo 34"<<std::endl;
	bintree.erase(34);
	std::cout<<"finished erase"<<std::endl;

	std::cout<<bintree<<std::endl;
	std::cout<<"rimozione nodo 1"<<std::endl;
	bintree.erase(1);
	std::cout<<"finished erase"<<std::endl;

	std::cout<<bintree<<std::endl;

	std::cout<<"rimozione nodo 17"<<std::endl;
	bintree.erase(17);
	std::cout<<"finished erase"<<std::endl;

	
	bintree.tree_minimum();
	MyIterator<treepair> iniziale = bintree.begin();
	std::cout<<bintree<<std::endl;

	
	std::cout<<"printed tree"<<std::endl;
	
	b_t_INT bintree_copy{};//made an empty tree
	
	bintree_copy = bintree;
	std::cout<<"copy made"<<std::endl;
	std::cout<<bintree<<std::endl;
	std::cout<<"BINTREE_COPY"<<bintree_copy<<std::endl;
	bintree_copy.erase(5);
	std::cout<<"BINTREE_COPY_AFTER_ERASE"<<bintree_copy<<std::endl;
	//std::cout<<"TREE MINIMUM"<<std::endl;
	//bintree_copy.tree_minimum();	
	std::cout<<"PRINT BINTREE_COPY"<<bintree_copy<<std::endl;

	
	
	//std::cout<<bintree<<std::endl;
	
	//std::cout<<bintree_copy<<std::endl;
	b_t_INT bintree_copy_by_constructor{bintree};//made an empty tree
	
	std::cout<<bintree_copy_by_constructor<<std::endl;
	//b_t_INT bintree_move{std::move(bintree)};
	//std::cout<<bintree_move<<std::endl;
	for (auto& x : bintree_copy_by_constructor)
		std::cout<<x<<" ";
	std::cout<<std::endl;


	bintree_copy_by_constructor.emplace(8,45);
	bintree_copy_by_constructor.erase(4);
	
	std::cout<<bintree<<std::endl;	
	std::cout<<bintree_copy_by_constructor<<std::endl;
	
	int i = 99;
	int j = 100;
 	std::cout<<"SEARCHING FOR KEY"<<bintree[i]<<std::endl;
	std::cout<<"SEARCHING FOR KEY"<<bintree[j]<<std::endl;
	std::cout<<"SEARCHING FOR KEY"<<bintree[100]<<std::endl;
	std::cout<<"SEARCHING FOR KEY"<<bintree[5]<<std::endl;
 	//TRIAL WITH CONST_ITERATOR
	
	const b_t_INT const_bintree = b_t_INT{bintree};
	std::cout<<const_bintree<<std::endl;
	//const_bintree.emplace(3,3);
	//const_bintree.insert({5,5});
	const_bintree.find(100);
        std::cout<<const_bintree<<std::endl;

	std::cout<<"###########################TEST ON BALANCE##########"<<std::endl;
	std::cout<<bintree<<std::endl;
	bintree.balance();
	std::cout<<bintree<<std::endl;		
	std::cout<<"counted "<< bintree.size()<<" nodes "<<std::endl;	
	
	std::cout<<const_bintree<<std::endl;
	std::cout<<"counted "<< const_bintree.size()<<" nodes "<<std::endl;	
	//const_MyIterator<treepair> iterate = const_bintree[70]; //subscription doesn't work on constant bst-s	
	return 0;
}

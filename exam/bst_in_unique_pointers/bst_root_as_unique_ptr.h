#ifndef BST
#define BST


struct FullMemoryException{};

/////////////BINARY SEARCH TREE CLASS

template<class key,class value,typename cmp = std::less<key>>
class bst{
/**
	Class that implements a binary search tree, as described in the book "Introduction to algorithms" by Cormen,Leiserson,Rivest,Stein; chapter 12 pages 286 to 298
*/
	using treepair = std::pair<const key,value>;//pair used in tree
	
public:

//define the iterator of the class
class iterator : public MyIterator<treepair>{
public:	
	iterator(Node<treepair>* a, Node<treepair>* b): MyIterator<treepair>(a,b){}

	
};
//define the constant iterator of the class
struct const_iterator : public const_MyIterator<treepair>{
public:	
	const_iterator(Node<treepair>* a, Node<treepair>* b): const_MyIterator<treepair>(a,b){}
	

};
	cmp op;//this is the comparison operator

	std::unique_ptr<Node<treepair>> root;//pointer to the root node
	
	//default creator
	bst()
	{std::cout<<"binary tree created"<<std::endl;}

	~bst(){
	std::cout<<"destructor on bst"<<std::endl;
	root.reset();
	}
//************copy semantics
	//copy constructor -- deep copy
	bst(const bst& bintree) 
	:root{} {
		if(!bintree.isEmpty()){
		root.reset(bintree.root.get());//destroys the old tree
		copy_part(bintree.root.get());//calls a recursive function that fills the new bst	
		}	
	}
 

  	// copy assignment -- deep copy
	bst& operator=(const bst& bintree) {
		
		if(&bintree == this)//check for self reference
        	    return *this;
		clear();//empties the lhs bst
		if(bintree.isEmpty()) return *this;	
		insert(bintree.root->value);//inserts the root of the bst to copy
		copy_part(bintree.root.get());//calls a recursive function that fills the new bst	
		
		return *this;
	}
	
	


	//**************************MOVE SEMANTICS(done as default)
	//move constructor
	bst(bst&& bintree) noexcept : root{std::move(bintree.root)}{}
	// move assignment
 	bst& operator=(bst&& bintree) noexcept{
    		root = std::move(bintree.root);
   		return *this;
  	}






/*

private:
//We collect here a few private accessory functions

	void copy_part(Node<treepair>* x) {
	
		//Accessory function to perform the deep-copy
	
		if(x == nullptr) return;//check if tree is empty
		//inserts first the left children of the node and all its children
		if((x->left).get()!=nullptr){
			insert(x->left->value);		
		        copy_part((x->left).get());//recusive call
		}
		//and then inserts the right children of the node and all its children
		if((x->right).get()!=nullptr){
			insert(x->right->value);		
		        copy_part((x->right).get());//recursive call
		}
	}


//-**************************TREE MIN and TREE MAX
 Node<treepair>* tree_minimum( Node<treepair>* y) const noexcept{

	//Accessory function that finds the most left sided node of tree that has the argument as a root
	//(The first one in the tree walk)		

	//check if the argument is nullptr	
	if (y == nullptr ) return y;	

	Node<treepair>* x = nullptr;
	//check if argument has left child
	if((y->left).get() !=nullptr)
		x = (y->left).get();
	else return y;//else the argument is the most left sided node	
	
	//now we find the most left sided node
	while ((x->left).get() != nullptr)
	{
		x = (x->left).get();		
	}	
	return x;//return the found node
}


Node<treepair>* tree_maximum(Node<treepair>* y) const noexcept{

	//Accessory function to find the most right sided node of the tree that has the argument as the root node
	//(The last one in the tree walk)

	//check if the argument is nullptr
	if (y == nullptr ) return y;

	Node<treepair>* x = nullptr;
	
	//check if the argument has right child	
	if((y->right).get()!=nullptr)
		 x= (y->right).get();//!?
	else return y;//else the argument is the most right sided node		
	
	//now we find the most right sided node
	while ((x->right).get() != nullptr){
		x = (x->right).get();//!?
	}
	return x;//we return the found node
}

Node<treepair>* tree_minimum() const noexcept{

	//when called with no argument tree_minimum finds the most left sided node of the whole bst
	
	Node<treepair>* root_node{root};
	//check if applied on an empty bst	
	if (isEmpty()) return nullptr;
	return tree_minimum(root_node);
}


Node<treepair>* tree_maximum() const noexcept{

	//when called with no argument tree_maximum finds the most right sided node of the whole bst
	
	Node<treepair>* root_node{root};
	//check if applied on an empty bst
	if (isEmpty()) return nullptr;
	return tree_maximum(root_node);
}


iterator tree_search(Node<treepair>* x, const key& y) noexcept{

	//Accessory function that performs the bt search exploiting the binary-search-tree property
	//Returns a regular iterator
	

	if(x == nullptr)//element not found,we have reached a dead end
	{
		return end();
	}
	else if ( !op(y,x->value.first)&&!op(x->value.first,y))//equality among the comparison operators, if true the element is found
	{
		iterator i{x,tree_maximum()};
		return i;
	}
	
	//element yet to be found, here the keys are compared and the wanted left or right sub-tree is choosen
	if(op(y , x->value.first) )
		return tree_search((x->left).get(),y);
	else 
		return tree_search((x->right).get(),y);
}

const_iterator tree_search(Node<treepair>* x, const key& y) const noexcept{
//CORRECTION,REORDER THE SEQUENCE OF IF CLAUSES TO AVOID REPEATING THE COMPARISON OPERATOR
	//Accessory function that performs the bt search exploiting the binary-search-tree property
	//Returns a const_iterator

	if(x == nullptr)//element not found, we have reached a dead end
	{
		return end();
	}
	else if ( !op(y,x->value.first)&&!op(x->value.first,y))//equality among the comparison operators, if true the element is found
	{
		const_iterator i{x,tree_maximum()};
		return i;
	}

	//element yet to be found, here the keys are compared and the wanted left or right sub-tree is choosen
	if(op(y , x->value.first)) 
		return tree_search((x->left).get(),y);
	else	
		return tree_search((x->right).get(),y);
}




void transplant(Node<treepair>* a, Node<treepair>* b) noexcept{

	//Accessory function that serves to rearreange the nodes before and after deletion 
	//a 's place is exchanged with b's place
std::cout<<"into transplant"<<std::endl;
 
	if ((a->parent).get() == nullptr){//a is the root, then b becomes the root
		std::cout<<"case1"<<std::endl;		
		root = b;
	}
	else if (a == (a->parent->left).get()){//a is not the root, a is the left child of his parent		
		std::cout<<"case2"<<std::endl;
		Node<treepair>* temp1 = a->parent->left.release();
		a->parent->left.reset(b);//then b becomes the new left child of a's parent
		//std::cout<<"!!"<<std::endl;
		//if(temp1 == nullptr) std::cout<<"!nullptr!"<<std::endl;
		//std::unique_ptr<Node<treepair>> temporary1{temp1};
	}
	else{
		std::cout<<"case3"<<std::endl;		
		Node<treepair>* temp2 = a->parent->right.release();
		a->parent->right.reset(b);//else b becomes the new right child of a's parent
	
		//std::unique_ptr<Node<treepair>> temporary2{temp2};
	}
	if (b != nullptr){ 	
		std::cout<<"extra point declenched"<<std::endl;
		Node<treepair>* temp3 = (b->parent).release();	
		(b->parent).reset(a->parent.release()); //if b is an actual node, then b's parent becomes a's parent
	
		//std::unique_ptr<Node<treepair>> temporary3{temp3};
	}
std::cout<<"outo transplant"<<std::endl;
}

*/
void clear_part(Node<treepair>* x) noexcept{

	//Accessory function that sweeps the whole tree and deletes all the nodes
	if(x != nullptr){
	std::cout<<"inside "<<std::endl;
	if(x->left!=nullptr)
	x->left.reset(nullptr);
	else std::cout<<"is nullptr"<<std::endl;
	if(x->right!=nullptr)
	x->right.reset(nullptr);
	else std::cout<<"is nullptr"<<std::endl;
	}	
	/*if(x != nullptr){
		clear_part((x->left).get());
		clear_part((x->right).get());
		delete x;
		
	}*/

}

/*
void balance_recursion(std::vector<Node<treepair>> to_split)  {


	//Accessory function to fill the binary search tree in a balanced fashion


	if (to_split.size()<2){//if vector has 1 element
		insert(to_split.begin()->value);//add the node to the bst
	}else if(to_split.size()==2){//if vector has 2 elements
		insert(to_split.begin()->value);//add first element
		insert((to_split.begin()+1)->value);//add second element(order not important)
	}else{//in the other cases
	//use iterators of vector to find middle node
	insert((to_split.begin()+to_split.size()/2)->value);//insert middle value
	
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
	balance_recursion(std::move(one));
	balance_recursion(std::move(two));
	}

 
}



*/
/*
public:

//-*********************BEGIN AND END

iterator begin() noexcept{

	//retuns a regular iterator pointing at the first element of the tree walk

	return iterator{tree_minimum(),tree_maximum()};
}
  
const_iterator begin() const noexcept{

	//retuns a cons_iterator pointing at the first element of the tree walk

	return const_iterator{tree_minimum(),tree_maximum()};
}


const_iterator cbegin() const noexcept{

	//retuns a cons_iterator pointing at the first element of the tree walk

	return const_iterator{tree_minimum(),tree_maximum()};
}




iterator end() noexcept{

	//retuns a regular iterator pointing at the past-the-last-element of the tree walk

	return iterator{nullptr,tree_maximum()};

}


const_iterator end() const noexcept{

	//retuns a cons_iterator pointing at the past-the-last-element of the tree walk

	return const_iterator{nullptr,tree_maximum()};
}


const_iterator cend() const noexcept{

	//retuns a cons_iterator pointing at the past-the-last-element of the tree walk

	return const_iterator{nullptr,tree_maximum()};
}

*/
//-**************************INSERTION
std::pair<iterator,bool> insert(const treepair& z){

	//Inserts a new element of the type treepair into the bst. It works with lvalues.
	//-If the key is not present it creates a new node and inserts it into the bst keeping intact the binary-search-tree property then it just returns am std::pair containing an iterator to the new node and a boolean saying "true"	
	//- If the key is already present it just returns an iterator to that element and a boolean saying "false"


std::cout<<"Inserting pair "<< z << std::endl;
	iterator found = find(z.first);//searches for the key

	if(found !=end()){//if it is already present
	 	std::pair<iterator,bool> x{found,false};//creates the output pair
 		return x;//returns the wanted pair
	}
	//else creates a new node and inserts it
	Node<treepair>* newnode_z = new Node<treepair>{z};
	
	if (newnode_z == nullptr) throw FullMemoryException{};
	
	if(isEmpty())//empty tree
	{	
			
		root.reset(newnode_z);//inserted node is the root
		iterator x_root {root.get(),root.get()};//creates the pointer to the root
		std::pair<iterator,bool> to_return ={x_root,true};//creates the output pair
        	return to_return;//returns the wanted pair
	}
	
	//We apply the algorithm from the book
	
	Node<treepair>* y = nullptr;//this will be the parent of x
	Node<treepair>*	x = root;//this will be one of the children of y
	while(x != nullptr){//until we find an empty space
		y = x;
		if (op( newnode_z->value.first,x->value.first))//here we apply the operator on the key of the element to insert and the key of the element we are inspecting
			x = (x->left).get();
		else x= (x->right).get();
		}
	Node<treepair>* temp1 = (newnode_z->parent).release();
	(newnode_z->parent).reset( y ); //so y is the parent of the new node
	(void)temp1;
	//std::unique_ptr<Node<treepair>> temporary1{temp1};
	if (y == nullptr){
		root = newnode_z;
		}
	else if(op(   newnode_z->value.first, y->value.first  )){//key check using the comparison operator	
		Node<treepair>* temp2 = (y->left).release();	
		(y->left).reset(newnode_z);//now we identify the correct position of the new node accordingly to the parent
		(void) temp2;
	
		//std::unique_ptr<Node<treepair>> temporary2{temp2};
	}else{
	Node<treepair>* temp3 =(y->right).release();
 	(y->right).reset(newnode_z);
	(void)temp3;
	//std::unique_ptr<Node<treepair>> temporary3{temp3};
	}	
	//Now we have to return the iterator to the node we inserted
	iterator x_ret{newnode_z,tree_maximum()};//create iterator
	std::pair<iterator,bool> to_return ={x_ret,true};//create pair
        return to_return;//return pair
}


std::pair<iterator,bool> insert(treepair&& z) {

	//Inserts a new element of the type treepair into the bst. It works with rvalues.
	//-If the key is not present it creates a new node and inserts it into the bst keeping intact the binary-search-tree property then it just returns am std::pair containing an iterator to the new node and a boolean saying "true"	
	//- If the key is already present it just returns an iterator to that element and a boolean saying "false"
	//The code is the same as the above example

	return insert(z);//it just invokes the lvalue function

}
*/

//-**********************************EMPLACE

template< typename... Types >
std::pair<iterator,bool> emplace(Types&&... args) {
treepair newelement{std::forward<Types>(args)...};
std::pair<iterator,bool> x = insert(newelement);
return x;
}
*/
//-***********************************FIND

iterator find(const key& x) noexcept{

	//Finds the element whose key is the given argument
	//Returns a regular iterator pointing to that element

	return tree_search(root,x);	
}




const_iterator find(const key& x) const noexcept
{

	//Finds the element whose key is the given argument
	//Returns a const_iterator pointing to that element

	return tree_search(root,x);	
}

void debug(int a){}

//-****************************DELETE

void erase(const key& x) noexcept{

	//Removes the element from the tree with the corresponding key. If the key is not present nothing is done.
	//The removal leaves the binary-search-tree property intact.


	iterator to_remove = find(x);//finds the element to remove, if present
	Node<treepair>* remove = &(*to_remove);//we change the type of the element to remove from iterator to regular pointer;
std::cout<<"find made"<<std::endl;
	if (remove == nullptr)//The key has not been found
	{
		std::cout<<"Key not found"<<std::endl;
		return;//nothing is done
	}
	
	if ((remove->left).get() == nullptr){//first case, the node to remove doesn't have a left child
		std::cout<<"first case made"<<std::endl;
		transplant(remove,(remove->right).get());//just attach the right child to the parent(if it's nullpointer then the node to remove has no children and is just deleted)
		
	}
	else if ((remove->right).get() == nullptr){//second case, the node to remove doesn't have a right child
		std::cout<<"second case made"<<std::endl;
		transplant(remove,(remove->left).get());//just attach the left child to the parent
	}
	else{//third case, the node to remove has both left and right child
		//we find the node with the smallest key in the right subtree of the node to remove
		std::cout<<"third case made"<<std::endl;
		Node<treepair>* y_ = tree_minimum((remove->right).get());
		
		if((y_->parent).get() != remove){//this handles the harder case when the node we found above is not the direct child of the node to delete: in practice we turn that node INTO the direct child of the node to delete while assuring the binary-search-tree property
			std::cout<<"inside if1"<<std::endl;			
			transplant(y_,(y_->right).get());
			Node<treepair>* temp1 = y_->right.release();
			y_->right.reset((remove->right).release());
			std::cout<<"inside if2"<<std::endl;
			//std::unique_ptr<Node<treepair>> temporary1{temp1};
			Node<treepair>* temp2 = y_->right->parent.release();
			y_->right->parent.reset(y_);
			//std::unique_ptr<Node<treepair>> temporary2{temp2};
			std::cout<<"inside if3"<<std::endl;	
			}
		std::cout<<"if node is not child case made"<<std::endl;
		transplant(remove,y_);//we swap the node to remove and its direct child(which is its right child)
		
		Node<treepair>* temp3 = y_->left.release() ;
		y_->left.reset((remove->left).release()); //the left child and its subtree is inherited without changes
		
		
		//std::unique_ptr<Node<treepair>> temporary3{temp3};		
		
		Node<treepair>* temp4 = y_->left->parent.release();
		y_->left->parent.reset( y_ ); //we adjust the left child of the node to remove with its new parent
		
		
		//std::unique_ptr<Node<treepair>> temporary4{temp4};		
		
		std::cout<<"almost remove case made"<<std::endl;
	}
	std::cout<<"almost remove"<<std::endl;	
	if (remove == nullptr) std::cout<<"remove is nullptr"<<std::endl;	
	//delete remove;//there is no need to free the memory anymore
	
}
*/
//-****************************CLEAR
void clear() noexcept{

	//Clears and empties the whole tree. Leaves an empty tree.

	clear_part(root);
	root = nullptr;
}


bool isEmpty() const noexcept{

	//Checks if the bst is empty

	return root == nullptr;
}

//-***********************SUBSCRIPTING OPERATOR
value& operator[](const key& x) {

	//Returns the value of a pair given the key as an argument.Works with lvalues
	//If the key is not present, it inserts a new pair with the inputted key and a default conostructed value(since it has not been specified what to insert)


	value newitem = value{};//create default new value
	treepair newpair = treepair{x,newitem};//create new pair to insert		
	std::pair<iterator,bool> v = insert(newpair);//we insert the new pair anyway. If the key is already present nothing will happen and the output will still be a valid iterator
	return (*(v.first)).value.second;//returns the value of the inserted(or already present) pair
}

value& operator[](key&& x) {

	//Returns the value of a pair given the key as an argument. Works with rvalues.
	//If the key is not present, it inserts a new pair with the inputted key and a default conostructed value(since it has not been specified what to insert)

	//It just calls the lvalue function

	return (*this)[x];
}


//-************************************************BALANCE
void balance() {

	//Reshapes the bst to become balanced


	if(isEmpty()) return;//does nothing if bst is empty
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


//-************************SIZE
size_t size() const noexcept{

	//Returns the size of the bst


	size_t counter{0};
	for ( auto& i : *this ){
		(void)i;
		++counter;	
	}
	return counter;
}

//-************************************************* PRINT

friend
std::ostream& operator<<(std::ostream& os,const bst& x) noexcept{

	//Prints the bst in tree walk order

	//we use the auto keyword
        for ( auto& i : x )
		os<<i<<" ";
	return os;
}

};//END OF CLASS BST
#endif

// std::iterator example
#include <iostream>     // std::cout
#include <iterator>     // std::iterator, std::input_iterator_tag
#include <vector>       // std::vector

template<class T>
class Node;

template<class key,class value,typename cmp /*= std::less<key>*/>
class bst;

//*******************NORMAL ITERATOR
template<class T>
class MyIterator : public std::iterator<std::forward_iterator_tag, Node<T>>
{
  Node<T>* pointer;
  Node<T>* last;
public:
  MyIterator(Node<T>* x,Node<T>* last_element) :pointer(x),last{last_element} {}
  MyIterator(const MyIterator<T>& mit) : pointer(mit.pointer), last{mit.last} {}//copy constructor

  MyIterator& operator++() {
	//std::cout<<"++ invoked"<<std::endl;
	if(pointer == last) {
		pointer = nullptr;
		//std::cout<<"Tree ended"<<std::endl;
        	return *this;
		}
	if (pointer->right != nullptr){
			
			pointer = pointer->right;
                        while (pointer->left != nullptr)
				pointer = pointer->left;
			//std::cout<<"path A is chosen"<<std::endl;
			return *this;
			}
	Node<T>* y = pointer->parent;
	while(y != nullptr && pointer == y->right){
		pointer = y;
		y = y->parent;
		}
	pointer = y;
	//std::cout<<"path B is chosen"<<std::endl;
	return *this;
		}

  //MyIterator operator++(int) {MyIterator tmp(*this); operator++(); return tmp;}
 
  bool operator==(const MyIterator& rhs) const {return pointer==rhs.pointer;}
  bool operator!=(const MyIterator& rhs) const {return pointer!=rhs.pointer;}
  Node<T>& operator*() {return *pointer;}

   /*friend
std::ostream& operator<<(std::ostream& os, const MyIterator& x)
{
	os<< *x<<std::endl;
	return os;
}*/	
};

//*******************CONST ITERATOR
template<class T>
class const_MyIterator : public std::iterator<std::forward_iterator_tag, const Node<T>>
{
  Node<T>* pointer;
  Node<T>* last;
public:
  const_MyIterator(Node<T>* x,Node<T>* last_element) :pointer(x),last{last_element} {}
  const_MyIterator(const const_MyIterator<T>& mit) : pointer(mit.pointer), last{mit.last} {}//copy constructor

const_MyIterator& operator=(const const_MyIterator& x){
	pointer = x.pointer;
	last = x.last;
	return *this;	
	
}

  const_MyIterator& operator++() {
	//std::cout<<"++ invoked"<<std::endl;
	if(pointer == last) {
		pointer = nullptr;
		//std::cout<<"Tree ended"<<std::endl;
        	return *this;
		}
	if (pointer->right != nullptr){
			
			pointer = pointer->right;
                        while (pointer->left != nullptr)
				pointer = pointer->left;
			//std::cout<<"path A is chosen"<<std::endl;
			return *this;
			}
	Node<T>* y = pointer->parent;
	while(y != nullptr && pointer == y->right){
		pointer = y;
		y = y->parent;
		}
	pointer = y;
	//std::cout<<"path B is chosen"<<std::endl;
	return *this;
		}

  //MyIterator operator++(int) {MyIterator tmp(*this); operator++(); return tmp;}
 
  bool operator==(const const_MyIterator& rhs) const {return pointer==rhs.pointer;}
  bool operator!=(const const_MyIterator& rhs) const {return pointer!=rhs.pointer;}
  const Node<T>& operator*() {return *pointer;}//HERE IS THE DIFFERENCE

   /*friend
std::ostream& operator<<(std::ostream& os, const MyIterator& x)
{
	os<< *x<<std::endl;
	return os;
}*/	
};


//*************************************NODE

template<class T>
class Node{
T value;
Node<T>* left;
Node<T>* right;
Node<T>* parent;
public:

Node(T element)
:value{element},left{nullptr},right{nullptr},parent{nullptr}{}


~Node(){//std::cout<<"Removed Node"<<std::endl;
}

/***********function used only for printing the content of the node, not used anymore
T getValue() const{
return value;
}
*/

template<class key,class value,typename cmp/* = std::less<key>*/>
friend class bst;

template<class S>
friend class MyIterator;
template<class S>
friend class const_MyIterator;

//friend
//std::ostream& operator<<(std::ostream& os, bst& x);
	/*{
	MyIterator<treepair> i = x.begin();
	for(;i!=x.end();++i)
		os << (*i).value.first;
	return os;
	}*/
friend
std::ostream& operator<<(std::ostream& os, const Node<T>& x)
	{
	os<<x.value;
	return os;
	}
};

template<typename T1,typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1,T2>& x)
{
	os<<x.first<<"_"<<x.second;
	return os;
}

////////////////////////
/////////////BINARY SEARCH TREE CLASS
////////////////////////
template<class key,class value,typename cmp = std::less<key>>
class bst{
using treepair = std::pair<key,value>;
cmp op;
Node<treepair>* root;

public:
bst()
:root{nullptr} {std::cout<<"binary tree created"<<std::endl;}

//************copy semantics


bst(const bst& bintree):root{new Node<treepair>{bintree.root->value}} {
std::cout<<"copy constructor"<<std::endl;
//std::cout<<"root is"<<root->value.first<<"_"<<root->value.second<<std::endl;
copy_part(bintree.root);	

} 

  // copy assignment -- deep copy
bst& operator=(const bst& bintree){
	std::cout<<"copy assignment invoked"<<std::endl;
	if(&bintree == this)
            return *this;
	
	clear();	
	insert(bintree.root->value);
	copy_part(bintree.root);	
	return *this;
}
void copy_part(Node<treepair>* x){
		std::cout<<*this<<std::endl;
		if(x->left!=nullptr){
			insert(x->left->value);		
		        copy_part(x->left);
		}
		if(x->right!=nullptr){
			insert(x->right->value);		
		        copy_part(x->right);
		}
}



//**************************MOVE SEMANTICS
//move constructor
bst(bst&& bintree) : root{std::move(bintree.root)}{
    std::cout << "move ctor\n";
  }

  
  // move assignment
  bst& operator=(bst&& bintree) {
    std::cout << "move assignment\n";
    root = std::move(bintree.root);
    return *this;
  }








//**************************TREE MIN and TREE MAX



 Node<treepair>* tree_minimum( Node<treepair>* y) const 
{
	if (y ==nullptr ) return y;
	
	//std::cout<< "Invoked tree_min on"<< y->value.first<<" then "<< y->value.second<<std::endl;
	Node<treepair>* x = nullptr;
	if(y->left!=nullptr)
		x = y->left;
	else return y;	
		
	while (x->left != nullptr)
	{
		
		x = x->left;
		//std::cout<< "Now we have"<< x->value.first<<" then "<< x->value.second<<std::endl;		
	}
	//std::cout<<"found first: "<< x->value.first<<" : "<< x->value.second<<std::endl;	
	
	//std::cout<<"we return first"<<std::endl;	
	return x;

}
Node<treepair>* tree_maximum(Node<treepair>* y) const
{
	if (y ==nullptr ) return y;
	
	//std::cout<< "Invoked tree_min on"<< y->value.first<<" then "<< y->value.second<<std::endl;
	Node<treepair>* x = nullptr;
	if(y->right!=nullptr)
		 x= y->right;
	else return y;		
	while (x->right != nullptr){
		//std::cout<< "Now we have"<< x->value.first<<" then "<< x->value.second<<std::endl;
		x = x->right;
		//std::cout<< "Now we have"<< x->value.first<<" then "<< x->value.second<<std::endl;

}
	//std::cout<<"found last: "<< x->value.first<<" : "<< x->value.second<<std::endl;	
	return x;

}
Node<treepair>* tree_minimum() const
{
	//std::cout<<"tree_min() invoked"<<std::endl;
	Node<treepair>* i{root};	
	//std::cout<<"new node created"<<std::endl;
	if (i ==nullptr ) return i;
	
	return tree_minimum(i);

}
Node<treepair>* tree_maximum() const
{
	//std::cout<<"root pointer is"<<root<<std::endl;
	Node<treepair>* i{root};
	if (i ==nullptr ) return i;
		
	return tree_maximum(i);

}
//*********************BEGIN AND END

MyIterator<treepair> begin(){
	//std::cout<<"invoked begin()"<<std::endl;
	return MyIterator<treepair>{tree_minimum(),tree_maximum()};
}
  
const_MyIterator<treepair> begin() const{
	return const_MyIterator<treepair>{tree_minimum(),tree_maximum()};
}


const_MyIterator<treepair> cbegin() const{
	return const_MyIterator<treepair>{tree_minimum(),tree_maximum()};
}




MyIterator<treepair> end(){
//std::cout<<"invoked end()"<<std::endl;
return MyIterator<treepair>{nullptr,tree_maximum()};

}


const_MyIterator<treepair> end() const{

return const_MyIterator<treepair>{nullptr,tree_maximum()};
}


const_MyIterator<treepair> cend() const{

return const_MyIterator<treepair>{nullptr,tree_maximum()};
}


//**************************INSERTION
std::pair<MyIterator<treepair>,bool> insert(const treepair& z){
std::cout<<"LVALUE INSERTION INVOKED adding pair"<<z.first<<" : "<<z.second<<std::endl;
//if(root != nullptr) std::cout<<"root is"<<root->value.first<<"_"<<root->value.second<<std::endl;
MyIterator<treepair> found = find(z.first);
if(found !=end()){
 std::cout<<"Inserted Copy  "<<(*found).value.first<< "_" << (*found).value.second <<std::endl;
 std::pair<MyIterator<treepair>,bool> x{found,false};
 return x;
}
Node<treepair>* newnode_z = new Node<treepair>{z};
std::cout<<"node created"<<std::endl;

if(root == nullptr)//empty tree
	{	
		root = newnode_z;
		//std::cout<<"new root :"<< (*root).value.first<<" : "<<(*root).value.second<<std::endl;
		MyIterator<treepair> x_root {newnode_z,tree_maximum()};
		std::pair<MyIterator<treepair>,bool> to_return ={x_root,true};
        	return to_return;
        	
	}
	//start algorithm from the book
	Node<treepair>* y = nullptr;//is the parent of x
	Node<treepair>*	x = root;//is one of the children of y
	while(x != nullptr){//until we find an empty space
		y = x;
		if (op((*newnode_z).value.first,(*x).value.first))
			x = (*x).left;
		else x= (*x).right;
		}
	(*newnode_z).parent = y; //so y is the parent of the new node
	//std::cout<<"parent found. it's "<<(*y).value.first<<" : "<<(*y).value.second<<std::endl;
	
	if (y == nullptr){
                //std::cout<< "root changed in unusual way"<<std::endl;
		root = newnode_z;
		}
	else if(op(   (*newnode_z).value.first,(*y).value.first  ))		
		(*y).left = newnode_z;//now we identify the correct position of the new node accordingly to the parent
	else (*y).right = newnode_z;
	MyIterator<treepair> x_ret{newnode_z,tree_maximum()};
	std::pair<MyIterator<treepair>,bool> to_return ={x_ret,true};
        return to_return;
}


std::pair<MyIterator<treepair>,bool> insert(treepair&& z){
std::cout<<"RVALUE INSERTION INVOKED adding pair"<<z.first<<" : "<<z.second<<std::endl;
//if(root != nullptr) std::cout<<"root is"<<root->value.first<<"_"<<root->value.second<<std::endl;
MyIterator<treepair> found = find(z.first);
if(found !=end()){
 std::pair<MyIterator<treepair>,bool> x{found,false};
 return x;
}
Node<treepair>* newnode_z = new Node<treepair>{z};
std::cout<<"node created"<<std::endl;

if(root == nullptr)//empty tree
	{	
		root = newnode_z;
		//std::cout<<"new root :"<< (*root).value.first<<" : "<<(*root).value.second<<std::endl;
		MyIterator<treepair> x_root {newnode_z,tree_maximum()};
		std::pair<MyIterator<treepair>,bool> to_return ={x_root,true};
        	return to_return;
        	
	}
	//start algorithm from the book
	Node<treepair>* y = nullptr;//is the parent of x
	Node<treepair>*	x = root;//is one of the children of y
	while(x != nullptr){//until we find an empty space
		y = x;
		if ( op((*newnode_z).value.first,(*x).value.first)  )
			x = (*x).left;
		else x= (*x).right;
		}
	(*newnode_z).parent = y; //so y is the parent of the new node
	//std::cout<<"parent found. it's "<<(*y).value.first<<" : "<<(*y).value.second<<std::endl;
	
	if (y == nullptr){
                //std::cout<< "root changed in unusual way"<<std::endl;
		root = newnode_z;
		}
	else if(  op(  (*newnode_z).value.first,(*y).value.first  )   )		
		(*y).left = newnode_z;//now we identify the correct position of the new node accordingly to the parent
	else (*y).right = newnode_z;
	MyIterator<treepair> x_ret{newnode_z,tree_maximum()};
	std::pair<MyIterator<treepair>,bool> to_return ={x_ret,true};
        return to_return;
}


//**********************************EMPLACE
template< class... Types >
std::pair<MyIterator<treepair>,bool> emplace(Types&&... args){
treepair newelement{args...};
std::pair<MyIterator<treepair>,bool> x = insert(newelement);
return x;
}
//***********************************FIND

MyIterator<treepair> find(const key& x)
{
	std::cout<<"regular find invoked"<<std::endl;
	return tree_search(root,x);	
}
const_MyIterator<treepair> find(const key& x) const
{
	std::cout<<"const find invoked"<<std::endl;
	return tree_search(root,x);	
}


const_MyIterator<treepair> tree_search(Node<treepair>* x, const key& y) const
{
	if(x == nullptr)
	{
		std::cout<<"element not found"<<std::endl;
		const_MyIterator<treepair> x = end();
		return x;
	}
	else if ( !op(y,x->value.first)&&!op(x->value.first,y))
	{
		const_MyIterator<treepair> i{x,tree_maximum()};
		std::cout<<"element found"<<std::endl;
		return i;
	}
	if(op(y , x->value.first)) 
		return tree_search(x->left,y);
	else return tree_search(x->right,y);
}

MyIterator<treepair> tree_search(Node<treepair>* x, const key& y)
{
	if(x == nullptr)
	{
		std::cout<<"element not found"<<std::endl;
		MyIterator<treepair> x = end();
		return x;
	}
	else if ( !op(y,x->value.first)&&!op(x->value.first,y))
	{
		MyIterator<treepair> i{x,tree_maximum()};
		std::cout<<"element found"<<std::endl;
		return i;
	}
	if(op(y , x->value.first) ) 
		return tree_search(x->left,y);
	else return tree_search(x->right,y);
}

/*
MyIterator<treepair> find(const key& x)
{
	std::cout<<"regular find invoked"<<std::endl;
	return tree_search<MyIterator<treepair>>(root,x);	
}
const_MyIterator<treepair> find(const key& x) const
{
	std::cout<<"const find invoked"<<std::endl;
	return tree_search<const_MyIterator<treepair>>(root,x);	
}

template<typename iterator>
iterator tree_search(Node<treepair>* x, const key& y) const
{
	if(x == nullptr)
	{
		std::cout<<"element not found"<<std::endl;
		iterator x = end();//end is called on a "const this" and so calls the const end() that returns a const variable
		return x;
	}
	else if (y == x->value.first)
	{
		iterator i{x,tree_maximum()};
		std::cout<<"element found"<<std::endl;
		return i;
	}
	if(y < x->value.first) 
		return tree_search<iterator>(x->left,y);
	else return tree_search<iterator>(x->right,y);
}
*/
//****************************DELETE
void transplant(Node<treepair>* a, Node<treepair>* b)
{
std::cout<<"Transplant invoked"<<std::endl;
if (a->parent == nullptr)
	root = b;
else if (a == a->parent->left)
	a->parent->left = b;
else a->parent->right = b;
if (b != nullptr)
	b->parent = a->parent;

}

void erase(const key& x){
	MyIterator<treepair> to_remove = find(x);
	Node<treepair>* remove = &(*to_remove);
//std::cout<<"NODE to remove points to left "<<remove->left->value.firs<<"_"<<remove->right->value.second<<" and to right to "<<remove->right->value.first<<"_"<<remove->right->value.second<<std::endl;
	if (remove ==nullptr)
	{
		std::cout<<"Key not found"<<std::endl;
		return;
	}
	if (remove->left == nullptr){
		//std::cout<<"Road A"<<std::endl;
		transplant(remove,remove->right);
	}
	else if (remove->right == nullptr){
		//std::cout<<"Road B"<<std::endl;
		transplant(remove,remove->left);
	}
	else{
		//std::cout<<"Road C"<<std::endl;
//std::cout<<"1!!remove point right to "<<remove->right->value.first<<"_"<<remove->right->value.second<<std::endl;
		Node<treepair>* y_ = tree_minimum(remove->right);
		//std::cout<<"1.5!!remove point right to "<<remove->right->value.first<<"_"<<remove->right->value.second<<std::endl;
		//std::cout<< "HERE we found:"<<y->value.first<<"_"<<y->value.second<<std::endl;
		if(y_->parent != remove){
//std::cout<<"2!!remove point right to "<<remove->right->value.first<<"_"<<remove->right->value.second<<std::endl;
			transplant(y_,y_->right);
//std::cout<<"3!!remove point right to "<<remove->right->value.first<<"_"<<remove->right->value.second<<std::endl;
			//if(y_->right != nullptr)
			//std::cout<<"NOW "<<y_->right->value.first<<"_"<<y_->right->value.second<<"BECOMES"<<remove->right->value.first<<"_"<<remove->right->value.second<<std::endl;
			//else std::cout<<"NOW "<<"nullptr"<<"_"<<"nullptr"<<"BECOMES"<<remove->right->value.first<<"_"<<remove->right->value.second<<std::endl;
			y_->right = remove->right;

			y_->right->parent = y_;
			}
		transplant(remove,y_);
		
		y_->left=remove->left;
		
		y_->left->parent=y_;
		//std::cout<< "SUBSTITUTED NODE POINTS AT "<< "left:"<<y_->left->value.first<<"_"<<y_->left->value.second<< "right:"<<y_->right->value.first<<"_"<<y_->right->value.second<<std::endl;
		
	}
	delete remove;

}

//****************************CLEAR
void clear(){
	clear_part(root);
	root = nullptr;
}

void clear_part(Node<treepair>* x){
	
	if(x != nullptr){
		clear_part(x->left);
		clear_part(x->right);
		delete x;
	}
}

//***********************SUBSCRIPTING OPERATOR

//_____________________I WILL TRY A BETTER VERSION
/*
value& operator[](const key& x){
MyIterator<treepair> y = find(x);
if(y == end())
{
	value newitem = value{};
	treepair newpair = treepair{x,newitem};		
	//Node<treepair> newnode = Node<treepair>{newpair};
	std::pair<MyIterator<treepair>,bool> v = insert(newpair);
	return (*(v.first)).value.second;
}
else return (*y).value.second;
}*/

value& operator[](const key& x){

	value newitem = value{};
	treepair newpair = treepair{x,newitem};		
	std::pair<MyIterator<treepair>,bool> v = insert(newpair);
	return (*(v.first)).value.second;
}
value& operator[](key&& x){
value newitem = value{};
	treepair newpair = treepair{x,newitem};		
	std::pair<MyIterator<treepair>,bool> v = insert(newpair);
	return (*(v.first)).value.second;

}
//************************************************BALANCE
void balance(){

std::vector<Node<treepair>> container = std::vector<Node<treepair>>{};

//std::cout << std::boolalpha;
//std::cout<<"is vector empty? right after creation  "<<container.empty()<<std::endl;

//MyIterator<treepair> beginning = begin();
//MyIterator<treepair> ending = end();
//container.push_back(*root);
std::cout<<"printing from bst:"<<std::endl;
//for (;beginning!=ending;++beginning)

for(auto& beginning : *this)
{
std::cout<< beginning<<" ";
container.push_back(beginning);
}
std::cout<<std::endl;


//	container.push_back(*beginning);
//std::cout<<"print from vector"<<std::endl;
//for (auto& x : container)
//	std::cout<< x << " ";
//std::cout<<std::endl;

//std::cout<<"is vector empty? right after filling it  "<<container.empty()<<std::endl;

//size_t size = container.size();
//std::cout<<"size of vector"<<size<<std::endl;
clear();
balance_recursion(container);


/*    //NOW THIS IS NOT USEFUL 
while(!container.empty()){
//for (auto& x : container)
//	std::cout<< x << " ";
 ///////////std::iterator<Node<treepair>> init = container.begin()
container.erase(container.begin());
//std::cout<<std::endl;
std::cout<<"while cycle"<<std::endl;
Node<treepair> temp =*(container.begin());
insert(temp.value);
//insert(container[size/2].value);
//container.erase(container.begin()+size/2);
for (auto& x : container)
	std::cout<< x << " ";
std::cout<<std::endl;
//size = container.size();
std::cout<<"print from tree"<<std::endl;
for(auto& x : *this)
	std::cout<< x << " ";
std::cout<<std::endl;
 
}*/


std::cout<<"print from vector"<<std::endl;
for (auto& x : container)
	std::cout<< x << " ";
std::cout<<std::endl;

}

void balance_recursion(std::vector<Node<treepair>> to_split){
std::cout<<"print from recursion"<<std::endl;
for (auto& x : to_split)
	std::cout<< x << " ";
std::cout<<std::endl;


if (to_split.size()<2){
Node<treepair> temp1 =*(to_split.begin());
insert(temp1.value);
}else if(to_split.size()==2){
Node<treepair> temp1 =*(to_split.begin());
insert(temp1.value);
Node<treepair> temp2 =*(to_split.begin()+1);
insert(temp2.value);
}else{
	Node<treepair> temp2 = *(to_split.begin()+to_split.size()/2);
	insert(temp2.value);
	std::vector<Node<treepair>> one{};
	std::vector<Node<treepair>> two{}; 
	for(size_t i = 0; i<to_split.size()/2;i++)
		one.push_back(to_split[i]);
	
	for(size_t i = (to_split.size()/2)+1; i<to_split.size();i++)
		two.push_back(to_split[i]);
        balance_recursion(one);
	balance_recursion(two);
	}
}

//************************************************* PRINT

friend
std::ostream& operator<<(std::ostream& os,const bst& x)
	{
	std::cout<<"started printing"<<std::endl;
	//const_MyIterator<treepair> i = x.begin();
	//x.tree_minimum();
	//x.tree_maximum();	
	//std::cout<<"exited from tree min"<<std::endl;	
	//for(/*const_MyIterator<treepair> i = x.begin()*/;i!=x.end();++i)//CHANGED
	//	os << (*i)<<" ";
	//return os;
        for ( auto& i : x )
		os<<i<<" ";
	return os;
	}

};

/*
template<class key,class value>
std::ostream& operator<<(std::ostream& os, bst<key,value>& x);
	{
	MyIterator<treepair> i = x.begin();
	for(;i!=x.end();++i)
		os << (*i).value.first;
	return os;
	}*/

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
	return 0;
}

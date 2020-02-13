// std::iterator example
#include <iostream>     // std::cout
#include <iterator>     // std::iterator, std::input_iterator_tag


template<class T>
class Node;

template<class key,class value>
class bst;


template<class T>
class MyIterator : public std::iterator<std::forward_iterator_tag, Node<T>>
{
  Node<T>* pointer;
  Node<T>* last;
public:
  MyIterator(Node<T>* x,Node<T>* last_element) :pointer(x),last{last_element} {}
  MyIterator(const MyIterator& mit) : pointer(mit.pointer), last{mit.last} {}//copy constructor

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

template<class T>
class Node{




T value;
Node<T>* left;
Node<T>* right;
Node<T>* parent;
public:

Node(T element)
:value{element},left{nullptr},right{nullptr},parent{nullptr}{}


~Node(){std::cout<<"Removed Node"<<std::endl;}

T getValue(){
return value;
}


template<class key,class value>
friend class bst;

template<class S>
friend class MyIterator;

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
	os<<x.value<<std::endl;
	return os;
}
};




template<class key,class value>
class bst{
using treepair = std::pair<key,value>;

Node<treepair>* root;

public:
bst()
:root{nullptr} {std::cout<<"binary tree created"<<std::endl;}

//************copy semantics


bst(const bst& bintree):root{bintree.root} {
//copy_part(bintree.root, this);	

} 

  // copy assignment -- deep copy
bst& operator=(const bst& bintree){
	std::cout<<"copy assignment invoked"<<std::endl;
	//bst newbst{};
	/*(*this).*/clear();	
	/*(*this).*/insert(bintree.root->value);
	//if(*this.root == nullptr){ std::cout<<"NULLPTR";}
	//std::cout<<"Inserted Node root"<<newbst.root->value.first<<"_"<<bintree.root->value.second<<std::endl;//" having : left :"<<bintree.root->left->value.first<<"_";//<<newbst.root->left->value.second<<" right :"newbst.root->right->value.first<<"_"<<newbst.root->right->value.second<<
	copy_part(bintree.root, *this);
	//std::cout<<"AFTER COPY :"<<newbst<<std::endl;	
	return *this;
}
void copy_part(Node<treepair>* x, bst& bintree){
		std::cout<<bintree<<std::endl;
		if(x->left!=nullptr){
			bintree.insert(x->left->value);		
		        copy_part(x->left,bintree);
		}
		if(x->right!=nullptr){
			bintree.insert(x->right->value);		
		        copy_part(x->right,bintree);
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

MyIterator<treepair> begin()const{
	//std::cout<<"invoked begin()"<<std::endl;
	return MyIterator<treepair>{tree_minimum(),tree_maximum()};
}
MyIterator<treepair> end() const{
//std::cout<<"invoked end()"<<std::endl;
return MyIterator<treepair>{nullptr,tree_maximum()};

}



//**************************INSERTION
MyIterator<treepair> insert(treepair& z){
std::cout<<"INSERTION INVOKED adding pair"<<z.first<<" : "<<z.second<<std::endl;

Node<treepair>* newnode_z = new Node<treepair>{z};
std::cout<<"node created"<<std::endl;

if(root == nullptr)//empty tree
	{	
		root = newnode_z;
		//std::cout<<"new root :"<< (*root).value.first<<" : "<<(*root).value.second<<std::endl;
		MyIterator<treepair> x_root {newnode_z,tree_maximum()};
        	return x_root;
	}
	//start algorithm from the book
	Node<treepair>* y = nullptr;//is the parent of x
	Node<treepair>*	x = root;//is one of the children of y
	while(x != nullptr){//until we find an empty space
		y = x;
		if ((*newnode_z).value.first<(*x).value.first)
			x = (*x).left;
		else x= (*x).right;
		}
	(*newnode_z).parent = y; //so y is the parent of the new node
	//std::cout<<"parent found. it's "<<(*y).value.first<<" : "<<(*y).value.second<<std::endl;
	
	if (y == nullptr){
                //std::cout<< "root changed in unusual way"<<std::endl;
		root = newnode_z;
		}
	else if(((*newnode_z).value.first<(*y).value.first))		
		(*y).left = newnode_z;//now we identify the correct position of the new node accordingly to the parent
	else (*y).right = newnode_z;
	MyIterator<treepair> x_ret{newnode_z,tree_maximum()};
        return x_ret;
}


//**********************************EMPLACE
template< class... Types >
MyIterator<treepair> emplace(Types&&... args){
treepair newelement{args...};
MyIterator<treepair> x = insert(newelement);
return x;
}
//***********************************FIND
MyIterator<treepair> find(const key& x)
{
	return tree_search(root,x);	

}


MyIterator<treepair> tree_search(Node<treepair>* x, const key& y)
{
	if(x == nullptr)
	{
		std::cout<<"element not found"<<std::endl;
		return end();
	}
	else if (y == x->value.first)
	{
		MyIterator<treepair> i{x,tree_maximum()};
		std::cout<<"element found"<<std::endl;
		return i;
	}
	if(y < x->value.first) 
		return tree_search(x->left,y);
	else return tree_search(x->right,y);
}
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
//std::cout<<"NODE to remove points to left "<<remove->left->value.first<<"_"<<remove->right->value.second<<" and to right to "<<remove->right->value.first<<"_"<<remove->right->value.second<<std::endl;
	if (remove ==nullptr)
	{
		std::cout<<"Key not found"<<std::endl;
		return;
	}
	if (remove->left == nullptr){
		std::cout<<"Road A"<<std::endl;
		transplant(remove,remove->right);
	}
	else if (remove->right == nullptr){
		std::cout<<"Road B"<<std::endl;
		transplant(remove,remove->left);
	}
	else{
		std::cout<<"Road C"<<std::endl;
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
//************************************************* PRINT

friend
std::ostream& operator<<(std::ostream& os,const bst& x)
	{
	std::cout<<"started printing"<<std::endl;
	//MyIterator<treepair> i = x.begin();
	for(MyIterator<treepair> i = x.begin();i!=x.end();++i)
		os << (*i).getValue().first << "_"<<(*i).getValue().second<<" ";
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
	treepair pairF = treepair{3,33};
	
        using b_t_INT = bst<int,int>;
	b_t_INT bintree = b_t_INT();
	
	bintree.emplace(3,4);
	bintree.emplace(2,2);
	bintree.emplace(1,4);
	bintree.emplace(5,5);
	bintree.emplace(4,6);
	bintree.emplace(6,7);
	std::cout<<bintree<<std::endl;
	bintree.erase(3);
	MyIterator<treepair> beginning = bintree.begin();
	std::cout<<bintree<<std::endl;	

	
	bintree.insert(pairA);
	bintree.insert(pairB);
	bintree.insert(pairC);
        bintree.insert(pairD);
	bintree.insert(pairE);
	bintree.insert(pairF);
	
	bintree.emplace(4,6);
	bintree.emplace(8,9);
	bintree.emplace(27,7);
	bintree.emplace(34,8);
	//std::cout<< "Max key is: "<< bintree.tree_maximum()<<" Min key is: "<<	bintree.tree_minimum()<<std::endl;
	
	MyIterator<treepair> inizio = bintree.begin();
        MyIterator<treepair> fine = bintree.end();
	int counter{0};	
	for(;inizio!=fine;++inizio){
		counter++;
		//std::cout<< bintree;
		//std::cout<<"contati "<<counter<<" nodi."<<std::endl;
		std::cout<<(*inizio).getValue().first<<"_"<<(*inizio).getValue().second<< " ";		
			
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
	std::cout<<"TREE MINIMUM"<<std::endl;
	bintree_copy.tree_minimum();	
	std::cout<<"PRINT BINTREE_COPY"<<bintree_copy<<std::endl;

	
	
	std::cout<<bintree<<std::endl;
	
	//std::cout<<bintree_copy<<std::endl;
	b_t_INT bintree_copy_by_constructor{bintree};//made an empty tree
	
	
	//b_t_INT bintree_move{std::move(bintree)};
	//std::cout<<bintree_move<<std::endl;


	return 0;
}

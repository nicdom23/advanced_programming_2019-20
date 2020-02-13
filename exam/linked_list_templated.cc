#include<iostream>
#include <string>
#include <cassert>

//una lista contenente elementi di qualunque classe T

template<typename T>
class List;
template<typename T>
class Iterator;

template<typename T>
class Node{
public:
	Node(T s);//dichiarazione costruttore 
private:
	T data;
	Node<T>* previous;
	Node<T>* next;
	friend class List<T>;
	friend class Iterator<T>;//friend= list e iterator devono esaminare e modificare i membri dei dati della classe Node ////A friend class can access private and protected members of other class in which it is declared as friend. It is sometimes useful to allow a particular class to access private members of other class
};

template<typename T>
class List{
public:
	List();//empty list constructor
//*******************************new addictions
	List(const List<T>& b);//copy constructor
	~List(); //destructor
	List<T>& operator=(const List<T>& b);// assign another list to this list(copy assignment)
//*************************************
	void push_back(T s); //insert at the end
	void insert (Iterator<T> pos, T s); //insert s before position pos
	Iterator<T> erase(Iterator<T> pos); //erase object at position pos
	Iterator<T> begin();//return iterator pointing at first object
	Iterator<T> end(); //return iterator pointint at after-last object
private:
	
	//************** new addictions
	void copy(const List<T>& b);//copies another list into this list
	void free(); //deletes all the nodes in a list
	//******************
	Node<T>* first;
	Node<T>* last;
};




//iteratore indica una posizione nella lista, puntatore alla lista e puntatore al nodo che indica la posizione corrente
template<typename T>
class Iterator{
public:
	Iterator();//constructor of an iterator that doesn't point to any list
	T operator*() const; //use this instead of * operator (can work on const iterators)
	//use operator overloading
	void operator++(int dummy); 
 	void operator--(int dummy);
	bool operator==(Iterator<T> b) const;
 	bool operator!=(Iterator<T> b) const;
private:
	Node<T>* position;  //Nullptr se alla fine della lista
	Node<T>* last; //memorizzato per permettere di retrocedere con previous dalla dopo-ultima posizione della lista
friend class List<T>;
};

template<typename T>
Node<T>::Node(T s)//costruttore del nodo
: data{s},previous{nullptr},next{nullptr} {}

template<typename T>
List<T>::List()
:first{nullptr},last{nullptr} {std::cout<<"constructor of list"<<std::endl;}

template<typename T>
Iterator<T>::Iterator()
:position{nullptr} , last{nullptr} {}

//****************************************************  last addictions

template<typename T>
List<T>::~List()
{
std::cout<<"destructor of list"<<std::endl;
free();
}

template<typename T>
List<T>::List(const List<T>& b)
:first{nullptr},last{nullptr}
{
std::cout<<"copy of list"<<std::endl;
copy(b);
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& b)
{
	if (this != &b)
	{
		free();
		copy(b);
	}
	return *this;
}

//******************************************

//implementiamo per primi gli iteratori
//List::begin e List::end creano iteratori che puntano rispettivamente al primo nodo della lista e all'avant'ultima posizione della lista(nullptr)

template<typename T>
Iterator<T> List<T>::begin()////////begin
{
Iterator<T> iter{};
iter.position =first;
iter.last =last;
return iter;
}

template<typename T>
Iterator<T> List<T>::end() ////////end
{
Iterator<T> iter{};
iter.position = nullptr;
iter.last = last;
return iter;
}

template<typename T>
void Iterator<T>::operator++(int dummy)
{
assert(position !=nullptr);//here we have a source of exceptions
position = position -> next; //memorizes in position the pointer to the next node that is saved in the node that the iterator is pointing at 
}

template<typename T>
void Iterator<T>::operator--(int dummy)//no needed in a foward iterator
{
if(position == nullptr)//we are pointing at the after-last element of the list(remember that there is no fictious node at the end of the list to cover the role of the avant-last member of the lsit)
	position =last;
else
	position = position ->previous;
assert(position != nullptr);//we verify that we are not pointing at the pre-first element of the list, which has a nullptr
}

template<typename T>
T Iterator<T>::operator*() const
{
assert(position != nullptr);//source of exception, we cannot extract data from the avant-last element of the list, thought it might be a valid position for the iterator
return position -> data; 
}

//equal is instead a comparison of pointers, if they point at the same position then the two iterators are equal
template<typename T>
bool Iterator<T>::operator==(Iterator<T> b) const
{
return position == b.position; //this is a delegation from the equal of the pointers
}

template<typename T>
bool Iterator<T>::operator!=(Iterator<T> b) const
{
return !(*this == b); //this is a delegation from the equal of the == sign
}


//vediamo ora il push_back della lista
template<typename T>
void List<T>::push_back(T s)
{
	Node<T>* newnode = new Node<T>(s);//initialize a new node, nothing is said about next and previous(maybe they start as nullptrs)
	if(last == nullptr)//lista vuota
	{
		first = newnode;
		last =newnode;//we have inserted the first element on the list
	}
	else
	{
		newnode ->previous =last;
		last->next =newnode;
		last =newnode;//the added node is now the last node
	}
}

template<typename T>
void List<T>::insert(Iterator<T> iter, T s)
{
	if(iter.position == nullptr)//è solo il caso in cui iter punta all'avant-ultima posizione della lista
	{
		push_back(s);
		return;	
	}
	Node<T>*  after = iter.position;//the iter points at the future next node of th newly added node
	Node<T>* before =after -> previous; //the iter points at a node that has the pointer to the future previous node of the newly added node

	Node<T>* newnode = new Node<T>(s);
	//now we update all the pointers
	newnode->previous =before;
	newnode->next =after;
	after ->previous = newnode;//the after-the-new-node node has its previous pointer set to new
	if(before == nullptr)//there is no before-the-new-node node, we are inserting at the beginning
		first =newnode;//we just update first
	else
		before->next = newnode;//else we can update the before-the-new-node's next

}

template<typename T>
Iterator<T> List<T>::erase(Iterator<T> i)
{
	Iterator<T> iter = i;
	assert(iter.position != nullptr);//we must not be pointing at the after-final position//source of exception
	//here we can see all the types of nodes involved into the erasement	
	Node<T>* remove = iter.position;
	Node<T>* before = remove-> previous;
	Node<T>* after = remove -> next;//luckily here we have a bidirectional pointer so this is easier
	if(remove == first)//sees if there exist a before-the-eliminated-node node
		first == after;//we eliminate the first node;
	else
	before->next = after;//else after becomes the new next of the before-the-eliminated-node node
	//now we focus on the after-the-eliminated-node
	if(remove == last)//there is no after-the-eliminated-node node
		last == before;//we just update last in List
	else
		after->previous = before;//we update the previous of the after-the-eliminated-node node

	iter.position = after;//we update the iterator(now we can invoke insert to substitute the eliminated node
	delete remove; //remember to delete the pointer at the deleted node
	return iter;//we return the iterator pointing at the after-the-eliminated-node node
}

//********************************************new addicitons
template<typename T>
void List<T>::copy(const List<T>& b)
{
	for(Iterator<T> p = b.begin(); p != b.end;p++)
		push_back(*p);
}

template<typename T>
void List<T>::free()
{
	while( begin() != end() ){
		//std::cout<<"about to erase:"<<*begin()<<std::endl;	
		erase(begin());				
		}
}
//**********
int main(){
try{
List<std::string> citizens;

citizens.push_back("Miami");	
citizens.push_back("Vice");	
citizens.push_back("CSI");	
citizens.push_back("NewYork");

Iterator<std::string> pos;
//for(pos = citizens.begin();pos!=citizens.end();pos++)
//	std::cout<<*pos<<std::endl;
//std::cout << std::endl;
pos = citizens.begin();
pos++;
pos++;

//Iterator<std::string> expos = citizens.erase(pos);
pos = citizens.erase(pos);
//for(pos = citizens.begin();pos!=citizens.end();pos++)
//	std::cout<<*pos<<std::endl;
//std::cout << std::endl;

//citizens.insert(expos,"my grandma");
citizens.insert(pos,"my grandma");

//for(pos = citizens.begin();pos!=citizens.end();pos++)
//	std::cout<<*pos<<std::endl;
//std::cout << std::endl;
}catch(const std::logic_error& err)
{std::cout << err.what()<<std::endl;}
return 0;
}

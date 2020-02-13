#include<iostream>
#include <string>
#include <cassert>
//implementare una lista di string
class List;
class Iterator;

class Node{
public:
	Node(std::string s);//dichiarazione costruttore 
private:
	std::string data;
	Node* previous;
	Node* next;
	friend class List;
	friend class Iterator;//friend= list e iterator devono esaminare e modificare i membri dei dati della classe Node ////A friend class can access private and protected members of other class in which it is declared as friend. It is sometimes useful to allow a particular class to access private members of other class
};

class List{
public:
	List();//empty list constructor
	void push_back(std::string s); //insert at the end
	void insert (Iterator pos, std::string s); //insert s before position pos
	Iterator erase(Iterator pos); //erase object at position pos
	Iterator begin();//return iterator pointing at first object
	Iterator end(); //return iterator pointint at after-last object
private:
	Node* first;
	Node* last;
};




//iteratore indica una posizione nella lista, puntatore alla lista e puntatore al nodo che indica la posizione corrente
class Iterator{
public:
	Iterator();//constructor of an iterator that doesn't point to any list
	std::string operator*() const; //use this instead of * operator (can work on const iterators)
	//use operator overloading
	void operator++(int dummy); 
 	void operator--(int dummy);
	bool operator==(Iterator b) const;
 	bool operator!=(Iterator b) const;
private:
	Node* position;  //Nullptr se alla fine della lista
	Node* last; //memorizzato per permettere di retrocedere con previous dalla dopo-ultima posizione della lista
friend class List;
};
//****************************************************  last addictions
Node::Node(std::string s)//costruttore del nodo
: data{s},previous{nullptr},next{nullptr} {}

List::List()
:first{nullptr},last{nullptr} {}

Iterator::Iterator()
:position{nullptr} , last{nullptr} {}


//******************************************

//implementiamo per primi gli iteratori
//List::begin e List::end creano iteratori che puntano rispettivamente al primo nodo della lista e all'avant'ultima posizione della lista(nullptr)

Iterator List::begin()////////begin
{
Iterator iter{};
iter.position =first;
iter.last =last;
return iter;
}
Iterator List::end() ////////end
{
Iterator iter{};
iter.position = nullptr;
iter.last = last;
return iter;
}

void Iterator::operator++(int dummy)
{
assert(position !=nullptr);//here we have a source of exceptions
position = position -> next; //memorizes in position the pointer to the next node that is saved in the node that the iterator is pointing at 
}

void Iterator::operator--(int dummy)//no needed in a foward iterator
{
if(position == nullptr)//we are pointing at the after-last element of the list(remember that there is no fictious node at the end of the list to cover the role of the avant-last member of the lsit)
	position =last;
else
	position = position ->previous;
assert(position != nullptr);//we verify that we are not pointing at the pre-first element of the list, which has a nullptr
}


std::string Iterator::operator*() const
{
assert(position != nullptr);//source of exception, we cannot extract data from the avant-last element of the list, thought it might be a valid position for the iterator
return position -> data; 
}

//equal is instead a comparison of pointers, if they point at the same position then the two iterators are equal
bool Iterator::operator==(Iterator b) const
{
return position == b.position; //this is a delegation from the equal of the pointers
}
bool Iterator::operator!=(Iterator b) const
{
return !(*this == b); //this is a delegation from the equal of the == sign
}


//vediamo ora il push_back della lista
void List::push_back(std::string s)
{
	Node* newnode = new Node(s);//initialize a new node, nothing is said about next and previous(maybe they start as nullptrs)
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

void List::insert(Iterator iter, std::string s)
{
	if(iter.position == nullptr)//è solo il caso in cui iter punta all'avant-ultima posizione della lista
	{
		push_back(s);
		return;	
	}
	Node*  after = iter.position;//the iter points at the future next node of th newly added node
	Node* before =after -> previous; //the iter points at a node that has the pointer to the future previous node of the newly added node

	Node* newnode = new Node(s);
	//now we update all the pointers
	newnode->previous =before;
	newnode->next =after;
	after ->previous = newnode;//the after-the-new-node node has its previous pointer set to new
	if(before == nullptr)//there is no before-the-new-node node, we are inserting at the beginning
		first =newnode;//we just update first
	else
		before->next = newnode;//else we can update the before-the-new-node's next

}

Iterator List::erase(Iterator i)
{
	Iterator iter = i;
	assert(iter.position != nullptr);//we must not be pointing at the after-final position//source of exception
	//here we can see all the types of nodes involved into the erasement	
	Node* remove = iter.position;
	Node* before = remove-> previous;
	Node* after = remove -> next;//luckily here we have a bidirectional pointer so this is easier
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

//this code is unlinkable and i do not understand why????  I added the constructors and now the linker works
int main(){

List citizens;

citizens.push_back("Miami");	
citizens.push_back("Vice");	
citizens.push_back("CSI");	
citizens.push_back("NewYork");

Iterator pos;
for(pos = citizens.begin();pos!=citizens.end();pos++)
	std::cout<<*pos<<std::endl;
std::cout << std::endl;
pos = citizens.begin();
pos++;
pos++;

Iterator expos = citizens.erase(pos);
for(pos = citizens.begin();pos!=citizens.end();pos++)
	std::cout<<*pos<<std::endl;
std::cout << std::endl;

citizens.insert(expos,"my grandma");


for(pos = citizens.begin();pos!=citizens.end();pos++)
	std::cout<<*pos<<std::endl;
std::cout << std::endl;

return 0;
}

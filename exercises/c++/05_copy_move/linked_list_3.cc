#include <iostream>
#include <memory>  //unique pointere
//#include <vector>
#include "ap_error.h"
enum class method { push_back, push_front };

template <class value_type>
class List {
 public:
  // insert a new node with the value v according to the method m
  // this method should be used to fill the list

//move semantic

template<class OT>
void insert(OT&& v, const Insertion_method m);  


//copy semantic
void insert(const value_type& v, const Insertion_method m);

  // return the size of the list
  std::size_t size_of() const{
		return size;}

  // delete all the nodes of the list
  void reset(){ head.reset();
		size=0;
	std::cout << "reset"<<std::endl;}

  // constructor(s) for List
  	List() noexcept= default;
  // copy semantics
	//copuìy constructor
	List(const List& l);
//no noexcept needed
	//copy assignment
	List& operator=(const List&l);
  // move semantics   they dont throw exceptions
	//move constructor
	List(List&&) noexcept =default; //move on each memeber even on the unique pointer
	//move assignment1	
List& operator=(List&&) noexcept = default;
  // destructor

 private:
 

	Node* tail();


  // private struct node with the proper value_type
  struct Node {//nested class in the privare part of the list.it is theemplated in the same template of the class List,class node is not templated yet is inside a templated calss list
    value_type value;
    std::unique_ptr<Node> next;
	
    // implement suitable constructor(s) for node
	//Node():value{},next{nullptr}{std::cout<<"created empty node"<<std::endl;};    
	Node(const value_type& object,Node* next_node):value{object},next{next_node}{std::cout<<"created copy constructor node"<<std::endl;} 
	Node(value_type&& object,Node* next_node):next{next_node},value{std::move{object}}{std::cout<<"created move constructor node"<<std::endl;} 
	Node (const std::unique_ptr<node>& p): value{p->value}{
	if{p->next}
		next = std::make_unique<node>& p 
	}

//Node(value_type object):value{object},next{nullptr}{std::cout<<"half full node"<<std::endl;}
    // copy and move semantics if needed
    
    // destructor
	~Node(){std::cout<<"destroy"<<std::endl;}
  };

  // append the newly created node at the end of the list
  void push_back(const value_type& v);

void push_back(value_type&& v);

  // insert the newly created node in front of the list
  void push_front(const value_type& v);

template<class OT>
void push_front(OT&& v);

  std::unique_ptr<Node> head;
  std::size_t size;

template<class o>  //List<T>  wgìhere <T> is implicit   //we must template the friend call too
friend std::ostream& operator<<(std::ostream&,const List<o>&);
};


template <class T>
List::Node* tail(){
	auto tmp = head.get();	
	while(tmp->next)	
		tmp = tmp -> next.get();
//	segfault if empty List, no check here by design
	return tmp;
	
	}

//deep copy constructor

template <class T>
List<T>::List(const List& l){
	auto tmp = l.head.get();
	while(tmp){
	insert(tmp->value,Insertion_method::push_back);
	tmp=tmp->next.get
	
	}	
	head =std::make_unique<Node>(l)	
	}





template <class T>
void List<T>::insert(const T& v , const Insertion_method m){

if (!head){
	//head.reset(new node{v, nullptr});
	head = std::make_unique<Node>(v,nullptr); //is in c++14	
	return;
		}

	 switch (m) {
    case Insertion_method::push_front:
        std::cout << "option 1: push_front\n";
	// push front
	push_front(v);
        break;
    	case Insertion_method::push_back:
        std::cout << ",option 2: push back\n";
	push_back(v);
	break;
	default;
	API_ERROR(false)<<"unknow insertion method"
	break;
	};
}

void insert(value_type&& v, const Insertion_method m){

if (!head){
	//head.reset(new node{v, nullptr});
	head = std::make_unique<Node>(std::move(v),nullptr); //we use the move sematic to pass v as an rvalue  :: can we do better?? yes we can Template metaprogramming	
	return;
		}

	 switch (m) {
    case Insertion_method::push_front:
        std::cout << "option 1: push_front\n";
	// push front
	push_front(std::move(v));
        break;
    	case Insertion_method::push_back:
        std::cout << ",option 2: push back\n";
	push_back(std::move(v));
	break;
	default;
	API_ERROR(false)<<"unknow insertion method"
	break;
	};
}


//void f(Date&& d){ g(d) d is passed to g as an lvalue  g(std::move(d)) moved as an rvalue}

//template<Class T>

//void f(T&& d)//can be both an rvalue and an lvalue{ g(d) d is passed to g as an lvalue  g(std::move(d)) moved as an rvalue}


//perfect forward
//template<Class T>

//void f(T&& d)//can be both an rvalue and an lvalue{ g(d) d is passed to g as an lvalue  g(std::forward<T>(d)) moved as any value}


template <class T>
void List<T>::push_back(const T& v){
	Node* last =tail();
	//last->next.reset(new node{v,nullptr})
	last->next=std::make_unique<Node>(v,nullptr);
	}





template <class T>
void List<T>::push_front(const T& v){
	auto h = head.release();
	auto new_node = new Node{v,h};
	head.reset(new_node);

	//head =std::make_unique<Node>(v,head.release());
	// head.reset(new_node ...	
	}

/*Node* p=head.get();
			
	   while(!p->next){ 
				p=p->next.get();
			}


		p->next.reset(new Node{v,nullptr});
*/

template <class T>
std::ostream& operator<<(std::ostream& os, const List<T>& l){
	//everything is private,i need to say that you can share your secrets
	auto tmp = head.get();
	while(tmp){
	os << tmp->value<<" ";
	tmp = tmp->next.get();
	}	
	return os;
}

int main(){

try{
List<int> l{};
l.insert(1,Insertion_method::push_back);
l.insert(2,Insertion_method::push_back);
l.insert(4,Insertion_method::push_front);
std::cout << l<<std::endl;

auto ol =l ; //invokes the copy constructor which is a deep copy

l.insert(4,Insertion_method::push_front);
std:cout<<l<<std::endl;
std:cout<<l<<std::endl;

}

catch(std::exception& e){
std::cerr<<e.what()<<std::endl;}
catch(...){
std::cerr<< "unknown exception"<<std::endl;


}
return 0;

}

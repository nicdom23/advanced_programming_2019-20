#include<utility>
#include<memory>

enum class Insertion_method { push_back, push_front };//two methods inserted at the beginning or at the end

template <class value_type>
class List {
 public:
//insert the new node at the beginning or at the end(or also in the middle)
  
// insert a new node with the value v according to the method m
  // this method should be used to fill the list
  void insert(const value_type& v, const Insertion_method m){

	 switch (m) {
    case Insertion_method::push_front:
      std::cout << "option 1: push_front\n";
	node node(v,head);	
	head.reset(&node);	
	++size;
      break;
    case Insertion_method::push_back:
      std::cout << "option 2: push back\n";
	node* p=head.get;		
	   while(!p){
			node d =*head;
			p = d.
		}
			
	++size;
      break;
  }	
	}

void insert(value_type&& v, const Insertion_method m);//use move semantics

//int&& rvalue reference object that cannot appear on the left side of an equal sign:
//like numbers or objects returned by value For bulit in types the move semantuìics id ewual to the opy , if custom tyoe it will invoke the copy semantic google function std::vector:: pushback there is an overload for lvalue and rvalue
//move

//push back function insert v in a vector of vector,inside a new vector will be constructed copying v and it will be inserted, so if i change v i will ot change v inside the vv vector of vectors:::: before cc11 i insert a nev vector with 78 elements, before c++11,you copied the vector twice times, so it is a perfect candidate as a temporary object, you no need to copy this, just create it and move it into vv, rvaule,before c++11 we used twice the memory, construct +copy, instead after we create it and then copy it into the variable,uses half the memory::std::move calls a move even on an lvalue but it gives away the variable,and you get a segfault if you try to access the variable


  // return the size of the list
  std::size_t size() const{

	return size;}

  // delete all the nodes of the list
  void reset(){

	size = 0;}

  // constructor(s) for List
  List():size{0}{
	head.reset();}
  // copy semantics(copy constructor ccopy assignment)
  // move semantics
  
  // destructor

 private:
 
  // private struct node with the proper value_type
  struct node {//nested class
    value_type value;
    std::unique_ptr<node> next;

    // implement suitable constructor(s) for node
    node(value_type t,node*adress): value{t}, next{adress} {}
    // copy and move semantics if needed
    
    // destructor
	~node(){std::cout<<"destroy";}
  };

  // append the newly created node at the end of the list
  void push_back(const value_type& v){
	node()
		}
	void push_back(value_type&& v);
	  // insert the newly created node in front of the list
  void push_front(const value_type& v);
	void push_front(value_type&& v);
  std::unique_ptr<node> head;
  std::size_t size;
};

template <class T>
std::ostream& operator<<(std::ostream& os, const List<T>& l);//to print the value


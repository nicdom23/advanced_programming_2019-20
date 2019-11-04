#include <iostream>
#include <memory>
//#include <vector>

enum class Insertion_method { push_back, push_front };

template <class value_type>
class List {
 public:
  // insert a new node with the value v according to the method m
  // this method should be used to fill the list
  void insert(const value_type& v, const Insertion_method m){

	Node node_to_add{v,head};
	head.reset(&node_to_add);
	std::cout<<"inserted"<<v<<std::endl;
	size++;
	}

  // return the size of the list
  std::size_t size_of() const{
		return size;}

  // delete all the nodes of the list
  void reset(){ head.reset();
		size=0;}

  // constructor(s) for List
  	List():head{nullptr},size{0} { std::cout<<"created"<<std::endl;}
  // copy semantics
  // move semantics
  
  // destructor

 private:
 
  // private struct node with the proper value_type
  struct Node {
    value_type value;
    std::unique_ptr<Node> next;
	
    // implement suitable constructor(s) for node
	Node():value{},next{nullptr}{std::cout<<"created empty node"<<std::endl;};    
	Node(value_type object,std::unique_ptr<Node> next_node):value{object},next{next_node}{std::cout<<"created full node"<<std::endl;}
	Node(value_type object):value{object},next{nullptr}{std::cout<<"half full node"<<std::endl;}
    // copy and move semantics if needed
    
    // destructor
	~Node(){std::cout<<"destroy"<<std::endl;}
  };

  // append the newly created node at the end of the list
  void push_back(const value_type& v);

  // insert the newly created node in front of the list
  void push_front(const value_type& v);

  std::unique_ptr<Node> head;
  std::size_t size;
};

/*template <class T>
std::ostream& operator<<(std::ostream& os, const List<T>& l){
	node * node = head;	
	for(int i=0;i<size;++i){
	os<< (*node).value<<" ";
	node= (*node).next;
os<<std::endl;
return os;
}*/

int main(){

List<int> L1{};
L1.insert(1,Insertion_method::push_back);
L1.insert(2,Insertion_method::push_back);
std::cout<<L1.size_of()<<std::endl;
return 0;

}

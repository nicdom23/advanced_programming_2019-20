#include <iostream>
#include <stdexcept>
#include <string>
#include <new>
#include <exception>

struct TooFullException{//exception thrown when the array is full
	std::string message;
	
	TooFullException(const std::string& error)//constructor
	: message{error} {}
};

template<typename T>
struct placeholder{//first custom type
T value;

public:
placeholder() =default;
placeholder(T element): value{element} {}

friend 
std::ostream& operator<<(std::ostream& os, const placeholder& x){
	os<<x.value<<std::endl;
	return os;    	      }

};



template<typename T1,typename T2>
struct MyPair : public std::pair<T1,T2> //second custom type
{
		/*MyPair(T1 type1, T2 type2)
		{
			std::pair<T1,T2> a{type1,type2};
		}*/
	MyPair(){}
	using std::pair<T1,T2>::pair;//no parentheses needed at the end
		//MyPair(): std::pair(){};
	friend
	std::ostream& operator<<(std::ostream& os,const MyPair& x)//std::pair cannot be printed by itself
	{
		std::cout<< x.first << " : " << x.second;
		return os;
	}
};


template<typename T>
class MyIterator : public std::iterator<std::forward_iterator_tag, T>//custom iterator i found online
{
  T* p;
public:
  MyIterator(T* x) :p(x) {}
  MyIterator(const MyIterator& mit) : p(mit.p) {}
  MyIterator& operator++() {++p;return *this;}
  MyIterator operator++(int) {MyIterator tmp(*this); operator++(); return tmp;}
  bool operator==(const MyIterator& rhs) const {return p==rhs.p;}
  bool operator!=(const MyIterator& rhs) const {return p!=rhs.p;}
  T& operator*() {return *p;}
};



template<typename T>
class array{//third custom type, a regular array that is created in the heap

const int dimension = 10;//i decided, to simplify things to fix the array dimension
T* start;
int size;

public:
array()
:start{new T[dimension]}, size{0} {
/*std::cout<<"type of array: "<< typeid(T).name()<<std::endl;
std::cout<<"array dimension: "<< dimension<<std::endl;
start = new T[dimension];
std::cout <<"pointer "<<start<<std::endl;
*/

}

~array()
{
std::cout<<"Destructor Called"<<std::endl;
delete[] start;
}


MyIterator<T> insert(T item){
if (size == dimension-1)
	throw TooFullException{"Array is too small"};
start[size] = item;
MyIterator<T> x{start+size};
++size;
std::cout<<"size:"<<size<<std::endl;
return x;
}

template< typename... Types >//furries furries furry furries owo what's this
MyIterator<T> emplace(Types&&... args){

T newelement{args...};
MyIterator<T> newiterator= insert(newelement);
return newiterator;
}


 
MyIterator<T> begin(){
MyIterator<T> x{start};
return x;
}

MyIterator<T> end(){
MyIterator<T> x{start+size};
return x;
}


friend
std::ostream& operator<<(std::ostream& os, array& x)//printing the array
{
for(MyIterator<T> i = x.begin(); i != x.end(); ++i)
 	os<<*i<<" ";
os<<std::endl;
return os;
}



};



int main(){
try{
///////////////////////test with an array of integers
array<int> arrayInt{};
arrayInt.insert(8);
arrayInt.insert(9);
MyIterator<int> element_inside = arrayInt.insert(4);
arrayInt.insert(36);
arrayInt.insert(8);
arrayInt.insert(9);
arrayInt.insert(4);

std::cout<< arrayInt;
*element_inside = 99;//this works to change the pointed item in the list
std::cout << arrayInt;



using pair = MyPair<int,std::string>;//my custom type works
pair pairx{1,"string"};
std::cout<<pairx<<std::endl;
pair pairy{2,"string"};
std::cout<< pairy << std::endl;


array<pair> arrayPairs{};//this gives the exceptions catched below
arrayPairs.insert(pairx);
arrayPairs.insert(pairy);
std::cout<<arrayPairs<<std::endl;
MyIterator<pair> iter = arrayPairs.emplace(3,"string from emplace");
std::cout<<arrayPairs<<std::endl;
*iter = {3.5,"String that substitutes"};
std::cout<<arrayPairs<<std::endl;


using pairInt = MyPair<int,int>;
array<pairInt> arrayPairsInt{};//this also doesnt work


using ph = placeholder<std::string>;//this other custom type works
ph item1{"first"};
ph item2{"second"};

array<ph> arrayCustom{};
arrayCustom.insert(item1);
arrayCustom.insert(item2);
arrayCustom.emplace("third from emplace");
arrayCustom.emplace("added again from emplace");
std::cout<< arrayCustom <<std::endl;



array<std::string> arrayString{};
std::string itemString1{"first"};
std::string itemString2{"second"};
std::string itemString3{"third"};
std::string itemString4{"fourth"};
std::string itemString5{"fifth"};

arrayString.insert("zeroeth");
arrayString.insert("zeroeth");
arrayString.insert(itemString1);
arrayString.insert(itemString2);
arrayString.insert(itemString3);
std::cout<<arrayString<<std::endl;
arrayString.insert(itemString4);
arrayString.insert(itemString5);
std::cout<<arrayString<<std::endl;
    //the code above is not executed because the exception blocks the execution

}catch(const TooFullException& e){
	std::cerr <<"ERROR: "<< e.message << std::endl;
	return 1;

}catch(const std::bad_array_new_length& e){
	std::cerr<<"ERROR: "<<e.what()<<std::endl;
	return 2;
}catch(const std::bad_alloc& e){
	std::cerr<<"ERROR: "<<e.what()<<std::endl;
	return 3;

}catch(...){
	std::cout<<"Unknow Exception"<<std::endl;
}
return 0;
}

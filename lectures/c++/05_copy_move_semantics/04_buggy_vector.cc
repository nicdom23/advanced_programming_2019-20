#include <iostream>

template <typename T>
class Vector {
  T* elem;
  std::size_t _size;

 public:
//what does explicit do? each constructor that takes only an argument defines an implicit conversion rule from one obj to the other. explicit avoids to define implicit rules to define a variable
//EXAMPLE of print:: it applies implicit rule to create a vector if it has an int
  explicit Vector(const std::size_t length)
      : elem{new T[length]{}}, _size{length} {} //all elements are initialzied/else
                        //the cutly braces are important, they initialize data/Else they are uninitaialzied
  ~Vector() { delete[] elem; }

  const T& operator[](const std::size_t& i) const { return elem[i]; }
  T& operator[](const std::size_t& i) { return elem[i]; }

  std::size_t size() const { return _size; }

  // range-for
  const T* begin() const { return elem; }
  T* begin() { return elem; }

  const T* end() const { return elem + size(); }
  T* end() { return elem + size(); }
};

void print(const Vector<int>& v)
{for (auto x:v)
std::cout<<x<<std::endl;
}
int main() {
  Vector<int> v1{3};
  v1[0] = 1;
  v1[1] = 2;
  v1[2] = 3;

print(v1);//we have a print of valuse

print(1); //used to explain the explicit codeword //without the explicitt, it prints a 0
/*{

auto it = v1.begin():
auto stop = v1.end();
	for(;it!=stop; ++it)
	{
		const auto x =*it	
	}

}*/


  std::cout << "v1: ";
  for (const auto x : v1)// loop througout the container  you need to specify the type of the x, it woud need begin and end
    std::cout << x << " ";
  std::cout << std::endl;

  Vector<int> v2{v1};  // default copy constructor

  std::cout << "v2 after default copy ctor: ";
  for (const auto x : v2)
    std::cout << x << " ";
  std::cout << std::endl;

  v1[0] = 99;

  std::cout << "v2 after v1 has been changed: ";
  for (const auto x : v2)
    std::cout << x << " ";
  std::cout << std::endl;

  v2[1] = -999;//are the two objects?
//two different objects in the vector case
//WRONG BUGGY PROGRAM;WE GET AN ERROR, we got a compire defautl action, compiler doesnt know the meaning of a vector, it can only copy by value,,In a default compiler geneartaed copy constructor then copy each memeber by value(PROBLEM WITH POINTERS)for built-in types ELSE we invoke the copy sematic for a custom type, if there is none we get a copiler error
//I try to delete a memotìry space twice  we have a shallow copy a cheap copy [][][][][][][]array in the heap elementt in the stack that points in the heap memory location,then i crate v2 as the default copy constructor,the compiler does a copy by value of the pointer, so the pointers point to the same memory space..V1 V"refer to the same big array in my memory, they are entalged RAII resour acquisition is initialization doesnt work well because memory is alraedy freed once 

  std::cout << "v1 after v2 has been changed: ";
  for (const auto x : v1)
    std::cout << x << " ";
  std::cout << std::endl;

  return 0;
}   //is the tryining to understand if thhe compiler geneatro copy constructor fits the definition of array vector

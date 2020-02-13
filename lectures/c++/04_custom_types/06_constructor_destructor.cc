#include <iostream>
#include <string>
//how does std::vector work without defining a new memory allocation on heap
//or a delete
struct Foo {
  int _i;
  double _d;
  std::string _s;

  Foo(const int i, const double d,
      const std::string& s);  // custom constructor  no return type, same name of the class

  Foo();  // default constructor  many constructors are possible

  ~Foo();  // destructor is unique  invoked when variable is out of scope it commands the delete in std::vector
};
//malloc on C  then use free()
//new opeator in c++ will call the constructor delete()will call the destructor

Foo::Foo(const int i, const double d, const std::string& s)//signature of the constructor
    : _i{2*i},_d{d},_s{s}//use curly braces //inside this limbo,where variables are constructed
//i can just consruct things not call std::cout,but can i call functions
	// _i, _d, _s must be initialized in the same order they have been declared
//actual region
{ //_i{i}//wrong
	//_i=i; //works but the curly braces are faster ; first you constuct then you copy the value
  std::cout << "custom ctor\n";//variables are already constructed
  // if you want/need you can use _i, _d, _s and change their value
  // with the usual notation +,-,=,*, call a function..
  // don't use {} because this notation is reserved for the
  // construction of the variables and at this point they have already
  // been constructed
}

Foo::Foo() {//no column name
  std::cout << "default ctor\n";  // what happens to our member variables? initialized at random
}//used to make an array of these object

Foo::~Foo() {//destructor
  std::cout << "dtor\n";
}

std::ostream& operator<<(std::ostream& os, const Foo& f) {//operator overloading
  os << f._i << " " << f._d << " " << f._s << std::endl;
  return os;
}

int main() {
  Foo f0;    // call default ctor
  Foo f1{};  // call default ctor
  // Foo f2(); // compiler error, no arguments between parentheses,calls a function

  Foo f2{8, 2.2, "hello"};//also curly braces
 //Foo f2(8,2.2,"hello") works too;  
  std::cout << "f0: " << f0 << "f1: " << f1 << "f2: " << f2 << std::endl;
   ///first argument///sec.argument// before and after the operator            
  // the destructor is called when the variable goes out of scope
  //never invoke a destructor by hand
  //ddestructs by f2 to f1 to f0 destruct bottom to top
  //even the varables in the classes are destructed bottom to top
  return 0;
}

#include <algorithm>  // std::copy
#include <iostream>
#include <memory>

template <typename T>
class Vector {
  std::size_t _size;
  std::unique_ptr<T[]> elem;//avoid to call delete on the destructor
//it will call delete on the owned object once it is out of scope

 public:
  // custom ctor
  explicit Vector(const std::size_t length)
      : _size{length}, elem{new T[length]{}} {
    std::cout << "custom ctor\n";
  }

  // Vector(const std::initializer_list<T> args)
  //     : _size{args.size()}, elem{new T[_size]} {
  //   std::cout << "list ctor\n";
  //   std::copy(args.begin(), args.end(), begin());
  // }
 
  //e.g. std::vector<int>{1,2,3,4,5}//std initializer is created passed by value
   //start to copy from the begin//  initialize the container with the values inserted before
//	std::vector<int>{4} initializer list constructor
//	std::vector<int>(4) no ambiguity, 4 is the size of the array



  // default ctor //No arguments
  Vector() { std::cout << "default ctor\n"; }  // _size uninitialized
  // Vector() : _size{}, elem{} { std::cout << "default ctor\n"; } // this could
  // be better Vector() = default;

  ~Vector() = default;

  /////////////////////////
  // copy semantics

  // copy ctor -- deep copy
  Vector(const Vector& v); //const because you could modify the other

  // copy assignment -- deep copy
  Vector& operator=(const Vector& v);
  // end of copy semantics
  /////////////////////////

  /////////////////////////
  // move semantics    we impleemtned the swap function we can do something better: here we are::: i want to swap two contents auto x =a a = b b= x we use copy semantics---->>>the move semantics will be better than before auto x =std::move(a) a = std::move(b) b=std::move(x)
// x = std::move(a)
  // move ctor   // l-values reference are only on the left end side of the equal
//v is R value
  Vector(Vector&& v) : _size{std::move(v._size)}, elem{std::move(v.elem)} {
    std::cout << "move ctor\n";
  }//move of bulit in types is copy   Use unique pointers, but have nice features

  // Vector(Vector&& v) = default; // ok
					//be carfuel &&guys will die at the end of the line
  // move assignment
  Vector& operator=(Vector&& v) {
    std::cout << "move assignment\n";
    _size = std::move(v._size);
    elem = std::move(v.elem);
    return *this;//pointer to the instantiated object, to yourself(this refers to the object fo which a member function is invoked)
  }//elementwise move, it is not a constructor, a move generatied by the constructor would be fine too

  // Vector& operator=(Vector&& v) = default; // ok

  // end move semantics
  /////////////////////////

  const T& operator[](const std::size_t& i) const { return elem[i]; }
  T& operator[](const std::size_t& i) { return elem[i]; }

  std::size_t size() const { return _size; }

  // range-for
  const T* begin() const { return &elem[0]; }
  T* begin() { return &elem[0]; }

  const T* end() const { return &elem[_size]; }
  T* end() { return &elem[_size]; }
};

// copy ctor
template <typename T> //friend keyword  you can access to various elements
//we want to do an elemnetwise copy
Vector<T>::Vector(const Vector& v) : _size{v._size}, elem{new T[_size]} {
  std::cout << "copy ctor\n";
  std::copy(v.begin(), v.end(), begin());//in the algorithm header,start from begin
}

// copy assignment
template <typename T> //++ i increments itself and returns itself i++ maeks a copy and adds to itseld and then retunr the copy
Vector<T>& Vector<T>::operator=(const Vector& v) {
  std::cout << "copy assignment (\n";

  // we could decide that this operation is allowed if and only if
  // _size == v._size
  //

  elem.reset();//funct of unique pointer       // first of all clean my memory
  auto tmp = v;              // then use copy ctor (it is invoked)
  (*this) = std::move(tmp);  // steal this then finally move assignment
    //this neds to be dereferenced
  // or we do everything by hand..
  // and we can do not reset and call new again if the sizes are suitable

  std::cout << ")\n";
  return *this;

  // is this approach consistent with self-assignment vx=vx?
}

template <typename T>
// why we return by value?
Vector<T> operator+(const Vector<T>& lhs, const Vector<T>& rhs) {
  const auto size = lhs.size(); //no check for the same size

  // how we should check that the two vectors have the same size? well see it

  Vector<T> res(size);//new vector made
  for (std::size_t i = 0; i < size; ++i)
    res[i] = lhs[i] + rhs[i];

  return res;  //can be returned only by value  point by reference will delete himself soon enough
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
  for (const auto& x : v)
    os << x << " ";
  os << std::endl;
  return os;
}

int main() {
  std::cout << "Vector<int> v0; calls\n";
  Vector<int> v0;
  std::cout << v0.size() << "\n";
  std::cout << "Vector<int> v00{}; calls\n";
  Vector<int> v00{};
  std::cout << v00.size() << "\n";

  std::cout << "\nVector<double> v1{5}; calls\n";
  Vector<double> v1{5};//now there is ambiguity, this constructor has the ighrst priority, so our vector v1 will have one element that is 5
//if i eant to call the constructor that takes one argument i use the round braces
//vector<double> v1(5)

//std::vector<int>{4,2} 2 elements who are 4 and 2
//std::vector<int>(4,2) 4 elements whose value is 2

//when you invoke a constructor you put the initialize list constructor, there is ambiguity initializer list wins ambiguity, either use round braces
  std::cout << "\nVector<double> v2 = v1; calls\n";
  Vector<double> v2 = v1;
  std::cout << "\nv2 = Vector<double>{7}; calls\n";
  v2 = Vector<double>{7};
  std::cout << "\nVector<double> v3{std::move(v1)}; calls\n";
  Vector<double> v3{std::move(v1)};  // now v1 should not be used
  std::cout << "\nv3 = v2; calls\n";
  v3 = v2;
  std::cout << "\nv2 = " << v2;
  std::cout << "v3 = " << v3;

//auto& ov = v
//ov = v segfault




  std::cout << "\nassign some values to v3\n";
  {
    // auto i = v3.size();
    // while (i--)
    //   v3[i] = i;

    int c = 0;
    for (auto& x : v3)
      x = c++;
  }
  // v3=v3;
  std::cout << "\nv2 = " << v2;
  std::cout << "v3 = " << v3;

  std::cout << "\nVector<double> v4{v3 + v3}; calls\n";
  Vector<double> v4{v3 + v3};

  std::cout << "v4 = " << v4;

  std::cout << "\nNRVO: Named Return Value Optimization\n";
//compiler applies an optimization cepps all the call to the mobe functionsa the object is contstruceted in the stack frame of the callee (No call to the move constructor) At the end v4 is res and didnt call move constructor   ----------C++11 ARE ADDED NOW
  std::cout << "\nv4 = v3 + v3 + v2 + v3; calls\n";
  v4 = v3 + v3 + v2 + v3;
  std::cout << "v4 = " << v4;

  return 0;
}

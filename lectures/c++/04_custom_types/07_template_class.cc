#include <iostream>
#include <string>

template <typename num>//vector of any type
class Vector {
  num* elem;//pointer to the first element
  std::size_t _size;

 public:
  Vector(const std::size_t size) : elem{new num[size]}, _size{size} {}//null body, no post processing

  // automatically release the acquired memory :Resource Acquisition Is Initialization
  ~Vector() { delete[] elem; }

  // try to remove the const and recompile 
  std::size_t size()const{ return _size; }//the value is not changed if function is called

  num& operator[](const std::size_t i) { return elem[i]; }

  // try to comment this line and recompile ,the next operator overoad doesnt work
  const num& operator[](const std::size_t i) const { return elem[i]; }
};                                          //|
                                            //|
template <typename T>                      // v 
std::ostream& operator<<(std::ostream& os,const Vector<T>& v) {//verifica di non
  for (auto i = 0u; i < v.size(); ++i)
    os << "v[" << i << "] = " << v[i] << std::endl;//
  return os;
}

int main() {
  Vector<double> v{10};

  for (auto i = 0u; i < v.size(); ++i)
    v[i] = i;

  std::cout << v << std::endl;

  Vector<double>* pv{&v};

  // first dereference the pointer, then I can use the defined operators
  (*pv)[0] = -99.999;

  pv->operator[](1) = 77777.3333;  // or I call the function by name

  std::cout << *pv << std::endl;

  Vector<double>& rv{v};

  rv[5] = 555; //works ok  //copies content inside main array

  std::cout << v << std::endl;

  return 0;
}

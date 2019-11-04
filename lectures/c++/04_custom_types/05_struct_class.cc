#include <array>
#include <iostream>
#include <vector>
//structures in C
//Classes in C++ : we can add  data and functions too
struct Point_s {//not the same struct as  in c //it is a new type
//default visibility of sybols change with class
  double x;
  double y;
  void print();
};  // note ; at the end

void Point_s::print() {//now the function has a namespace
  std::cout << "Structure. x = " << x << "; y = " << y << std::endl;//x and y ca be called because wwe are inside the class
}

class Point_c {//here not everything is public but defaut visibility of the symbols is private!!
private: //implied
  double x;
  double y;

 public: //defined a function is inside the class and can access private variables
  void print() {
    std::cout << "Class. x = " << x << "; y = " << y << std::endl;
  }  // note no ; at the end
};   // note ; at the end of the declaration

int main() {
  Point_s ps;
  ps.x = 9.9;//data can be accessed
  ps.y = 3. / 7;

  ps.print();
//you can predefine the operators, ITS OPERATORS OVERLOADING, the sum operator, the star operator, the or operator
  Point_c pc;
  // pc.x =7.6; // error x and y are private
  pc.print();  // I can access private data through public functions
//goal of the class : read every c++ code  //interface of a class, set of public variables and functions
  
  Point_s* p = &ps; //a pointer to a class,has the same size of adresses, and can be easier to send than the class variable
  p->x = 0.0;//instead of . we use ->
  p->print();

  auto& pr = ps; //reference to a type, auto works too pr is a reference to ps
  ++pr.x; //incrementing by 1 the x member of pr
  pr.print();//compiler error to find the type of the variable

  Point_s array_of_structs[8];  // built-in array
  array_of_structs[0].x = 1;
  array_of_structs[0].y = 2;

  std::array<Point_s, 5> as;
  as[3].x = 3;

  std::vector<Point_s> vs;
  vs.push_back(ps);//a function defined in class std::vector
				  //push_back == copy
  vs[0].x = 999;
  ps.x = 11;
  ps.print();
  vs[0].print();

  return 0;
}

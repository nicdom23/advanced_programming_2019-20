#include <assert.h>
#include <cmath>
#include <iostream>
#define NDEBUG
#include "ap_error.h"

// implment a square root function that "deals with" negative
// numbers. Moreover according to the logic of the program, d should
// never be greater than 50
double square_root(const double d);

int main() {
  try {
    std::cout << "please insert a number\n";
    double number;
    std::cin >> number;
    double d = square_root(number);
    std::cout << "square root of " << number << " is " << d << '\n';
    return 0;
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return 1;
  } catch (...) {
    std::cerr << "Unknown exception. Aborting.\n";
    return 3;
  }
}

double square_root(const double d) {
  // test the pre-conditions
  assert(d >= 0 && d <= 50);  // provided by C, no execeptions
     //yet it aborts the program, strange enough it doesn't work if you define NDEBUG in the header
   //AP_ASSERT(d>=0 && d<=50) <<  "d should be in the range [0,50]"; //Same fucntion as assert
//can be removed by ??? 
/*
if you think that checks slow down your code you can use assert to disable them,depending on assemble flags

if it depends on internal logic use
error always check and if clasues slow down the code
no unnecessary checks leave tests as asserts

bugs :found out by the compilers
bugs:internal logic bug :found out by asserts
bugs : wrong resut is gotten

//assert works only in debug mode and is not imported in the final build
//you just have to write #define NDEBUG  or compile with -DNDEBUG, so this is a different way to help the programmer in error handling
//"Therefore, this macro is designed to capture programming errors, not user or run-time errors, since it is generally disabled after a program exits its debugging phase"
//it is contained in the header <assert.h>

//in "ap_error.h" we have that "If a condition must be always checked (i.e., also when the code is
 * compiled in release mode), use the AP_ERROR interface(instead of AP_ASSERT)"


*/
  //AP_ASSERT_IN_RANGE(d,0,50);
  return sqrt(d);
}

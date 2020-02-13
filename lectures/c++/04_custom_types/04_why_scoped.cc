#include <iostream>

enum month { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
          //the rests are incrememted by 1
//using namespace std;//do not use into a header to avoid importantion
using std::cout; //single "use"
using std::endl; //element can be called alone

int main() {
  cout << nov << endl;
  // cout << dec << endl; //doesnt compile with this uncommented because of namecrashing
  //namecrashing with using namespace std, instead use scoped enum
  

  return 0;
}

//WHY NAMECRASHING?  month::dec vs std::dec the latter is used to write in decimal

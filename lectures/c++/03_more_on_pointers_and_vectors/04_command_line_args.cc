#include <iostream>

int main(int argc, char* argv[]) {//equal to char** argv
  for (auto i = 0; i < argc; ++i)
    std::cout << "argv[" << i << "] = " << argv[i] << std::endl;
  return 0;
}    //command line aarguments argv is  an array of strings

	//converting string to a number must be casted, well see at the course

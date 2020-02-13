extern void hello_from_cpp(void);  //functions get external linkage by default, extern could be avoided
//the linker complains if you write
// void hello();
//int main(){
// hello(1,2,3,4); this does not give an error in the compiler, you need to write void hello(void)
//}

//C++ is strongly typed and strongly checked
//C is strongly typed and weakly checked
int main(int argc, char* argv[]) {
  hello_from_cpp();
  return 0;
}

//when linking, the linker must be compliant with the language for which the main is written
// we have to link to the c++ library    -lstdc++   binaries are indipendent from the language

//src ->language dependent to intermediate language-> optimization->assemly->produce a .o code which is an ELF format

//here we link against a cpp library    try to write file main.oe

//do not mix compilers

// a c++ linker links automatically to c libraries, the opposite doesn't work


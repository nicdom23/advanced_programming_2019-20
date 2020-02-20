#include <iostream>     // std::cout
#include <iterator>     // std::iterator, std::input_iterator_tag
#include <vector>       // std::vector
#include "header.h"
#include <string>

int main () {
 try{   
	using treepair = std::pair<const int,std::string>;
	using b_t = bst<int,std::string>;
	

	std::cout<<"Test on an empty tree"<<std::endl;
	b_t emptyBST = b_t{};//construcor 1
	std::cout<<"size: "<<emptyBST.size()<<std::endl;
	emptyBST.balance();
	std::cout<< std::boolalpha;
	emptyBST.find(4);
	//emptyBST[5]; works but adds an element to the aray
	std::cout<<"Is it empty? "<<emptyBST.isEmpty()<<std::endl;
	std::cout<<"Print of empty bst: "<<emptyBST<<std::endl;
	b_t::const_iterator iterat_begin = emptyBST.cbegin();	
	b_t::const_iterator iterat_end = emptyBST.cend();
	(void) iterat_begin; (void) iterat_end;	
	b_t copied_emptyBST{emptyBST};//construcor 2
	copied_emptyBST = emptyBST;	
	emptyBST.clear();
	b_t moved_emptyBST{std::move(emptyBST)};//construcor 3
	
	
	treepair pairA = treepair{80,"eighty"};
	treepair pairB = treepair{17,"seventeen"};
	treepair pairC = treepair{45,"forthy-five"};
		
        
	b_t bintree = b_t();//construcor 4
	

	std::cout<<"Test for emplace"<<std::endl;
	bintree.emplace(3,"three");
	bintree.emplace(2,"two");
	bintree.emplace(1,"four");
	bintree.emplace(5,"five");
	bintree.emplace(5,"five");
	bintree.emplace(4,"four");
	bintree.emplace(6,"six");
	
	std::cout<<"The bst so far:"<<std::endl;
	std::cout<<bintree<<std::endl;
	
	bintree.erase(3);
	
	std::cout<<"key 3 erased"<<bintree<<std::endl;	

	std::cout<<"Test for insert"<<std::endl;
	bintree.insert(pairA);
	bintree.insert(pairB);
	bintree.insert(pairC);
        
	std::cout<<"Test for rvalue insert"<<std::endl;
	treepair pairF = treepair{70,"seventy"};
	bintree.insert(std::move(pairF));
	bintree.insert(treepair{71,"seventy-one"});
	bintree.insert({72,"seventy-two"});
	
	
	std::cout<<"Counted "<<bintree.size()<<" nodes."<<std::endl;  
	
	std::cout<<"The bst so far:"<<std::endl;
	std::cout<<bintree<<std::endl;	


	bintree.find(34);
	bintree.find(2);
	bintree.find(7);
	bintree.find(5);

	std::cout<<"erase node 34"<<std::endl;
	bintree.erase(34);
	
	std::cout<<"erase node 1"<<std::endl;
	bintree.erase(1);
	
	std::cout<<"erase node 17"<<std::endl;
	bintree.erase(17);
	
	
	
	b_t bintree_copy{};//made an empty tree//construcor 5
	std::cout<<"copy assignment test"<<std::endl;
	bintree_copy = bintree;
	
	std::cout<<"Original bst :"<<bintree<<std::endl;
	std::cout<<"Copy bst :"<<bintree_copy<<std::endl;
	std::cout<<std::endl<<"erase node 5 from copy bst"<<std::endl;	
	bintree_copy.erase(5);
	std::cout<<"Copy bst after erase :"<<bintree_copy<<std::endl;
	std::cout<<"Original bst :"<<bintree<<std::endl;
		
	std::cout<<"Test of copy constructor"<<std::endl;
	b_t bintree_copy_by_constructor{bintree};//made a copy constructor tree//construcor 6
	
	std::cout<<"Copied bst"<<bintree_copy_by_constructor<<std::endl;
	
	std::cout<<std::endl<<"Emplace and erase on copied bst"<<std::endl;
	bintree_copy_by_constructor.emplace(8,"eight");
	bintree_copy_by_constructor.erase(4);
	
	std::cout<<"Original bst"<<bintree<<std::endl;	
	std::cout<<"Copied bst"<<bintree_copy_by_constructor<<std::endl;

	std::cout<<std::endl<<"Test of move constructor"<<std::endl;	
	////b_t bintree_move{std::move(bintree_copy_by_constructor)};//constructor 7 IS THIS THE SOURCE OF ERROR? Yes, I cannot delete a bst in a moved-from state
	//std::cout<<"Moved bst"<<bintree_move<<std::endl;
	

	int i = 99;
	int j = 100;
	bintree.emplace(99,"ninety-nine");
	bintree.emplace(5,"five");
	std::cout<<std::endl<<"Test of lvalue find"<<std::endl;	
 	std::cout<<"SEARCHING FOR KEY "<<i<< " ->returned value: " <<bintree[i]<<std::endl;
	std::cout<<"SEARCHING FOR KEY "<<j<< " ->returned value: " <<bintree[j]<<std::endl;
	
	std::cout<<std::endl<<"Test of move constructor"<<std::endl;	
	std::cout<<"SEARCHING FOR KEY 100  -> returned value:"<<bintree[100]<<std::endl;
	std::cout<<"SEARCHING FOR KEY 5  -> returned value :"<<bintree[5]<<std::endl;
 	
	
	std::cout<<std::endl<<"Test of const type bst"<<std::endl;
	const b_t const_bintree = b_t{bintree};//construcor 8
	std::cout<<const_bintree<<std::endl;
	//const_bintree.emplace(3,"three"); //Doesn't work
	//const_bintree.insert({10,"ten"}); //Doesn't work
		
	std::cout<<"###############TEST ON ITERATORS###########"<<std::endl;	
	std::cout<<"before modification"<<bintree<<std::endl;
	b_t::iterator iter_1 = bintree.find(5);
	b_t::iterator iter_2 = bintree.find(99);
		
	(*iter_1).value.second = "Nine-hundred-ninety-six"; //this is possible
	//(*iter_1).value.first = 996; //this ruins the tree //FIXED IF KEY IS CONSTANT
	(void) iter_2;	
	//*iter_2 = *iter_1;  //this crashes the code, don't know how
	std::cout<<"after modification"<<bintree<<std::endl;


	//const_MyIterator<treepair> const_iter = const_bintree.find(5);
	//*const_iter = pairA; //THIS DOESN'T WORK
        //std::cout<<const_bintree<<std::endl;

	std::cout<<"###########################TEST ON BALANCE##########"<<std::endl;
	//std::cout<<bintree<<std::endl;
	bintree.balance();
	//bintree.clear();
	std::cout<<bintree<<std::endl;		
	std::cout<<"counted "<< bintree.size()<<" nodes "<<std::endl;	
	
	
	//const_MyIterator<treepair> iterate = const_bintree[70]; //subscription doesn't work on constant bst-s
	

/*this was just a trivial test to throw the FullMemoryException	

	int counter{0};	

	while(true){
	counter++;	
	bintree.emplace(counter,"number");}
*/

	
	return 0;
}catch(const FullMemoryException& e){
	std::cerr<<"Memory is full. Aborting.\n";
	return 1;
}catch (...) {
    std::cerr << "Unknown exception. Aborting.\n";
    return 1;
  }
}

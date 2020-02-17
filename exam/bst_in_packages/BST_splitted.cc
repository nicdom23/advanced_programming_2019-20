// std::iterator example
#ifndef header
#define header
#include <iostream>     // std::cout
#include <iterator>     // std::iterator, std::input_iterator_tag
#include <vector>       // std::vector
#endif
#include "header.h"

int main () {
 
	using treepair = std::pair<int,int>;
	treepair pairA = treepair{5,34};
	treepair pairB = treepair{17,88};
	treepair pairC = treepair{45,2};
	treepair pairD = treepair{1,5};
	treepair pairE = treepair{6,12};
	
        using b_t_INT = bst<int,int>;
	b_t_INT bintree = b_t_INT();
	

	
	bintree.emplace(3,4);
	bintree.emplace(2,2);
	bintree.emplace(1,4);
	bintree.emplace(5,5);
	bintree.emplace(5,45);
	bintree.emplace(5,34);
	bintree.emplace(4,6);
	bintree.emplace(6,7);
	
	std::cout<<"FIRST PRINT:"<<std::endl;
	//std::cout<<bintree<<std::endl;
	
	bintree.erase(3);
	MyIterator<treepair> beginning = bintree.begin();
	//std::cout<<bintree<<std::endl;	

	
	bintree.insert(pairA);
	bintree.insert(pairB);
	bintree.insert(pairC);
        bintree.insert(pairD);
	bintree.insert(pairE);
	
	treepair pairF = treepair{70,33};
	
	bintree.insert(std::move(pairF));//TEST FOR RVALUE INSERTION
	bintree.insert(treepair{71,6});
	bintree.insert({72,77});
	bintree.emplace(4,6);
	bintree.emplace(8,9);
	bintree.emplace(27,7);
	bintree.emplace(34,8);
	bintree.emplace(99,99);//TEST FOR SUBSCRIPTION
	//std::cout<< "Max key is: "<< bintree.tree_maximum()<<" Min key is: "<<	bintree.tree_minimum()<<std::endl;
	
	MyIterator<treepair> inizio = bintree.begin();
        MyIterator<treepair> fine = bintree.end();
	int counter{0};	
	for(;inizio!=fine;++inizio){
		counter++;
		//std::cout<< bintree;
		//std::cout<<"contati "<<counter<<" nodi."<<std::endl;
		//std::cout<<(*inizio)<< " ";		
			
	}
	std::cout<<"contati "<<counter<<" nodi."<<std::endl;  
	
	//std::cout << bintree<<std::endl;

	bintree.find(34);
	bintree.find(2);
	bintree.find(7);
	bintree.find(5);
	std::cout<<"rimozione nodo 34"<<std::endl;
	bintree.erase(34);
	std::cout<<"finished erase"<<std::endl;

	//std::cout<<bintree<<std::endl;
	std::cout<<"rimozione nodo 1"<<std::endl;
	bintree.erase(1);
	std::cout<<"finished erase"<<std::endl;

	//std::cout<<bintree<<std::endl;

	std::cout<<"rimozione nodo 17"<<std::endl;
	bintree.erase(17);
	std::cout<<"finished erase"<<std::endl;

	
	bintree.tree_minimum();
	MyIterator<treepair> iniziale = bintree.begin();
	//std::cout<<bintree<<std::endl;

	
	std::cout<<"printed tree"<<std::endl;
	
	b_t_INT bintree_copy{};//made an empty tree
	
	bintree_copy = bintree;
	std::cout<<"copy made"<<std::endl;
	//std::cout<<bintree<<std::endl;
	//std::cout<<"BINTREE_COPY"<<bintree_copy<<std::endl;
	bintree_copy.erase(5);
	//std::cout<<"BINTREE_COPY_AFTER_ERASE"<<bintree_copy<<std::endl;
	//std::cout<<"TREE MINIMUM"<<std::endl;
	//bintree_copy.tree_minimum();	
	//std::cout<<"PRINT BINTREE_COPY"<<bintree_copy<<std::endl;

	
	
	//std::cout<<bintree<<std::endl;
	
	//std::cout<<bintree_copy<<std::endl;
	b_t_INT bintree_copy_by_constructor{bintree};//made an empty tree
	
	//std::cout<<bintree_copy_by_constructor<<std::endl;
	//b_t_INT bintree_move{std::move(bintree)};
	//std::cout<<bintree_move<<std::endl;
	/*	
	for (auto& x : bintree_copy_by_constructor)
		std::cout<<x<<" ";
	std::cout<<std::endl;
	*/

	bintree_copy_by_constructor.emplace(8,45);
	bintree_copy_by_constructor.erase(4);
	
	//std::cout<<bintree<<std::endl;	
	//std::cout<<bintree_copy_by_constructor<<std::endl;
	
	int i = 99;
	int j = 100;
 	std::cout<<"SEARCHING FOR KEY"<<bintree[i]<<std::endl;
	std::cout<<"SEARCHING FOR KEY"<<bintree[j]<<std::endl;
	std::cout<<"SEARCHING FOR KEY"<<bintree[100]<<std::endl;
	std::cout<<"SEARCHING FOR KEY"<<bintree[5]<<std::endl;
 	//TRIAL WITH CONST_ITERATOR
	
	const b_t_INT const_bintree = b_t_INT{bintree};
	//std::cout<<const_bintree<<std::endl;
	//const_bintree.emplace(3,3);
	//const_bintree.insert({5,5});
	const_bintree.find(100);
        //std::cout<<const_bintree<<std::endl;

	std::cout<<"###########################TEST ON BALANCE##########"<<std::endl;
	//std::cout<<bintree<<std::endl;
	bintree.balance();
	std::cout<<bintree<<std::endl;		
	std::cout<<"counted "<< bintree.size()<<" nodes "<<std::endl;	
	
	std::cout<<const_bintree<<std::endl;
	std::cout<<"counted "<< const_bintree.size()<<" nodes "<<std::endl;	
	//const_MyIterator<treepair> iterate = const_bintree[70]; //subscription doesn't work on constant bst-s	
	return 0;
}

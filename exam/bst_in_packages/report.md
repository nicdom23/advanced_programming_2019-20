#Advanced Programming project report

This code has been written with the intent of producing a working data structure for the purposes of the examination. 
The work proceeded by understanding and testing the various subcomponents of the data structure, such as the nodes and especially the iterators, that were fundamental for implementing most of the wanted public member functions.
Once the templated classes MyIterator and Node were ready and understood we implemented the class bst with a simpler template that only accepted the key type and the value type.
We implemented one by one the various public member functions that were requested and we added some accessory private member functions to achieve the wanted result. We used the < operator to compare the keys in the functions and we started by implementing only the regular iterator. We got the needed information on the binary search tree data structure from the book "Introduction to Algorithms" by Cormen,Leiserson,Rivest and Stein.
Once the member functions were implemented, tested and debugged we proceeded by making the data structure more complex:
-We added the third template type: the comparison operator. The member functions were corrected accordingly and were tested both with std::lesser and std::greater;
-We added the const_iterator and we tested it on a const binary search tree to see if all the functions that modified the tree gave a compiler error;
-We implemented the remaining member functions that operated with const_iterator;
-We splitted the code into different headers, one for each class. The classes are implemented in the headers .h and not in some proper files .cc because we want to avoid linker problems(the first ones we found were "undefined reference" errors for the constructor of the class Node whenever the class bst called it);
-At last we are testing the data structure to see if something unusual happens.We are noticing that iterators could be used to disrupt the binary-search-tree property and that end() produces a static iterator that could not be used to iterate the bst once the last element of the tree walk has changed. Probably this has to be reported as a behaviour to be avoided by the user. 
To try to avoid this misuse of the iterators we have imposed that the class treepair has a key of type 'const', and we also blocked the access to the Node constructor. Now we created the inner class iterator and const_iterator inside the bst class so that the user has now the proper iterators to use while programming.
What we notice now is the use of the public parameter last in the iterators. This leaves a statically defined iterator that could not be used to perform a walk on the tree since the last element of the walk could change over time.

We do not plan to write an all-performant code, but we are impressed by how far we got since the beginning of this project, and we hope that our hard-work is proven by what we made so far. 

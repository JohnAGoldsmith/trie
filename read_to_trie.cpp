
#include <string>
#include <iostream> 
#include "stringcollection.h"
#include "trie.h"
int   main()
{

    
  
	string dx1file = "../../data/english/dx1_files/english.dx1";
	stringcollection*   Words= new stringcollection();
	std::cout<<"Words' trie location " << Words->GetTrie()<<std::endl<<std::flush;;
	std::cout<<"Words' trie count" << Words->GetCount()<<std::endl<<std::flush;;
	std::cout<<"Words' trie location " << Words->GetTrie()<<std::endl<<std::flush;;
	string this_word = "hello";
	string that_word = "heaven";
	std::cout<<"Words' trie location " << Words->GetTrie()<<std::endl<<std::flush;;
	std::cout <<"A"<<std::endl<<std::flush;
	std::cout<<"Words' trie location " << Words->GetTrie()<<std::endl<<std::flush;;
	 *Words << this_word;
	std::cout <<"B"<<std::endl<<std::flush;
	 *Words << that_word;
	std::cout <<"C"<<std::endl<<std::flush;
};
 


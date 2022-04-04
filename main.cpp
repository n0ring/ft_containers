#include <map>
#include <unistd.h>
#include <sys/time.h>
#include <stack>
#include <vector>
#include <iomanip>
#include <iterator>
#include "Stack.hpp"
#include "Vector.hpp"
#include "pair.hpp"
#include "Binary_tree.hpp"
#include "Map.hpp"


// #include "iterators/Iterator.hpp"
// operator = in iterators

// stack or heap??

int main(void)
{
	// vector_test();
	// stack_test();
	// pair_test();
	map_test();
	// std::cout << static_cast<int>("fdsgsadf") << std::endl;

	// ft::Map<int, int> m;
	// for (int i = 1; i < 10; i++)
	// 	m[i] = i;
	// ft::Map<int, int>::iterator it = m.begin();
	// std::cout << it->first << std::endl;
	// it->first = 99;


	// node<int, int>  *end = m._tree.subtree_last(m._tree.root);
	// for (; tmp != end; tmp = m._tree.successor(tmp))
	// 	std::cout << tmp->pair.first << std::endl;
	// std::cout << tmp->pair.first << std::endl;
	
	
	// std::map<int, int> m;
	// m[1] = 1;
	// m[2] = 2;
	// m[3] = 3;
	// std::map<int, int>::iterator it = m.begin();
	// std::cout << it->first << std::endl;
	// it++;
	// std::cout << it->first << std::endl;





	// std::map<int, int> std_map;
	// std::map<int, int>::iterator it_s =  std_map.begin();
	// std::cout << it_s->second << std::endl;
	

	
	// Btree<int, int>	tree;

	// tree.insert_element(new ft::Pair<int, int>(10, 10));
	// tree.insert_element(new ft::Pair<int, int>(5, 5));
	// tree.insert_element(new ft::Pair<int, int>(4, 4));
	// tree.insert_element(new ft::Pair<int, int>(3, 3));
	// tree.insert_element(new ft::Pair<int, int>(7, 7));
	// tree.insert_element(new ft::Pair<int, int>(15, 15));
	// tree.insert_element(new ft::Pair<int, int>(13, 13));
	// tree.insert_element(new ft::Pair<int, int>(11, 11));
	// tree.insert_element(new ft::Pair<int, int>(14, 14));
	// tree.insert_element(new ft::Pair<int, int>(21, 21));
	
	// tree.delete_element(13);
	
	// tree.subtree_delete(tree.find(21));
	// tree.show_tree(tree.root);



	// tree.iterate();
	// tree.delete_element(5);

	// std::cout << (tree.precessor(n))->key << std::endl;
	// tree.show_tree(tree.get_root());

	// tree.subtree_delete(n);
	// std::cout << "-----" << std::endl;

	// tree.show_tree(tree.get_root());
	// std::cout << "-----" << std::endl;
	// tree.iterate();
	// std::cout << "-----" << std::endl;
	// tree.reverse_iterate();


	return (0);
}


// test adding in random order 
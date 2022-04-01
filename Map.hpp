#include <iostream>
#include "pair.hpp"
#include "utils.hpp"
#include "Binary_tree.hpp"


namespace ft
{
	

template < class Key,												// map::key_type
			class T,												// map::mapped_type
			class Compare = std::less<Key>,							// map::key_compare
			class Alloc = std::allocator<ft::Pair<const Key, T> >	// map::allocator_type
>
class Map
{

	public:
		typedef node<Key, T>					node;
		typedef typename node::key_type		key_type;
		typedef typename node::mapped_type	mapped_type;
		typedef typename node::node_type	node_type;
		typedef	Compare						key_compare;
		typedef Alloc						allocator_type;
		typedef size_t						size_type; // ?? 
		typedef ft::Pair<key_type, mapped_type> pair_type;	

	private:
		Btree<Key, T>	_tree;
		allocator_type	_alloc;
		size_type		_size;

	public:

		explicit Map (const key_compare& comp = key_compare(), // wtf is key_compare???
			const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0)
		{
			(void) comp;
		}

	size_type size(void) { return _size; }

	bool empty() const { return  (_size > 0 ) ? false : true; }

	mapped_type& operator[] (const key_type& k)
	{
		node *res = _tree.find(k);
		if (res == NULL)
		{
			_tree.root = new node(make_pair(k, mapped_type() )) ;
			return _tree.root->pair.second;
		}
		if (res->pair.first != k)
		{
			_size++;
			return (_tree.subtree_insert_after(res, new node(make_pair(k, mapped_type())) ) )->pair.second;
			//  return (_tree.insert_element()->pair.second;
		}
		return (res->pair.second);
	}

};


};
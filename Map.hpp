#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "pair.hpp"
#include "utils.hpp"
#include "Binary_tree.hpp"
#include "iterators/Iterator.hpp"

namespace ft
{

template<typename T>
class iterator_map
{
	// typedef typename T::first_type key_type;
	// typedef typename T::second_type v_type;

	private:
		T	*current;
		T	*tree_root;

		
	
	public:
		typedef T													iterator_type;
		typedef typename iterator_traits<T*>::iterator_category		iterator_category;
		typedef typename iterator_traits<T*>::value_type			value_type;
		typedef typename iterator_traits<T*>::difference_type		difference_type;
		typedef typename  iterator_type::reference_type 			reference;
		typedef typename  iterator_type::pointer					pointer;
		// typedef typename iterator_traits<T*>::reference				reference;
		// typedef typename iterator_traits<T*>::pointer				pointer;



		// default 
		iterator_map(void) : current(NULL), tree_root(NULL) {}
		iterator_map(T *current_pos, T *r) : current(current_pos), tree_root(r) {}
		//copy
		iterator_map(iterator_map<T> const &other) : current(other.current),
			tree_root(other.tree_root) {}
		// copy assignable
		iterator_map &operator=(iterator_map<T> const &other)
		{
			current = other.current;
			tree_root = other.tree_root;
			return (*this);
		}
		~iterator_map(void) {}

		// iterator_map(T *ptr) : current(ptr) {}
		
		// template <class Iter>
		// iterator_map (const iterator_map<Iter>& rev_it) : current(rev_it.current) { }

		iterator_type* base() const { return (current); }
		reference operator*() const {  return (current->pair); }

		iterator_map &operator++() { 
			current = current->successor();
			return *this;
		}

		iterator_map  operator++(int i) {
			(void) i;
			iterator_map tmp = *this;
			current = current->successor();
			return *this;
		}

		iterator_map &operator--() { 
			if (this->base()->isNil)
			{
				current = tree_root->subtree_last();
				return *this;
			}
			current = current->precessor();
			return *this;
		}

		iterator_map  operator--(int i) {
			(void) i;
			if (this->base()->isNil)
			{
				current = tree_root->subtree_last();
				return *this;
			}
			iterator_map tmp = *this;
			current = current->precessor();
			return *this;
		}
		pointer operator->() const { return &((operator*())) ; }
};


		template <class Iterator>
		  bool operator== (const iterator_map<Iterator>& lhs,
				const iterator_map<Iterator>& rhs) { return (lhs.base() == rhs.base()); }

		template <class Iterator>
		bool operator!= (const iterator_map<Iterator>& lhs,
				const iterator_map<Iterator>& rhs) { return !(lhs == rhs);}


template<typename T>
class reverse_iterator_map
{
	// typedef typename T::first_type key_type;
	// typedef typename T::second_type v_type;

	private:
		T	*current;
		T	*tree_root;

		
	
	public:
		typedef T													iterator_type;
		typedef typename iterator_traits<T*>::iterator_category		iterator_category;
		typedef typename iterator_traits<T*>::value_type			value_type;
		typedef typename iterator_traits<T*>::difference_type		difference_type;
		typedef typename  iterator_type::reference_type 			reference;
		typedef typename  iterator_type::pointer					pointer;
		// typedef typename iterator_traits<T*>::reference				reference;
		// typedef typename iterator_traits<T*>::pointer				pointer;



		// default 
		reverse_iterator_map(void) : current(NULL), tree_root(NULL) {}
		reverse_iterator_map(T *current_pos, T *r) : current(current_pos), tree_root(r) {}
		//copy
		reverse_iterator_map(reverse_iterator_map<T> const &other) : current(other.current),
			tree_root(other.tree_root) {}
		// copy assignable
		reverse_iterator_map &operator=(reverse_iterator_map<T> const &other)
		{
			current = other.current;
			tree_root = other.tree_root;
			return (*this);
		}
		~reverse_iterator_map(void) {}

		// iterator_map(T *ptr) : current(ptr) {}
		
		// template <class Iter>
		// reverse_iterator_map (const reverse_iterator_map<Iter>& rev_it) : current(rev_it.current),
		// 	tree_root(rev_it)	{}

		iterator_type* base() const { return (current); }
		reference operator*() const {  return (current->pair); }

		reverse_iterator_map &operator++() { 
			if (this->base()->isNil)
			{
				current = tree_root->subtree_last();
				return *this;
			}
			current = current->precessor();
			return *this;


		}

		reverse_iterator_map  operator++(int i) {
			(void) i;
			reverse_iterator_map tmp = *this;
			if (this->base()->isNil)
			{
				current = tree_root->subtree_last();
				return *this;
			}
			current = current->precessor();
			return *this;

		}

		reverse_iterator_map &operator--() { 
			current = current->successor();
			return *this;
		}

		reverse_iterator_map  operator--(int i) {
			(void) i;
			reverse_iterator_map tmp = *this;
			current = current->successor();
			return *this;
		}
		pointer operator->() const { return &((operator*())) ; }
};


		template <class Iterator>
		  bool operator== (const reverse_iterator_map<Iterator>& lhs,
				const reverse_iterator_map<Iterator>& rhs) { return (lhs.base() == rhs.base()); }

		template <class Iterator>
		bool operator!= (const reverse_iterator_map<Iterator>& lhs,
				const reverse_iterator_map<Iterator>& rhs) { return !(lhs == rhs);}



template < class Key,												// map::key_type
			class T,												// map::mapped_type
			class Compare = std::less<Key>,							// map::key_compare
			class Alloc = std::allocator<ft::Pair<const Key, T> >	// map::allocator_type
>
class Map
{

	public:
		typedef node<Key, T>									node;
		typedef typename node::key_type							key_type;
		typedef typename node::mapped_type						mapped_type;
		typedef typename node::node_type						node_type;
		typedef Alloc											allocator_type;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::size_type				size_type;
		typedef	Compare											key_compare;
		typedef ft::Pair<Key, mapped_type> 						value_type;
		typedef ft::iterator_map<node>							iterator;
		typedef ft::reverse_iterator_map<node>					reverse_iterator;
		typedef typename iterator::difference_type  			difference_type;
		// typedef Compare<Key>									Compare;

	public:
		Btree<Key, T>	_tree;
		allocator_type	_alloc;
		size_type		_size;

	public:

		explicit Map (const key_compare& comp = key_compare(), // wtf is key_compare???
			const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0)
		{
			(void) comp;
		}

		// template <class InputIterator>
		// Map(InputIterator first, InputIterator last,
		// 	const key_compare& comp = key_compare(),
		// 	const allocator_type& alloc = allocator_type()) : _alloc(alloc)
		// {
		// 	for (; first != last; first++)
		// 		Map::operator[first->key] = first->second;
		// }

		// map (const map& x);

		iterator begin() {return iterator (_tree.root->subtree_first(), _tree.root);}
		 reverse_iterator rbegin(){return reverse_iterator (_tree.root->subtree_last(), _tree.root);}
		iterator end() {return iterator(_tree.nil, _tree.root);}
		reverse_iterator rend() { return reverse_iterator(_tree.nil, _tree.root);}

		size_type size(void) { return _size; }
		bool empty() const { return  (_size > 0 ) ? false : true; }

		size_type max_size() const { return _alloc.max_size(); }

	mapped_type& operator[] (const key_type& k)
	{
		node *res = _tree.find(k);
		if (res == _tree.nil)
		{
			_size++;
			_tree.root = new node(make_pair(k, mapped_type() ), _tree.nil) ;
			return _tree.root->pair.second;
		}
		if (res->pair.first != k)
		{
			_size++;
			if (k < res->pair.first)
			{
				return (_tree.subtree_insert_before(res,
					new node(make_pair(k, mapped_type()), _tree.nil)))->pair.second;
			}
			else
			{
				return (_tree.subtree_insert_after(res,
					new node(make_pair(k, mapped_type()), _tree.nil)))->pair.second;
			}
		}
		return (res->pair.second);
	}

	Pair<iterator,bool> insert (const value_type& val)
	{
		node *new_node;
		node *res		= _tree.find(val.first);
		if (res == _tree.nil)
		{
			_size++;
			_tree.root = new node(val, _tree.nil);
			return make_pair(begin(), true);
		}
		if (res->pair.first == val.first)
			return (make_pair(iterator(res, _tree.root), false));
		else
		{
			_size++;
			new_node = new node(val, _tree.nil);
			if (val.first < res->pair.first)
				_tree.subtree_insert_before(res, new_node);
			else
				_tree.subtree_insert_after(res, new_node);
			return (make_pair(iterator(new_node, _tree.root), true ));
			
		}
		return make_pair(iterator(res, _tree.root), true);
	}

};


};

#endif // !MAP_HPP

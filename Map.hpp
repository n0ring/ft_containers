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
		typedef node<Key, T>										node;
		typedef typename node::key_type								key_type;
		typedef typename node::mapped_type							mapped_type;
		typedef typename node::node_type							node_type;
		typedef Alloc												allocator_type;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::size_type					size_type;
		typedef	Compare												key_compare;
		typedef ft::Pair<const Key, mapped_type> 							value_type;
		typedef ft::iterator_map<node>								iterator;
		typedef ft::reverse_iterator_map<node>						reverse_iterator;
		typedef typename iterator::difference_type  				difference_type;
		typedef iterator											const_iterator;
		typedef typename ft::reverse_iterator_map<const_iterator>	const_reverse_iterator;
		// typedef Compare<Key>									Compare;

	public:
		Btree<Key, T>	_tree;
		allocator_type	_alloc;
		size_type		_size;
		key_compare		_comp;

	public:

		explicit Map (const key_compare& comp = key_compare(), // wtf is key_compare???
			const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0), _comp(comp)
		{
		}

		template <class InputIterator>
		Map(InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0), _comp(comp)
		{
			for (; first != last; first++)
				this->insert(*first);
		}

		Map (Map<Key, T> & x) : _alloc(x._alloc), _size(0) // const? 
		{
			iterator first = x.begin();
			iterator last = x.end();
			for (; first != last; first++)
				this->insert(*first);
		}

		iterator begin() {return iterator (_tree.root->subtree_first(), _tree.root);}
		const_iterator begin() const {return iterator (_tree.root->subtree_first(), _tree.root);}
		iterator end() {return iterator(_tree.nil, _tree.root);}
		const_iterator end() const {return iterator(_tree.nil, _tree.root);}
		reverse_iterator rbegin(){return reverse_iterator (_tree.root->subtree_last(), _tree.root);}
		const_reverse_iterator rbegin() const {return reverse_iterator (_tree.root->subtree_last(), _tree.root);}
		reverse_iterator rend() { return reverse_iterator(_tree.nil, _tree.root);}
		const_reverse_iterator rend() const { return reverse_iterator(_tree.nil, _tree.root);}

		size_type size(void) { return _size; }
		bool empty() const { return  (_size > 0 ) ? false : true; }

		size_type max_size() const { return _alloc.max_size(); }

	mapped_type& operator[] (const key_type& k)
	{
		node *res = find(k).base();
		if (res == _tree.nil)
		{
			_size++;
			_tree.root = new node(make_pair(k, mapped_type() ), _tree.nil) ;
			return _tree.root->pair.second;
		}
		if (res->pair.first != k)
		{
			_size++;
			if (_comp(k, res->pair.first))
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
		node *res		= find(val.first).base();
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
			if (_comp(val.first, res->pair.first))
				_tree.subtree_insert_before(res, new_node);
			else
				_tree.subtree_insert_after(res, new_node);
			return (make_pair(iterator(new_node, _tree.root), true ));
			
		}
		return make_pair(iterator(res, _tree.root), true);
	}

	// iterator insert (iterator position, const value_type& val) {} ??? 

	template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
	{
		for (; first != last; first++)
			this->insert(*first);
	}

	void erase (iterator position)
	{
		if (position.base() == NULL)
			return ;
		_tree.subtree_delete(position.base());
		_size--;
	}

	size_type erase (const key_type& k)
	{
		node *to_del_element = find(k).base();
		if (to_del_element->pair.first != k)
			return 0;
		erase(iterator(to_del_element, _tree.root));
		return 1;
	}

	void erase (iterator first, iterator last)
	{
		iterator it = first;
		iterator it_next = ++first;
		while (it != last)
		{
			erase(it);
			it = it_next;
			it_next++;
		}
	}

	void show()
	{
		iterator it = begin();
		for (; it != end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
	}
	void clear()
	{
		_tree.delete_tree(_tree.root);
		_tree.root = _tree.nil;
		_size = 0;
	}

	void swap (Map& x)
	{
		std::swap(x._tree.root, this->_tree.root);
		std::swap(x._tree.nil, this->_tree.nil);
	}

	 iterator find(const key_type& k)
	 {
		node *tmp = _tree.root;
		node *tmp_p = _tree.nil;
		while (tmp != _tree.nil)
		{
			tmp_p = tmp;
			if (tmp->pair.first == k)
				return iterator(tmp, _tree.root);
			if (_comp(k, tmp->pair.first))
				tmp = tmp->left;
			else
				tmp = tmp->right;
		}
		return iterator(tmp_p, _tree.root);
	 }

	const_iterator find (const key_type& k) const
	 {
		node *tmp = _tree.root;
		node *tmp_p = _tree.nil;
		while (tmp != _tree.nil)
		{
			tmp_p = tmp;
			if (tmp->pair.first == k)
				return iterator(tmp, _tree.root);
			if (_comp(k, tmp->pair.first))
				tmp = tmp->left;
			else
				tmp = tmp->right;
		}
		return iterator(tmp_p, _tree.root);
	}

	size_type count (const key_type& k) const
	{
		iterator res = find(k);
		if (res.base()->isNil == false && res->first == k)
			return (1);
		else
			return (0);
	}
	
	key_compare key_comp() const { return _alloc; }

	iterator lower_bound (const key_type& k)
	{
		node *tmp = _tree.root;
		while (tmp->isNil == false)
		{
			if (_comp(tmp->pair.first, k))
				tmp = tmp->successor();
			else
				return iterator(tmp, _tree.root);
		}
		return (iterator(_tree.nil, _tree.root));
	}

	const_iterator lower_bound (const key_type& k) const
	{
		node *tmp = _tree.root;
		while (tmp->isNil == false)
		{
			if (_comp(tmp->pair.first, k))
				tmp = tmp->successor();
			else
				return iterator(tmp, _tree.root);
		}
		return (iterator(_tree.nil, _tree.root));
	}

	iterator upper_bound (const key_type& k)
	{
		node *tmp = _tree.root;
		while (tmp->isNil == false)
		{
			if (_comp(k, tmp->pair.first))
				return iterator(tmp, _tree.root);
			else
				tmp = tmp->successor();
		}
		return (iterator(_tree.nil, _tree.root));
	}

	const_iterator upper_bound (const key_type& k) const
	{
		node *tmp = _tree.root;
		while (tmp->isNil == false)
		{
			if (_comp(k, tmp->pair.first))
				return iterator(tmp, _tree.root);
			else
				tmp = tmp->successor();
		}
		return (iterator(_tree.nil, _tree.root));
	}

	Pair<iterator,iterator> equal_range (const key_type& k)
	{
		// node *tmp = _tree.root;
		// while (tmp->isNil == false)
		// {
		// 	if (k == tmp->pair.first)
		// 		return (make_pair(iterator(tmp, _tree.root), ++(iterator(tmpn _tree.root))))
		// 	if (_comp(k, tmp->pair.first))
		// 		tmp = tmp->successor();
		// 	else

		// }
		// return (iterator(_tree.nil, _tree.root));
	}

	allocator_type get_allocator() const { return _alloc; }

};


};

#endif // !MAP_HPP

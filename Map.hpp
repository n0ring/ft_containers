#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "pair.hpp"
#include "utils.hpp"
#include "Binary_tree.hpp"
#include "iterators/Iterator.hpp"

namespace ft
{

template < class Key,												// map::key_type
			class T,												// map::mapped_type
			class Compare = std::less<Key>,							// map::key_compare
			class Alloc = std::allocator< ft::Pair<const Key, T> >	// map::allocator_type
>
class Map
{
	public:	
		typedef node<ft::Pair<const Key, T> >						node;
		typedef Key													key_type;
		typedef T													mapped_type;
		typedef Alloc												allocator_type;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::size_type					size_type;
		typedef	Compare												key_compare;
		typedef ft::Pair<const Key, mapped_type> 					value_type;
		typedef ft::iterator_tree<node>								iterator;
		typedef ft::reverse_iterator_map<node>						reverse_iterator;
		typedef typename iterator::difference_type  				difference_type;
		typedef iterator											const_iterator;
		typedef typename ft::reverse_iterator_map<const_iterator>	const_reverse_iterator;
	class value_compare : public std::binary_function<value_type, value_type, bool>
	{
		public:
			Compare comp;

			value_compare(void) : comp(Compare()) {}
			value_compare (Compare c) : comp(c) {}
		
			bool operator() (const value_type& x, const value_type& y) const
  			{
				return comp(x.first, y.first);
			}
	};

	private:
		Tree<value_type, value_compare, allocator_type>	_tree;
		allocator_type			_alloc;
		key_compare				_comp;
		value_compare			_value_comp;

	public:

		explicit Map (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _tree(comp),
				_alloc(alloc), _comp(comp), _value_comp(comp)
		{
		}

		template <class InputIterator>
		Map(InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _tree(comp), _alloc(alloc),
				 _comp(comp), _value_comp(comp)
		{
			this->insert(first, last);
		}

		Map (Map<Key, T> const &x) : _tree(x._comp, x._tree._size), _alloc(x._alloc),
			_comp(x._comp), _value_comp(x._value_comp) // const? 
		{
			_tree = x._tree;
		}

		Map &operator=(Map<Key, T> const &x)
		{
			_comp = x._comp;
			_alloc = x._alloc;

			_tree = x._tree;
			return *this;
		}

		iterator				begin() {return iterator (_tree.root->subtree_first(), _tree.root);}
		const_iterator			begin() const {return iterator (_tree.root->subtree_first(), _tree.root);}
		iterator				end() {return iterator(_tree.nil, _tree.root);}
		const_iterator			end() const {return iterator(_tree.nil, _tree.root);}
		reverse_iterator		rbegin(){return reverse_iterator (_tree.root->subtree_last(), _tree.root);}
		const_reverse_iterator	rbegin() const {return reverse_iterator (_tree.root->subtree_last(), _tree.root);}
		reverse_iterator		rend() { return reverse_iterator(_tree.nil, _tree.root);}
		const_reverse_iterator	rend() const { return reverse_iterator(_tree.nil, _tree.root);}
		size_type				size(void) const { return _tree._size; }
		bool					empty() const { return  (size() > 0 ) ? false : true; }
		size_type				max_size() const { return _alloc.max_size(); }

		
		mapped_type& operator[] (const key_type& k)
		{
			iterator res = find(k);

			if (res.base()->isNil == false && res->first == k)
				return res->second;
			else
				return ( _tree.insert_element(ft::make_pair(k, mapped_type()), res.base() ) )->value.second;
		}

		Pair<iterator,bool> insert(const value_type& val) // value
		{
			iterator res = find(val.first);
			node		*res_of_insert;
			if (res.base()->isNil == false && res->first == val.first)
				return ft::make_pair(res, false);
			else
				res_of_insert	= _tree.insert_element(val);

			return (ft::make_pair(iterator(res_of_insert, _tree.root), true));
		}

		iterator insert (iterator position, const value_type& val)
		{
			node		*successor = position.base()->successor();

			if (_comp(val.first, successor->value.first) && _comp(position->first, val.first))
				return iterator(_tree.subtree_insert_after(position.base(), new node(val, _tree.nil)), _tree.root);
			else
				return insert(val).first;
		}

		template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
		{
			for (; first != last; first++)
				this->insert(*first);
		}

		void erase (iterator position)
		{
			if (position.base() == NULL || position.base() == _tree.nil)
				return ;
			_tree.subtree_delete(position.base());
			_tree._size--;
		}

		size_type erase (const key_type& k)
		{
			node *to_del_element = find(k).base();
			if (to_del_element->value.first != k)
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
			_tree._size = 0;
		}

		iterator find(const key_type& k) // change this! 
		{
			node *tmp = _tree.root;
			node *tmp_p = _tree.nil;

			while (tmp != _tree.nil)
			{
				if (tmp->value.first == k)
					return iterator(tmp, _tree.root);
				tmp_p = tmp;
				if (_comp(k, tmp->value.first))
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
				if (tmp->value.first == k)
					return iterator(tmp, _tree.root);
				tmp_p = tmp;
				if (_comp(k, tmp->value.first))
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

		key_compare key_comp() const { return _comp; }

		iterator lower_bound (const key_type& k)
		{
			node	*tmp	= _tree.root;
			node	*tmp_p	= _tree.nil;
			
			while (tmp->isNil == false)
			{
				tmp_p = tmp;
				if (tmp->value.first == k)
					return iterator(tmp, _tree.root);
				if (_comp(k, tmp->value.first))
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			if (_comp(tmp_p->value.first, k))
				return iterator(tmp_p->successor(), _tree.root);
			return iterator(tmp_p, _tree.root);
		}

		const_iterator lower_bound (const key_type& k) const
		{
			return lower_bound(k);
		}

		iterator upper_bound (const key_type& k)
		{
			node	*tmp	= _tree.root;
			node	*tmp_p	= _tree.nil;
			
			while (tmp->isNil == false)
			{
				tmp_p = tmp;
				if (tmp->value.first == k)
					return iterator(tmp->successor(), _tree.root);
				if (_comp(k, tmp->value.first))
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			if (_comp(tmp_p->value.first, k))
				return iterator(tmp_p->successor(), _tree.root);
			return iterator(tmp_p, _tree.root);
		}

		const_iterator upper_bound (const key_type& k) const
		{
			return upper_bound(k);
		}

		Pair<iterator,iterator> equal_range (const key_type& k)
		{
			return ft::make_pair( lower_bound(k), upper_bound(k));
		}

		Pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{
			return ft::make_pair( lower_bound(k), upper_bound(k));
		}


		allocator_type get_allocator() const { return _alloc; }

		void swap (Map& x)
		{
			(void) x;
			// std::swap(x._tree, this->_tree);
			std::swap(x._tree.root, this->_tree.root);
			std::swap(x._tree.nil, this->_tree.nil);
			std::swap(x._tree._size, this->_tree._size);

			std::swap(x._alloc, this->_alloc);
			// std::swap(x._size, this->_size);
			std::swap(x._comp, this->_comp);
			std::swap(x._value_comp, this->_value_comp);
		}

};

	template <class Key, class T, class Compare, class Alloc>
	bool operator== ( const Map<Key,T,Compare,Alloc>& lhs,
					const Map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!= ( const Map<Key,T,Compare,Alloc>& lhs,
					const Map<Key,T,Compare,Alloc>& rhs )
	{
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator< ( const Map<Key,T,Compare,Alloc>& lhs,
					const Map<Key,T,Compare,Alloc>& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= ( const Map<Key,T,Compare,Alloc>& lhs,
					const Map<Key,T,Compare,Alloc>& rhs )
	{
		return (lhs < rhs || lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator> ( const Map<Key,T,Compare,Alloc>& lhs,
					const Map<Key,T,Compare,Alloc>& rhs )
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>= ( const Map<Key,T,Compare,Alloc>& lhs,
					const Map<Key,T,Compare,Alloc>& rhs )
	{
		return (rhs < lhs || lhs == rhs);
	}	

};

namespace std
{
	template <class Key, class T, class Compare, class Alloc>
	void swap (ft::Map<Key,T,Compare,Alloc>& x, ft::Map<Key,T,Compare,Alloc>& y)
	{
		std::swap(x._tree.root, y._tree.root);
		std::swap(x._tree._size, y._tree._size);
		std::swap(x._tree.nil, y._tree.nil);
		std::swap(x._alloc, y._alloc);
		std::swap(x._comp, y._comp);
		std::swap(x._value_comp, y._value_comp);
	}
}
#endif // !MAP_HPP

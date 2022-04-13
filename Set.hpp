#ifndef SET_HPP
#define SET_HPP

#include <iostream>
#include "pair.hpp"
#include "utils.hpp"
#include "Binary_tree.hpp"
#include "iterators/Iterator.hpp"

namespace ft
{

template < class T,                        // set::key_type/value_type
           class Compare = std::less<T>,        // set::key_compare/value_compare
           class Alloc = std::allocator<T>      // set::allocator_type
           >
class Set
{
	public:	
		typedef node<const T>										node;
		typedef T													key_type;
		// typedef T												mapped_type;
		typedef Alloc												allocator_type;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::size_type					size_type;
		typedef	Compare												key_compare;
		typedef const T 											value_type;
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
				return comp(x, y);
			}
	};

	public:
		Tree<value_type, value_compare, allocator_type>	_tree;
		allocator_type			_alloc;
		key_compare				_comp;
		value_compare			_value_comp;

	public:

		explicit Set (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _tree(comp),
				_alloc(alloc), _comp(comp), _value_comp(comp)
		{
		}

		template <class InputIterator>
		Set(InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _tree(comp), _alloc(alloc),
				 _comp(comp), _value_comp(comp)
		{
			this->insert(first, last);
		}

		Set (Set<value_type> const &x) : _tree(x._comp, x._tree._size), _alloc(x._alloc),
			_comp(x._comp), _value_comp(x._value_comp) 
		{
			_tree = x._tree;
		}

		Set &operator=(Set<value_type> const &x)
		{
			_comp = x._comp;
			_alloc = x._alloc;

			_tree = x._tree;
			return *this;
		}

		iterator				begin() {return iterator(_tree.root->subtree_first(), _tree.root);}
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

		Pair<iterator,bool> insert(const value_type& val)
		{
			size_type	size_before		= _tree._size;
			node		*res_of_insert	= _tree.insert_element(val);
			bool		insert_status 	= _tree._size != size_before ? true : false;

			return (ft::make_pair(iterator(res_of_insert, _tree.root), insert_status));
		}


		iterator insert (iterator position, const value_type& val)
		{
			node		*successor = position.base()->successor();

			if (_comp(val, successor->value) && _comp(*position, val))
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

		size_type erase (const value_type& k)
		{
			node *to_del_element = find(k).base();
			if (to_del_element->isNil || to_del_element->value != k)
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


		void clear()
		{
			_tree.delete_tree(_tree.root);
			_tree.root = _tree.nil;
			_tree._size = 0;
		}

		iterator find(const key_type& k)
		{
			node *tmp = _tree.root;

			while (tmp != _tree.nil)
			{
				if (tmp->value == k)
					return iterator(tmp, _tree.root);
				if (_comp(k, tmp->value))
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			return iterator(tmp, _tree.root);
		}

		const_iterator find (const key_type& k) const
		{
			node *tmp = _tree.root;

			while (tmp != _tree.nil)
			{
				if (tmp->value == k)
					return iterator(tmp, _tree.root);
				if (_comp(k, tmp->value))
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			return iterator(tmp, _tree.root);
		}

		size_type count (const key_type& k) const
		{
			iterator res = find(k);
			if (res.base()->isNil == false && *res == k)
				return (1);
			else
				return (0);
		}

		key_compare key_comp() const { return _comp; }
		value_compare value_comp() const { return _value_comp; }
		iterator lower_bound (const key_type& k)
		{
			node	*tmp	= _tree.root;
			node	*tmp_p	= _tree.nil;
			
			while (tmp->isNil == false)
			{
				tmp_p = tmp;
				if (tmp->value == k)
					return iterator(tmp, _tree.root);
				if (_comp(k, tmp->value))
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			if (_comp(tmp_p->value, k))
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
				if (tmp->value == k)
					return iterator(tmp->successor(), _tree.root);
				if (_comp(k, tmp->value))
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			if (_comp(tmp_p->value, k))
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

		void swap (Set& x)
		{
			(void) x;
			std::swap(x._tree.root, this->_tree.root);
			std::swap(x._tree.nil, this->_tree.nil);
			std::swap(x._tree._size, this->_tree._size);

			std::swap(x._alloc, this->_alloc);
			std::swap(x._comp, this->_comp);
			std::swap(x._value_comp, this->_value_comp);
		}

};

	template <class T, class Compare, class Alloc>
	bool operator== ( const Set<T,Compare,Alloc>& lhs,
					const Set<T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class T, class Compare, class Alloc>
	bool operator!= ( const Set<T,Compare,Alloc>& lhs,
					const Set<T,Compare,Alloc>& rhs )
	{
		return !(lhs == rhs);
	}

	template <class T, class Compare, class Alloc>
	bool operator< (const Set<T,Compare,Alloc>& lhs,
					const Set<T,Compare,Alloc>& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Compare, class Alloc>
	bool operator<= (const Set<T,Compare,Alloc>& lhs,
					const Set<T,Compare,Alloc>& rhs  )
	{
		return (lhs < rhs || lhs == rhs);
	}

	template <class T, class Compare, class Alloc>
	bool operator> ( const Set<T,Compare,Alloc>& lhs,
					const Set<T,Compare,Alloc>& rhs )
	{
		return (rhs < lhs);
	}

	template <class T, class Compare, class Alloc>
	bool operator>= (const Set<T,Compare,Alloc>& lhs,
					const Set<T,Compare,Alloc>& rhs )
	{
		return (rhs < lhs || lhs == rhs);
	}	

};

namespace std
{
	template <class Key, class T, class Compare, class Alloc>
	void swap (ft::Set<T,Compare,Alloc>& x, ft::Set<T,Compare,Alloc>& y)
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

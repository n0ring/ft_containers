#ifndef VECTOR_HPP
#define VECTOR_HPP

// Only if T is guaranteed to not throw while moving, implementations can optimize to move elements instead of copying them during reallocations.
#include <exception>
#include <type_traits>
#include <memory>
#include <iostream>
#include "iterators/Iterator.hpp"
#include "utils.hpp"



namespace ft
{

template < typename T, typename Alloc = std::allocator<T> > 
class Vector
{
	public:
		typedef	T												value_type;
		typedef	Alloc											allocator_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef typename allocator_type::size_type				size_type;
		typedef ft::iterator_vector<T>							iterator;
		typedef typename iterator::difference_type  			difference_type;
		typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
		typedef const_pointer									const_iterator;
		typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef	typename ft::iterator_vector<T>::iterator_category	iterator_category;

	private: 
		T					*_array;
		size_type			_size;
		size_type			_capacity;
		allocator_type		_alloc;

		void _clear_array()
		{
			_removeElements(this->begin(), this->end());
			if (_array)
			{
				_alloc.deallocate(_array, _capacity);
				_array = nullptr;
			}
		}
		
		void _realloc(size_type new_cap)
		{
			value_type *new_arr = _alloc.allocate(new_cap);
			if (_size > 0)
				std::uninitialized_copy(this->begin(), this->end(), new_arr);
			_clear_array();
			_array = new_arr;
			_capacity = new_cap;
		}

		template<typename Iter>
		void _removeElements(Iter first, Iter last)
		{
			value_type *tmp = first.base();
			value_type *end = last.base();

			for ( ; tmp != end; tmp++)
				_alloc.destroy(tmp);
		}

	public:
		
		Vector( void ) {
			_size = 0;
			_capacity = 0;
			_array = _alloc.allocate(_capacity);
		};

		explicit Vector(size_type n, const value_type& val = value_type()) {
			size_type i;
			_size = n;
			_capacity = n;
			_array = _alloc.allocate(_capacity);
			for (i = 0; i < n; i++)
				_alloc.construct(_array + i, val);
		}
		
		template <typename InputIterator>
		Vector (InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type(), 
			typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator >::type* = 0) : _alloc(alloc)
		{
			_size = std::distance(first, last);
			if (_size <= 0)
				throw std::range_error("Range error");
			_capacity = _size;
			_array = _alloc.allocate(_capacity);
			std::uninitialized_copy(first, last, _array);;
		}
			
		Vector(const Vector& x) {
			size_type i;
			_capacity = x.capacity();
			_size = x.size();
			_array = _alloc.allocate(_capacity);
			for (i = 0; i < x.size(); i++)
				_alloc.construct(_array + i, x[i]);
		}

		Vector &operator=(const Vector &rhs)
		{
			size_type i;
			if (this != &rhs)
			{
				this->~Vector();
				_capacity = rhs.capacity();
				_size = rhs.size();
				_array = _alloc.allocate(_capacity);
				for (i = 0; i < rhs.size(); i++)
					_alloc.construct(_array + i, rhs[i]);
			}
			return (*this);
		}

		~Vector( void ) {
			_clear_array();
			_size = 0;
			_capacity = 0;
		};

		void reserve (size_type n) {
			if (n <= _capacity)
				return ;
			_realloc(n);
		}

		void	resize(size_type n, value_type val = value_type() )
		{
			if (n == _size)
				return ;
			if (n > _capacity)
			{
				if (_capacity == 0)
					_realloc(n);
				else
					_realloc(_capacity * 2);
			}
			if (n < _size)
				_removeElements(this->begin() + n, this->end());
			else
				std::uninitialized_fill(_array + _size, _array + n, val);
			_size = n;
		}

		size_type	capacity( void ) const { return (_capacity); }
		size_type	size( void ) const { return (_size); }
		size_type	max_size() const { return _alloc.max_size(); }
		bool		empty() const { return (_size ? false : true); }



		// Element access:
		const_reference	operator[](size_type const &i) const { return (_array[i]); }
		reference		operator[](size_type const &i) { return (_array[i]); }

		reference		at(size_type n) {
			if (n >= _size)
				throw std::out_of_range("vector");
			return (_array[n]);
		}
		const_reference	at (size_type n) const {
			if (n >= _size)
				throw std::out_of_range("vector");
			return (_array[n]);
		}
		reference		front() { return *(this->begin()); }
		const_reference	front() const { return *(this->begin()); }
		reference		back() { return *( this->end() - 1); }
		const_reference	back() const { return *(this->end() - 1); }

		// Modifiers:
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last,
			typename ft::enable_if< !ft::is_integral< InputIterator >::value, InputIterator >::type* = 0)
		{
			size_type		dist		= std::distance(first, last);

			if (dist < _capacity)
			{
				_removeElements(this->begin(), this->end());
				std::uninitialized_copy(first, last, _array);
				_size = dist;
			}
			else
			{
				value_type *new_arr = _alloc.allocate(dist);
				_clear_array();
				std::uninitialized_copy(first, last, new_arr);
				_array = new_arr;
				_capacity =_size = dist;
			}
		}

		void assign(size_type n, const value_type& val)
		{
			if (n < _capacity)
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_array + i);
				std::uninitialized_fill_n(_array, n, val);
				_size = n;
			}
			else
			{
				value_type *new_arr = _alloc.allocate(n);
				_clear_array();
				std::uninitialized_fill_n(new_arr, n, val);
				_array = new_arr;
				_capacity = _size = n;
			}
		}
		

		void	push_back (const value_type& val)
		{
			size_type new_cap;

			if (_size == _capacity)
			{
				new_cap = _size ? _size * 2 : 2;
				_realloc(new_cap);
			}
			_alloc.construct(_array + _size, val);
			_size++;
		}

		void	pop_back( void ) {
			_size--;
			_alloc.destroy(_array + _size);	
		}
		void	clear( void ) {
			_removeElements(this->begin(), this->end());
			_size = 0;
		}

		iterator insert(iterator position, const value_type& val)
		{
			value_type	*new_arr;
			size_type	new_cap;
			size_type	insertIndex	= std::distance(this->begin(), position);
			iterator	tmp = position;

			if (_size < insertIndex)
				return (position);
			if (_size == _capacity) // new _array
			{
				new_cap = _size ? _size * 2 : 2;
				new_arr = _alloc.allocate(new_cap);
				std::uninitialized_copy(this->begin(), position, new_arr);
				_alloc.construct(new_arr + insertIndex, val);
				std::uninitialized_copy(position, this->end(), new_arr + insertIndex + 1);
				_clear_array();
				_capacity = new_cap;
				_size++;
				_array = new_arr;
				return (static_cast<iterator>(new_arr + insertIndex));
			}
			else
			{
				new_arr = _alloc.allocate(std::distance(position, this->end()));
				std::uninitialized_copy(position, this->end(), new_arr);
				
				_removeElements(tmp, this->end());
				_alloc.construct(position.base(), val);			/* insert new element */
				std::uninitialized_copy(new_arr, new_arr + _size - insertIndex, position + 1);
				for (size_type i = 0; i < _size - insertIndex; i++) 	/* clean new_arr */
					_alloc.destroy(new_arr + i);
				_alloc.deallocate(new_arr, _size - insertIndex);
				_size++;
				return (static_cast<iterator>(_array + insertIndex));
			}
		}

		void insert (iterator position, size_type n, const value_type& val) {
			value_type	*new_arr;
			size_type	insertIndex = std::distance(this->begin(), position);

			if (_size < insertIndex)
				return ;
			if (_size + n > _capacity)
			{
				new_arr = _alloc.allocate(_size + n);
				std::uninitialized_copy(this->begin(), position, new_arr);
				std::uninitialized_fill_n(new_arr + insertIndex, n, val);
				std::uninitialized_copy(position, this->end(), new_arr + insertIndex + n);
				_clear_array();
				_array = new_arr;
				_capacity = _size + n;
				_size = _size + n;
			}
			else
			{
				new_arr = _alloc.allocate(_size - insertIndex);
				std::uninitialized_copy(position, this->end(), new_arr);
				_removeElements(position, this->end());
				std::uninitialized_fill_n(position, n, val);
				std::uninitialized_copy(new_arr, new_arr + _size - insertIndex, position + n);
				for (size_type i = 0; i < _size - insertIndex; i++) 						/* clean new_arr */
					_alloc.destroy(new_arr + i);
				_alloc.deallocate(new_arr, _size - insertIndex);
				_size += n;
			}
		}

		template<class InputIt>
		bool validate_iterator_values(InputIt first, InputIt last, size_t range) {
			pointer reserved_buffer;
			reserved_buffer = _alloc.allocate(range);
			bool result = true;
			size_t i = 0;

			for (;first != last; ++first, ++i) {
				try { reserved_buffer[i] = *first; }
				catch (...) { result = false; break; }
			}
			_alloc.deallocate(reserved_buffer, range);
			return result;
	}


		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
		{
			size_type		new_size				= _size + std::distance(first, last);
			size_type		insertIndex			= std::distance(this->begin(), position);
			value_type		*new_arr;
			size_type		i = 0;
			iterator		last_element_pos;

		if (!validate_iterator_values(first, last, std::distance(first, last)))
			throw std::exception();

			if (_size < insertIndex)
				return ;
			if (new_size > _capacity)
			{	
				size_type new_cap = _size * 2 > new_size ? _size * 2 : new_size;
				new_arr = _alloc.allocate(new_cap);
				last_element_pos = std::uninitialized_copy(this->begin(), position, new_arr);
				last_element_pos = std::uninitialized_copy(first, last, last_element_pos);
				std::uninitialized_copy(position, this->end(), last_element_pos);
				_clear_array();
				_array = new_arr;
				_capacity = new_cap;
				_size = new_size;
			}
			else
			{
				new_arr = _alloc.allocate(_size - insertIndex);
				std::uninitialized_copy(position, this->end(), new_arr);
				_removeElements(position, this->end());
				last_element_pos = std::uninitialized_copy(first, last, position);
				std::uninitialized_copy(new_arr, new_arr + _size - insertIndex, last_element_pos);
				for (i = 0; i <= _size - insertIndex; i++)
					_alloc.destroy(new_arr + i);
				_alloc.deallocate(new_arr, _size - insertIndex);
				_size += std::distance(first, last);
			}
		}

		iterator erase (iterator position)
		{
			size_type index = position - this->begin();
			_alloc.destroy(position.base());
			for (size_type i = index; i < _size; i++)
				_array[i] = _array[i + 1];
			_size--;
			return (position);
		}

		iterator erase (iterator first, iterator last)
		{
			iterator	tmp = first;
			T			*new_arr;
			iterator	last_new_el;

			if (last == this->end())
			{
				while (tmp != last)
				{
					_alloc.destroy(tmp.base());
					tmp++;
				}
				_size = std::distance(this->begin(), first);
				return this->end();
			}
			else
			{
				new_arr = _alloc.allocate(_capacity);
				last_new_el = std::uninitialized_copy(this->begin(), first, new_arr);
				iterator returnValue = last_new_el;
				last_new_el = std::uninitialized_copy(last, this->end(), last_new_el);
				_clear_array();
				_size -= std::distance(first, last);
				_array = new_arr;
				return (returnValue); // last + 1
			}
		}


		void swap (Vector& x)
		{
			value_type		*tmp_arr = x._array;
			size_type 		tmp_size = x._size;
			size_type		tmp_cap = x._capacity;
			allocator_type	tmp_alloc = x._alloc;

			x._array = _array;
			x._size = _size;
			x._capacity = _capacity;
			x._alloc = _alloc;
			
			_array = tmp_arr;
			_size = tmp_size;
			_capacity = tmp_cap;
			_alloc = tmp_alloc;
			// std::swap(_array, x._array);
			// std::swap(_alloc, x._alloc);
			// std::swap(_capacity, x._capacity);
			// std::swap(_size, x._size);
			
		}

		// iterators funcs
		reverse_iterator		rbegin() { return static_cast<reverse_iterator>(_array + _size); }
		const_reverse_iterator	rbegin() const { return _array + _size; }

		reverse_iterator		rend() { return static_cast<reverse_iterator>(_array); }
		const_reverse_iterator	rend() const { return (_array); }

		iterator				begin() {return (static_cast<iterator>(_array)); }
		const_iterator			begin() const {return static_cast<const_iterator>(_array); }
		
		iterator				end() { return (static_cast<iterator>(_array + _size)); }
		const_iterator			end() const { return static_cast<const_iterator>(_array + _size); }

		allocator_type get_allocator() const { return (_alloc); }
};

		template <class T, class Alloc>
		void swap (Vector<T,Alloc>& x, Vector<T,Alloc>& y)
		{
			x.swap(y);
		}

		template <typename T, typename Allocator>
		bool operator==(const Vector<T,Allocator>& lhs, const Vector<T,Allocator>& rhs) {
			if (lhs.size() != rhs.size())
				return (false);
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}

		template <typename T, typename Allocator>
		bool operator!= (const Vector<T,Allocator>& lhs, const Vector<T,Allocator>& rhs) {
			return !(rhs == lhs);
		}


	template <typename T, typename Allocator>
		bool operator<(const Vector<T,Allocator>& lhs, const Vector<T,Allocator>& rhs) {
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

	template <typename T, typename Allocator>
		bool operator<=(const Vector<T,Allocator>& lhs, const Vector<T,Allocator>& rhs) {
			return (lhs < rhs || lhs == rhs);
		}

	template <typename T, typename Allocator>
		bool operator>(const Vector<T,Allocator>& lhs, const Vector<T,Allocator>& rhs) {
			return (rhs < lhs);
		}

	template <typename T, typename Allocator>
		bool operator>=(const Vector<T,Allocator>& lhs, const Vector<T,Allocator>& rhs) {
			return (rhs < lhs || rhs == lhs);
		}

}
#endif // !VECTOR


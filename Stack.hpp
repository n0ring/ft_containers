#ifndef STACK_HPP
#define STACK_HPP

#include "Vector.hpp"
#include <iostream>

namespace ft
{

template < typename T, typename Container = ft::Vector<T> >
class Stack
{
	protected:
		Container	c;

	public:
		typedef Container								container_type;
		typedef typename container_type::value_type		value_type;
		typedef typename container_type::size_type		size_type;

		Stack( void ) { };
		~Stack( void ) { };

		Stack( const Stack &src ) { *this = src; }

		Stack &operator=(const Stack<T, Container> &rhs)
		{
			if (this != &rhs)
				this->c = rhs.c;
			return (*this);
		}

		explicit Stack(const container_type& cont ) : c(cont) { }

		bool				empty( void ) const { return (this->c.empty()); }
		size_type			size( void ) const { return (this->c.size()); }
		const value_type	&top( void ) const { return (this->c.back()); }
		value_type			&top( void ) { return (this->c.back()); }
		void				push (const value_type& val) { this->c.push_back( val ); }
		void				pop( void ) { this->c.pop_back(); }

		template <typename U, class Allocator>
  		friend bool operator==(const Stack<U,Allocator>& lhs, const Stack<U,Allocator>& rhs) {
			return (lhs.c == rhs.c);
		}
		template <typename U, class Allocator>
		friend bool operator!= (const Stack<U,Allocator>& lhs, const Stack<U,Allocator>& rhs) {
			return (lhs.c != rhs.c);
		}
		template <typename U, class Allocator>
		friend bool operator<(const Stack<U,Allocator>& lhs, const Stack<U,Allocator>& rhs) {
			return (lhs.c < rhs.c);
		}
		template <typename U, class Allocator>
		friend bool operator<= (const Stack<U,Allocator>& lhs, const Stack<U,Allocator>& rhs){
			return (lhs.c <= rhs.c);
		}
		template <typename U, class Allocator>
		friend bool operator>  (const Stack<U,Allocator>& lhs, const Stack<U,Allocator>& rhs){
			return (lhs.c > rhs.c);
		}
		template <typename U, class Allocator>
		friend bool operator>=(const Stack<U,Allocator>& lhs, const Stack<U,Allocator>& rhs){
			return (lhs.c >= rhs.c);
		}
};

}

#endif
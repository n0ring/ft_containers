#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>




namespace ft
{

template<typename Iterator>
class iterator_traits
{
	public:
	    typedef typename Iterator::difference_type		difference_type;
    	typedef typename Iterator::value_type			value_type;
    	typedef typename Iterator::pointer				pointer;
    	typedef typename Iterator::reference			reference;
    	typedef typename Iterator::iterator_category	iterator_category;
};

template<typename T>
class iterator_traits<T*>
{
	public:
    	typedef T								value_type;
    	typedef T*								pointer;
    	typedef T&								reference;
    	typedef ptrdiff_t						difference_type;
    	typedef std::random_access_iterator_tag	iterator_category;
};



template<typename T>
class iterator_vector
{
	private:
		T *current;
	
	public:
		typedef T														iterator_type;
		typedef typename ft::iterator_traits<T*>::iterator_category		iterator_category;
		typedef typename ft::iterator_traits<T*>::value_type			value_type;
		typedef typename ft::iterator_traits<T*>::difference_type		difference_type;
		typedef typename ft::iterator_traits<T*>::reference				reference;
		typedef typename ft::iterator_traits<T*>::pointer				pointer;


		iterator_vector(void) : current() {}
		iterator_vector(T *ptr) : current(ptr) {}
		explicit iterator_vector (iterator_type it) : current(it) {}
		
		template <class Iter>
		iterator_vector (const iterator_vector<Iter>& rev_it) : current(rev_it.base()) { }
		
		~iterator_vector(void)
		{
		}

		pointer base() const { return (current); }
		reference operator*() const {  return *current; }
		iterator_vector operator+ (difference_type n) const
		{ return static_cast<iterator_vector>(current + n); }
		iterator_vector& operator++() { ++current; return *this; }
		iterator_vector  operator++(int i) {
			(void) i;
			iterator_vector tmp = *this;
			++current;
			return tmp;
		}
		iterator_vector& operator+= (difference_type n) { current += n; return *this; }

		iterator_vector operator- (difference_type n) const
		{ return static_cast<iterator_vector>(current - n); }
		
		
		iterator_vector& operator--() { --current; return *this; }
		
		iterator_vector  operator--(int i) {
			(void) i;
			iterator_vector tmp = *this;
			--current;
			return tmp;
		}


		iterator_vector& operator-= (difference_type n) { current -= n; return *this; }
		pointer operator->() const { return &(operator*()); }
		reference operator[](difference_type n) const { return *(*this + n); }

};
		template <class Iterator>
  		bool operator== (const iterator_vector<Iterator>& lhs,
				const iterator_vector<Iterator>& rhs) { return (lhs.base() == rhs.base()); }

		template <class Iterator>
		bool operator!= (const iterator_vector<Iterator>& lhs,
				const iterator_vector<Iterator>& rhs) { return !(lhs == rhs);}


		template <class Iterator>
		bool operator<(const iterator_vector<Iterator>& lhs,
				const iterator_vector<Iterator>& rhs) { return (lhs.base() < rhs.base()); }

		template <class Iterator>
  		bool operator<= (const iterator_vector<Iterator>& lhs,
			   const iterator_vector<Iterator>& rhs) { return (lhs.base() <= rhs.base());}
	
		template <class Iterator>
		bool operator>  (const iterator_vector<Iterator>& lhs,
			   const iterator_vector<Iterator>& rhs) { return (lhs.base() > rhs.base()); }

		template <class Iterator>
		bool operator>= (const iterator_vector<Iterator>& lhs,
				const iterator_vector<Iterator>& rhs) { return (lhs.base() >= rhs.base());}

		template <class Iterator>
		iterator_vector<Iterator> operator+ (
            typename iterator_vector<Iterator>::difference_type n,
            const iterator_vector<Iterator>& rev_it)
		{ return static_cast<iterator_vector<Iterator> >(rev_it.base() + n); }

		template <class Iterator>
			typename iterator_vector<Iterator>::difference_type operator-(
			const iterator_vector<Iterator>& lhs,
			const iterator_vector<Iterator>& rhs){
				return (static_cast<typename iterator_vector<Iterator>::difference_type>(lhs.base() - rhs.base()));
}

template<typename Iterator>
class reverse_iterator
{
	protected:
		Iterator current;
	private:
	public:
		typedef Iterator													iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::difference_type	difference_type;
		typedef typename iterator_traits<Iterator>::reference			reference;
		typedef typename iterator_traits<Iterator>::pointer			pointer;


		reverse_iterator(void) : current() {}
		explicit reverse_iterator (iterator_type it) : current(it) {}
		
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it) : current(rev_it.base()) { }
		
		~reverse_iterator(void)
		{
		}

		iterator_type base() const { return (current); }
		reference operator*() const { iterator_type tmp = current; return *--tmp; }
		reverse_iterator operator+ (difference_type n) const
		{ return static_cast<reverse_iterator>(current - n); }
		reverse_iterator& operator++() { --current; return *this; }
		reverse_iterator  operator++(int i) {
			(void) i;
			reverse_iterator tmp = *this;
			--current;
			return *this;
		}
		reverse_iterator& operator+= (difference_type n) { current -= n; return *this; }

		reverse_iterator operator- (difference_type n) const
		{ return static_cast<reverse_iterator>(current + n); }
		reverse_iterator& operator--() { ++current; return *this; }
		reverse_iterator  operator--(int i) {
			(void) i;
			reverse_iterator tmp = *this;
			++current;
			return *this;
		}
		reverse_iterator& operator-= (difference_type n) { current += n; return *this; }
		pointer operator->() const { return &(operator*()); }
		reference operator[](difference_type n) const { return *(*this + n); }

};
		template <class Iterator>
  		bool operator== (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs) { return (lhs.base() == rhs.base()); }

		template <class Iterator>
		bool operator!= (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs) { return !(lhs == rhs);}


		template <class Iterator>
		bool operator<  (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs) { return (lhs.base() > rhs.base()); }

		template <class Iterator>
  		bool operator<= (const reverse_iterator<Iterator>& lhs,
			   const reverse_iterator<Iterator>& rhs) { return (lhs.base() >= rhs.base());}
	
		template <class Iterator>
		bool operator>  (const reverse_iterator<Iterator>& lhs,
			   const reverse_iterator<Iterator>& rhs) { return (lhs.base() < rhs.base()); }

		template <class Iterator>
		bool operator>= (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs) { return (lhs.base() <= rhs.base());}

		template <class Iterator>
		reverse_iterator<Iterator> operator+ (
            typename reverse_iterator<Iterator>::difference_type n,
            const reverse_iterator<Iterator>& rev_it)
		{ return static_cast<reverse_iterator<Iterator> >(rev_it.base() - n); }

		template <class Iterator>
			typename reverse_iterator<Iterator>::difference_type operator-(
			const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs){
				return (static_cast<typename reverse_iterator<Iterator>::difference_type>(rhs.base() - lhs.base()));
				}
}

#endif // !ITERATOR_HPP

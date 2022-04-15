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
		typedef T*														iterator_type;
		typedef typename ft::iterator_traits<T*>::iterator_category		iterator_category;
		typedef typename ft::iterator_traits<T*>::value_type			value_type;
		typedef typename ft::iterator_traits<T*>::difference_type		difference_type;
		typedef typename ft::iterator_traits<T*>::reference				reference;
		typedef typename ft::iterator_traits<T*>::pointer				pointer;


		iterator_vector(void) : current() {}
		iterator_vector(T *ptr) : current(ptr) {}
		explicit iterator_vector (iterator_vector const & it) : current(it.base()) {}
		
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
template<typename T>
class iterator_tree
{
	private:
		T	*current;
		T	*tree_root;
	
	public:
		typedef T													iterator_type;
		typedef typename iterator_traits<T*>::value_type			value_type;
		typedef typename iterator_traits<T*>::difference_type		difference_type;
		typedef typename  iterator_type::reference_type 			reference;
		typedef typename  iterator_type::pointer					pointer;
		// typedef typename iterator_traits<T*>::reference				reference;
		// typedef typename iterator_traits<T*>::pointer				pointer;
		typedef std::bidirectional_iterator_tag						iterator_category;



		// default 
		iterator_tree(void) : current(NULL), tree_root(NULL) {}
		iterator_tree(T *current_pos, T *r) : current(current_pos), tree_root(r) {}
		//copy
		iterator_tree(iterator_tree<T> const &other) : current(other.current),
			tree_root(other.tree_root) {}
		// copy assignable
		iterator_tree &operator=(iterator_tree<T> const &other)
		{
			current = other.current;
			tree_root = other.tree_root;
			return (*this);
		}
		~iterator_tree(void) {}

		// iterator_tree(T *ptr) : current(ptr) {}
		
		// template <class Iter>
		// iterator_tree (const iterator_tree<Iter>& rev_it) : current(rev_it.current) { }

		iterator_type* base() const { return (current); }
		reference operator*() const {  return (current->value); }

		iterator_tree &operator++() { 
			current = current->successor();
			return *this;
		}

		iterator_tree  operator++(int i) {
			(void) i;
			iterator_tree tmp = *this;
			current = current->successor();
			return tmp;
		}

		iterator_tree &operator--() { 
			if (this->base()->isNil)
			{
				current = tree_root->subtree_last();
				return *this;
			}
			current = current->predecessor();
			return *this;
		}

		iterator_tree  operator--(int i) {
			(void) i;
			if (this->base()->isNil)
			{
				current = tree_root->subtree_last();
				return *this;
			}
			iterator_tree tmp = *this;
			current = current->predecessor();
			return tmp;
		}
		pointer operator->() const { return &((operator*())) ; }
};


		template <class Iterator>
		  bool operator== (const iterator_tree<Iterator>& lhs,
				const iterator_tree<Iterator>& rhs) { return (lhs.base() == rhs.base() ); }

		template <class Iterator>
		bool operator!= (const iterator_tree<Iterator>& lhs,
				const iterator_tree<Iterator>& rhs) { return !(lhs == rhs);}



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
		// typedef typename iterator_traits<T*>::iterator_category		iterator_category;
		typedef typename iterator_traits<T*>::value_type			value_type;
		typedef typename iterator_traits<T*>::difference_type		difference_type;
		typedef typename  iterator_type::reference_type 			reference;
		typedef typename  iterator_type::pointer					pointer;
		// typedef typename iterator_traits<T*>::reference				reference;
		// typedef typename iterator_traits<T*>::pointer				pointer;
		typedef std::bidirectional_iterator_tag						iterator_category;



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

		// iterator_tree(T *ptr) : current(ptr) {}
		
		// template <class Iter>
		// reverse_iterator_map (const reverse_iterator_map<Iter>& rev_it) : current(rev_it.current),
		// 	tree_root(rev_it)	{}

		iterator_type* base() const { return (current); }
		reference operator*() const {  return (current->value); }

		reverse_iterator_map &operator++() { 
			if (this->base()->isNil)
			{
				current = tree_root->subtree_last();
				return *this;
			}
			current = current->predecessor();
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
			current = current->predecessor();
			return tmp;

		}

		reverse_iterator_map &operator--() {
			if (this->base()->isNil)
			{
				current = tree_root->subtree_first();
				return *this;
			}
			current = current->successor();
			return *this;
		}

		reverse_iterator_map  operator--(int i) {
			(void) i;
			if (this->base()->isNil)
			{
				current = tree_root->subtree_first();
				return *this;
			}
			reverse_iterator_map tmp = *this;
			current = current->successor();
			return tmp;
		}
		pointer operator->() const { return &((operator*())) ; }
};


		template <class Iterator>
		  bool operator== (const reverse_iterator_map<Iterator>& lhs,
				const reverse_iterator_map<Iterator>& rhs) { return (lhs.base() == rhs.base()); }

		template <class Iterator>
		bool operator!= (const reverse_iterator_map<Iterator>& lhs,
				const reverse_iterator_map<Iterator>& rhs) { return !(lhs == rhs);}








}

#endif // !ITERATOR_HPP

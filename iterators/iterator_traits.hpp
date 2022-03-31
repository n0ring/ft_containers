#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

namespace ft
{

template <typename Iterator>
class iterator_traits
{
private:
	/* data */
public:
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
	typedef typename Iterator::iterator_category	iterator_category;
	iterator_traits(/* args */);
	~iterator_traits();
};



template<typename T>
class iterator_traits<T*>
{
    typedef ptrdiff_t					difference_type;
    typedef T							value_type;
    typedef T*							pointer;
    typedef T&							reference;
    typedef random_access_iterator_tag	iterator_category;
};

class input_iterator_tag  {};
class output_iterator_tag {};
class forward_iterator_tag       : public input_iterator_tag         {};
class bidirectional_iterator_tag : public forward_iterator_tag       {};
class random_access_iterator_tag : public bidirectional_iterator_tag {};

}

#endif // !ITERATOR_TRAITS_HPP
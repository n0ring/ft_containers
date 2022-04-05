#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{

template<typename T1, typename T2>
class Pair
{
		public:
		
		typedef	T1	first_type;
		typedef	T2	second_type;


		T1 first;
		T2 second;

		Pair(void) : first(), second()
		{
		}
		
		~Pair(void)
		{
		}

		template<class U, class V>
		Pair (const Pair<U,V>& pr) : first(pr.first), second(pr.second)
		{
		}

		Pair(const first_type& a, const second_type& b) : first(a), second(b)
		{
		}
		
		template<class U, class V>
		ft::Pair<U,V>& operator= (const ft::Pair<U, V>& pr)
		{
			this->first = pr.first;
			this->second = pr.second;
			return (*this);
		}
};

	template <class T1, class T2>
	bool operator== (const Pair<T1,T2>& lhs, const Pair<T1,T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool operator!= (const Pair<T1,T2>& lhs, const Pair<T1,T2>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool operator<  (const Pair<T1,T2>& lhs, const Pair<T1,T2>& rhs)
	{
    	return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template <class T1, class T2>
	bool operator<= (const Pair<T1,T2>& lhs, const Pair<T1,T2>& rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}

	template <class T1, class T2>
	bool operator> (const Pair<T1,T2>& lhs, const Pair<T1,T2>& rhs)
	{
		return (rhs < lhs);
	}
	
	template <class T1, class T2>
	bool operator>= (const Pair<T1,T2>& lhs, const Pair<T1,T2>& rhs)
	{
		return (rhs < lhs || rhs == lhs);
	}

	template <class T1,class T2>
	Pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return ( Pair<T1,T2>(x,y) );
	}
}

#endif // !PAIR_HPP
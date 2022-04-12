#ifndef ENABLE_IF
#define ENABLE_IF

// #include "Binary_tree.hpp"

namespace ft
{

template <bool B, typename T = void > 
struct enable_if {

};

template <typename T>
struct enable_if<true, T>
{
	typedef T type;
};

template<bool is_integral, typename T>
struct integral_res
{
	static const bool value = is_integral;
};

template <typename T>
struct integral_type : public integral_res<false, T> {};

template<> struct integral_type<char>					: public integral_res<true, char> {};
template<> struct integral_type<char16_t>				: public integral_res<true, char16_t> {};
template<> struct integral_type<int>					: public integral_res<true, int> {};
template<> struct integral_type<bool>					: public integral_res<true, bool> {};
template<> struct integral_type<char32_t>				: public integral_res<true, char32_t> {};
template<> struct integral_type<wchar_t>				: public integral_res<true, wchar_t> {};
template<> struct integral_type<signed char>			: public integral_res<true, signed char> {};
template<> struct integral_type<short int>				: public integral_res<true, short int> {};
template<> struct integral_type<long int>				: public integral_res<true, long int> {};
template<> struct integral_type<long long int>			: public integral_res<true, long long int> {};
template<> struct integral_type<unsigned char>			: public integral_res<true, unsigned char> {};
template<> struct integral_type<unsigned short int>		: public integral_res<true, unsigned short int> {};
template<> struct integral_type<unsigned int>			: public integral_res<true, unsigned int> {};
template<> struct integral_type<unsigned long int>		: public integral_res<true, unsigned long int> {};
template<> struct integral_type<unsigned long long int>	: public integral_res<true, unsigned long long int> {};


template<typename T>
struct is_integral : public integral_type<T> {};

template<class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
							 InputIt2 first2, InputIt2 last2)
{
	// for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
	for ( ; (first2 != last2); ++first1, (void) ++first2 ) {
		if (*first1 < *first2) return true;
		if (*first2 < *first1) return false;
	}
	// std::cout << first1 << std::endl;
	bool a = first1 == last1;
	bool b = first2 != last2;
	return (a) && (b);
}

template<class InputIt1, class InputIt2, class Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
							 InputIt2 first2, InputIt2 last2,
							 Compare comp)
{
	for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
		if (comp(*first1, *first2)) return true;
		if (comp(*first2, *first1)) return false;
	}
	return (first1 == last1) && (first2 != last2);
	// return first2!=last2;
}

template<class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, 
		   InputIt2 first2)
{
	for (; first1 != last1; ++first1, ++first2) {
		if (!(*first1 == *first2)) {
			return false;
		}
	}
	return true;
}

template<class InputIt1, class InputIt2, class BinaryPredicate>
bool equal(InputIt1 first1, InputIt1 last1, 
		   InputIt2 first2)
{
	for (; first1 != last1; first1++, first2++)
	{
		if (*first1 != *first2) {
			return false;
		}
	}
	return true;
}

	// template <class T> struct less : binary_function <T,T,bool> {
	// bool operator() (const T& x, const T& y) const {return x<y;}

}



// for tests

struct s_time_res
{
	time_t std_start;
	time_t std_end;
	time_t ft_start;
	time_t ft_end;
}  ;
// struct s_time_res	t_res;


time_t timer();
void print_res(std::string test, std::vector<int> &s,
		std::vector<int> &u, struct s_time_res &res);
void print_header();

void vector_test(void);
void stack_test(void);
void pair_test(void);
void map_test(void);
void set_test(void);


#endif // !ENABLE_IF

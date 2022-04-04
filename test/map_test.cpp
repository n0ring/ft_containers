#include <unistd.h>
#include <sys/time.h>
#include <stack>
#include <map>
#include <vector>
#include <iomanip>
#include <iterator>
#include "../pair.hpp"
#include "../Map.hpp"



static void construct_test_u(std::vector<int> &V, struct s_time_res &res)
{
	typedef ft::Map<int, int> _map;
	
	res.ft_start = timer();
	_map m;
	m[5] = 10;
	for (int i = 0; i < 20; i++)
		m[i] = i * 10;

	V.push_back(m[10]);
	V.push_back(m[11]);
	V.push_back(m[15]);
	V.push_back(m.size());

	_map m2(m.begin(), m.end());
	V.push_back(m[10]);
	V.push_back(m[11]);
	V.push_back(m[15]);
	V.push_back(m.size());

	_map m3(m2);
	V.push_back(m3[10]);
	V.push_back(m3[11]);
	V.push_back(m3[15]);
	V.push_back(m3.size());
	
	
	
	res.ft_end = timer();
}

static void construct_test_s(std::vector<int> &V, struct s_time_res &res)
{
	typedef std::map<int, int> _map;

	res.std_start = timer();

	_map m;

	m[5] = 10;
	for (int i = 0; i < 20; i++)
		m[i] = i * 10;

	V.push_back(m[10]);
	V.push_back(m[11]);
	V.push_back(m[15]);
	V.push_back(m.size());

	_map m2(m.begin(), m.end());
	V.push_back(m[10]);
	V.push_back(m[11]);
	V.push_back(m[15]);
	V.push_back(m.size());

	_map m3(m2);
	V.push_back(m3[10]);
	V.push_back(m3[11]);
	V.push_back(m3[15]);
	V.push_back(m3.size());

	res.std_end = timer();
}

static void insert_test_u(std::vector<int> &V, struct s_time_res &res)
{
	typedef ft::Map<int, int> _map;
	
	res.ft_start = timer();
	
	_map m;
	m[5000] = 5000000;
	for (int i = 0; i < 10000; i++)
		m[i] = i;
	V.push_back(m[10]);
	V.push_back(m[11]);
	V.push_back(m[1100]);
	V.push_back(m[15]);
	V.push_back(m.size());

	res.ft_end = timer();
}

static void insert_test_s(std::vector<int> &V, struct s_time_res &res)
{
	typedef std::map<int, int> _map;

	res.std_start = timer();

	_map m;
	m[5000] = 5000000;
	for (int i = 0; i < 10000; i++)
		m[i] = i;
	V.push_back(m[10]);
	V.push_back(m[11]);
	V.push_back(m[1100]);
	V.push_back(m[15]);
	V.push_back(m.size());

	res.std_end = timer();
}

static void empty_test_u(std::vector<int> &V, struct s_time_res &res)
{
	typedef ft::Map<int, int> _map;
	
	res.ft_start = timer();
	
	_map m;
	V.push_back(m.empty());

	for (int i = 0; i < 10; i++)
		m[i] = i;
	V.push_back(m[5]);
	V.push_back(m.empty());

	res.ft_end = timer();
}

static void empty_test_s(std::vector<int> &V, struct s_time_res &res)
{
	typedef std::map<int, int> _map;

	res.std_start = timer();

	_map m;
	V.push_back(m.empty());
	for (int i = 0; i < 10; i++)
		m[i] = i;
	V.push_back(m[5]);
	V.push_back(m.empty());

	res.std_end = timer();
}


static void begin_test_u(std::vector<int> &V, struct s_time_res &res)
{
	typedef ft::Map<int, int> _map;
	
	res.ft_start = timer();
	

	_map m;

	V.push_back(m.empty());
	for (int i = 1; i < 1000; i++)
		m[i] = i * 100;
	V.push_back(m[50]);
	V.push_back(m.empty());
	V.push_back(m.size());
	_map::iterator it = m.begin();
	V.push_back((*it).first);
	V.push_back(it->second);
	++it;
	V.push_back((*it).first);
	V.push_back(it->second);
	_map::iterator it2 = m.begin();
	V.push_back(it == it2);
	_map::iterator it3 = it;
	V.push_back(it == it3);
	it++;
	V.push_back(it->second);
	--it;

	V.push_back(it->second);
	it--;
	V.push_back(it->second);

	res.ft_end = timer();
}

static void begin_test_s(std::vector<int> &V, struct s_time_res &res)
{
	typedef std::map<int, int> _map;

	res.std_start = timer();

	_map m;

	V.push_back(m.empty());
	for (int i = 1; i < 1000; i++)
		m[i] = i * 100;
	V.push_back(m[50]);
	V.push_back(m.empty());
	V.push_back(m.size());
	_map::iterator it = m.begin();
	V.push_back((*it).first);
	V.push_back(it->second);
	++it;
	V.push_back((*it).first);
	V.push_back(it->second);
	_map::iterator it2 = m.begin();
	V.push_back(it == it2);
	_map::iterator it3 = it;
	V.push_back(it == it3);
	it++;
	V.push_back(it->second);
	--it;
	V.push_back(it->second);
	it--;
	V.push_back(it->second);

	res.std_end = timer();
}


static void end_test_u(std::vector<int> &V, struct s_time_res &res)
{
	typedef ft::Map<int, int> _map;
	
	res.ft_start = timer();
	

	_map m;

	V.push_back(m.empty());
	for (int i = 1; i < 10000; i++)
		m[i] = i * 100;
	V.push_back(m[50]);
	V.push_back(m.empty());
	V.push_back(m.size());
	_map::iterator ite = m.end();
	ite--;
	V.push_back(ite->first);
	V.push_back(ite->second);
	--ite;
	V.push_back(ite->first);
	V.push_back(ite->second);

	_map m2;
	m2[5] = 5;
	for (int i = 1; i < 10; i++)
		m2[i] = i;
	_map::iterator it = m2.begin();
	
	ite = m2.end();
	ite--;
	for (; it != ite; ite--)
		V.push_back(ite->first);

	res.ft_end = timer();
}

static void end_test_s(std::vector<int> &V, struct s_time_res &res)
{
	typedef std::map<int, int> _map;

	res.std_start = timer();

	_map m;
	V.push_back(m.empty());
	for (int i = 1; i < 10000; i++)
		m[i] = i * 100;
	V.push_back(m[50]);
	V.push_back(m.empty());
	V.push_back(m.size());
	_map::iterator ite = m.end();
	ite--;
	V.push_back(ite->first);
	V.push_back(ite->second);
	--ite;
	V.push_back(ite->first);
	V.push_back(ite->second);

	_map m2;
	m2[5] = 5;
	for (int i = 1; i < 10; i++)
		m2[i] = i;
	_map::iterator it = m2.begin();
	
	ite = m2.end();
	ite--;
	for (; it != ite; ite--)
		V.push_back(ite->first);

	res.std_end = timer();
}


static void rbegin_test_u(std::vector<int> &V, struct s_time_res &res)
{
	typedef ft::Map<int, int> _map;
	
	res.ft_start = timer();
	

	_map m;

	V.push_back(m.empty());
	m[5] = 5;
	for (int i = 1; i < 100; i++)
		m[i] = i * 100;
	_map::reverse_iterator it = m.rbegin();
	_map::reverse_iterator ite = m.rend();

	for (; it != ite; it++)
		V.push_back(it->first);



	res.ft_end = timer();
}

static void rbegin_test_s(std::vector<int> &V, struct s_time_res &res)
{
	typedef std::map<int, int> _map;

	res.std_start = timer();

	_map m;

	V.push_back(m.empty());
	m[5] = 5;
	for (int i = 1; i < 100; i++)
		m[i] = i * 100;
	_map::reverse_iterator it = m.rbegin();
	_map::reverse_iterator ite = m.rend();
	for (; it != ite; it++)
		V.push_back(it->first);
	
	res.std_end = timer();
}



// static void maxsize_test_u(std::vector<int> &V, struct s_time_res &res)
// {
// 	typedef ft::Map<int, int> _map;
	
// 	res.ft_start = timer();

// 	_map m;

// 	V.push_back(m.empty());
// 	V.push_back(m.max_size());
// 	std::cout << m.max_size() << " ft "  << std::endl;
// 	m[5] = 5;
// 	for (int i = 1; i < 100; i++)
// 		m[i] = i * 100;
// 	std::cout << m.max_size() << " ft "  << std::endl;
// 	V.push_back(m.max_size());

// 	res.ft_end = timer();
// }


// static void maxsize_test_s(std::vector<int> &V, struct s_time_res &res)
// {
// 	typedef std::map<int, int> _map;

// 	res.std_start = timer();

// 	_map m;

// 	V.push_back(m.empty());
// 	V.push_back(m.max_size());
// 	std::cout << m.max_size() << " std " << std::endl;
// 	m[5] = 5;
// 	for (int i = 1; i < 100; i++)
// 		m[i] = i * 100;
// 	std::cout << m.max_size() << " std " << std::endl;
// 	V.push_back(m.max_size());

// 	res.std_end = timer();
// }


static void insert_insert_test_u(std::vector<int> &V, struct s_time_res &res)
{
	typedef ft::Map<int, int> _map;
	
	res.ft_start = timer();
	

	_map m;
	V.push_back(m.empty());
	for (int i = 0; i < 1000; i++)
		m.insert(ft::make_pair(i, i * 100));

	V.push_back(m.insert(ft::make_pair(100, 100)).second);
	V.push_back(m.insert(ft::make_pair(1000000, 100000)).second);
	V.push_back(m[99]);
	
	_map m2;
	m2.insert(m.begin(), m.end());
	V.push_back(m2.size());
	V.push_back(m2[19]);
	V.push_back(m2[99]);
	V.push_back(m2[999]);


	res.ft_end = timer();
}

static void insert_insert_test_s(std::vector<int> &V, struct s_time_res &res)
{
	typedef std::map<int, int> _map;

	res.std_start = timer();

	_map m;
	V.push_back(m.empty());
	for (int i = 0; i < 1000; i++)
	{
		m.insert(std::make_pair(i, i * 100));
	}
		// m.insert(std::make_pair(i, i * 100));

	V.push_back(m.insert(std::make_pair(100, 100)).second);
	V.push_back(m.insert(std::make_pair(1000000, 100000)).second);
	V.push_back(m[99]);
		_map m2;
	
	
	m2.insert(m.begin(), m.end());
	V.push_back(m2.size());
	V.push_back(m2[19]);
	V.push_back(m2[99]);
	V.push_back(m2[999]);

	
	res.std_end = timer();
}

static void erase_test_u(std::vector<int> &V, struct s_time_res &res)
{
	typedef ft::Map<int, int> _map;
	
	res.ft_start = timer();
	

	_map m;
	V.push_back(m.empty());
	for (int i = 1; i < 3; i++)
		m.insert(ft::make_pair(i, i * 100));

	// m.show();
	m.erase( m.begin() );
	std::cout << "-----" << std::endl;
	// m.show();
	


	res.ft_end = timer();
}

// static void insert_insert_test_s(std::vector<int> &V, struct s_time_res &res)
// {
// 	typedef std::map<int, int> _map;

// 	res.std_start = timer();

// 	_map m;
// 	V.push_back(m.empty());
// 	for (int i = 0; i < 1000; i++)
// 	{
// 		m.insert(std::make_pair(i, i * 100));
// 	}
// 		// m.insert(std::make_pair(i, i * 100));

// 	V.push_back(m.insert(std::make_pair(100, 100)).second);
// 	V.push_back(m.insert(std::make_pair(1000000, 100000)).second);
// 	V.push_back(m[99]);
// 		_map m2;
	
	
// 	m2.insert(m.begin(), m.end());
// 	V.push_back(m2.size());
// 	V.push_back(m2[19]);
// 	V.push_back(m2[99]);
// 	V.push_back(m2[999]);

	
// 	res.std_end = timer();
// }


//----------------------------------------------------
void map_test(void)
{
	std::vector<int>	s;
	std::vector<int>	u;
	struct s_time_res	t_res;

	std::cout << "********************************************************************" << std::endl;
	std::cout << "********************************MAP*********************************" << std::endl;
	std::cout << "********************************************************************" << std::endl;

	print_header();

	construct_test_u(u, t_res);
	construct_test_s(s, t_res);
	print_res("Construct", s, u, t_res);
	u.clear();
	s.clear();

	insert_test_u(u, t_res);
	insert_test_s(s, t_res);
	print_res("Operator[]", s, u, t_res);
	u.clear();
	s.clear();

	empty_test_u(u, t_res);
	empty_test_s(s, t_res);
	print_res("Empty", s, u, t_res);
	u.clear();
	s.clear();

	begin_test_u(u, t_res);
	begin_test_s(s, t_res);
	print_res("Begin", s, u, t_res);
	u.clear();
	s.clear();

	end_test_u(u, t_res);
	end_test_s(s, t_res);
	print_res("end", s, u, t_res);
	u.clear();
	s.clear();

	rbegin_test_u(u, t_res);
	rbegin_test_s(s, t_res);
	print_res("rbegin", s, u, t_res);
	u.clear();
	s.clear();

	// maxsize_test_u(u, t_res);
	// maxsize_test_s(s, t_res);
	// print_res("maxsize", s, u, t_res);
	// u.clear();
	// s.clear();

	insert_insert_test_u(u, t_res);
	insert_insert_test_s(s, t_res);
	print_res("insert", s, u, t_res);
	u.clear();
	s.clear();

	erase_test_u(u, t_res);
	// insert_insert_test_s(s, t_res);
	// print_res("insert", s, u, t_res);
	// u.clear();
	// s.clear();
}
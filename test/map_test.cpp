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
	m[10] = 21;
	m[10] = 42;
	V.push_back(m[10]);
	V.push_back(m[11]);
	V.push_back(m[15]);
	V.push_back(m.size());
	
	res.ft_end = timer();
}

static void construct_test_s(std::vector<int> &V, struct s_time_res &res)
{
	typedef std::map<int, int> _map;

	res.std_start = timer();

	_map m;
	m[10] = 21;
	m[10] = 42;
	V.push_back(m[10]);
	V.push_back(m[11]);
	V.push_back(m[15]);
	V.push_back(m.size());
	res.std_end = timer();
}

static void insert_test_u(std::vector<int> &V, struct s_time_res &res)
{
	typedef ft::Map<int, int> _map;
	
	res.ft_start = timer();
	
	_map m;
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
		m[i] = i;
	V.push_back(m[50]);
	V.push_back(m.empty());
	V.push_back(m.size());
	_map::iterator it = m.begin();
	std::cout << (*it).first << std::endl;
	std::cout << (*it).second << std::endl;
	// V.push_back(m.begin()->first);

	res.ft_end = timer();
}

static void begin_test_s(std::vector<int> &V, struct s_time_res &res)
{
	typedef std::map<int, int> _map;

	res.std_start = timer();

	_map m;

	V.push_back(m.empty());
	for (int i = 1; i < 1000; i++)
		m[i] = i;
	V.push_back(m[50]);
	V.push_back(m.empty());
	V.push_back(m.size());
	_map::iterator it = m.begin();
	std::cout << (*it).first << std::endl;

	// V.push_back(m.begin()->first);


	res.std_end = timer();
}




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

}
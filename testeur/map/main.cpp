#include "../../container/map.hpp"
#include <map>
#include <list>

#ifndef TESTED_NAMESPACE
# define TESTED_NAMESPACE ft
#endif

#define T1 int
#define T2 std::string

typedef TESTED_NAMESPACE::map<T1, T2>::iterator iterator;
typedef TESTED_NAMESPACE::map<T1, T2>::const_iterator const_iterator;
typedef TESTED_NAMESPACE::pair<const T1, T2> T3;

void	print_content(TESTED_NAMESPACE::map<T1, T2> &m)
{
	TESTED_NAMESPACE::map<T1, T2>::iterator	        it = m.begin();
	TESTED_NAMESPACE::map<T1, T2>::iterator	        ite = m.end();
	TESTED_NAMESPACE::map<T1, T2>::reverse_iterator	rev = m.rbegin();
	TESTED_NAMESPACE::map<T1, T2>::reverse_iterator	reve = m.rend();

	std::cout << "Content :\n";
	for (; it != ite; ++it)
		std::cout << "\t\t" << "Key: " << it->first << "\tVal: " << it->second << '\n';
	std::cout << "\n";

	std::cout << "Reverse content :\n";
	for (; rev != reve; ++rev)
		std::cout << "\t\t" << "Key: " << rev->first << "\tVal: " << rev->second << '\n';
	std::cout << "\n";

    std::cout << "EMPTY\t\t" << m.empty() << std::endl;
	std::cout << "SIZE\t\t" << m.size() << std::endl;
	std::cout << "MAX_SIZE\t" << m.max_size() << std::endl;
}

void		ft_bound(TESTED_NAMESPACE::map<T1, T2> &m, const T1 &param)
{
	const_iterator lower;
	const_iterator upper;
	const_iterator ite = m.end();
	TESTED_NAMESPACE::pair<const_iterator, const_iterator> range;

	lower = m.lower_bound(param);
	upper = m.upper_bound(param);
	range = m.equal_range(param);

	std::cout << "lower bound: " << (lower == ite ? "end()" : lower->second) << std::endl;
	std::cout << "upper bound: " << (upper == ite ? "end()" : upper->second) << std::endl;
	std::cout << "equal range: " << (range.first == lower && range.second == upper) << std::endl;
}

void		ft_const_bound(TESTED_NAMESPACE::map<T1, T2> &m, const T1 &param)
{
	iterator lower;
	iterator upper;
	iterator ite = m.end();
	TESTED_NAMESPACE::pair<iterator, iterator> range;

	lower = m.lower_bound(param);
	upper = m.upper_bound(param);
	range = m.equal_range(param);

	std::cout << "lower bound: " << (lower == ite ? "end()" : lower->second) << std::endl;
	std::cout << "upper bound: " << (upper == ite ? "end()" : upper->second) << std::endl;
	std::cout << "equal range: " << (range.first == lower && range.second == upper) << std::endl;
}
int        main()
{
    std::cout << "MAP" << std::endl;
	//DEFAULT CONSTUCTOR 
    TESTED_NAMESPACE::map<T1, T2> m;

	TESTED_NAMESPACE::pair<int, std::string> p = TESTED_NAMESPACE::make_pair(12, "toto");
	m.insert(p);
	m.insert(TESTED_NAMESPACE::make_pair(14, "helo"));
	m.insert(TESTED_NAMESPACE::make_pair(9, "Bonjour"));
	m.insert(TESTED_NAMESPACE::make_pair(1, "BB QQ"));

	// SAME KEY INSERTION
	m.insert(TESTED_NAMESPACE::make_pair(22, "XDDFG"));
	m.insert(TESTED_NAMESPACE::make_pair(22, "YOYO"));

	m.insert(TESTED_NAMESPACE::make_pair(90, "YYYYYYY"));
	m.insert(TESTED_NAMESPACE::make_pair(54, "BBBBBBBB"));
	print_content(m);

	//RANGE CONSTRUCTOR
	TESTED_NAMESPACE::map<T1, T2> m_range(++(m.begin()), --(m.end()));
	print_content(m_range);

	//COPY CONSTRUCTOR
	TESTED_NAMESPACE::map<T1, T2> m_copy(m_range);
	print_content(m_copy);

	// INVALID ITERATOR
	iterator it = m_copy.begin();
	iterator ite = m_copy.end();

	m_copy.insert(TESTED_NAMESPACE::make_pair(42, "AAAAAAAAA"));
	m_copy.insert(TESTED_NAMESPACE::make_pair(12, "CCCCCCC"));

	m_copy.erase(++(m_copy.begin()));
	m_copy.erase(--(m_copy.end()));

	std::cout << it->first << std::endl;
	std::cout << (--ite)->first << std::endl;

	// INSERT WITH HINT
	m_copy.insert(++(m_copy.begin()), TESTED_NAMESPACE::make_pair(-43, "HHHHHHH"));
	m_copy.insert(++(m_copy.begin()), TESTED_NAMESPACE::make_pair(-54, "MMMMMMM"));
	m_copy.insert(++(++(m_copy.begin())), TESTED_NAMESPACE::make_pair(1432, "XXXXXXX"));

	print_content(m_copy);

	// INSERT RANGE
	std::list<T3> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 1; i < lst_size; ++i)
		lst.push_back(T3(i, std::string((lst_size - i), i + 65)));
	m_range.insert(lst.begin(), lst.end());
	print_content(m_range);

	// erase by key
	m_range.erase(1);
	m_range.erase(2);
	m_range.erase(7);

	m_range.erase(++(m_range.begin()), (--m_range.end()));
	m_copy.erase(m_copy.begin(), m_copy.end());
	
	m.insert(++(++(lst.begin())), lst.end());
	iterator it_m = m.begin();
	it_m++;
	it_m++;
	it_m++;
	it_m++;
	m.erase(it_m, m.end());

	print_content(m);
	print_content(m_range);
	print_content(m_copy);

	//SWAP FUNCTION
	std::cout << "SWAP" << std::endl;
	iterator itm = m.begin();
	iterator itrange = m_range.begin();

	std::cout << "BEFORE SWAP" << std::endl;
	print_content(m);
	print_content(m_range);
	m.swap(m_range);
	std::cout << "AFTER SWAP" << std::endl;
	print_content(m);
	print_content(m_range);

	std::cout << "ITERATOR VALIDITY" << std::endl;
	std::cout << (itm == m_range.begin()) << std::endl;
	std::cout << (itrange == m.begin()) << std::endl;

	// BOUND FUNCTION
	std::list<T3> lst1;
	for (unsigned int i = 1; i < lst_size; ++i)
		lst1.push_back(T3(i, std::string((lst_size - i), i + 65)));
	TESTED_NAMESPACE::map<T1, T2> mb(lst1.begin(), lst1.end());

	ft_bound(mb, 3);
	ft_bound(mb, 1);
	ft_bound(mb, 2);
	ft_bound(mb, 5);
	ft_bound(mb, 6);
	ft_bound(mb, 7);

	ft_const_bound(mb, 3);
	ft_const_bound(mb, 1);
	ft_const_bound(mb, 2);
	ft_const_bound(mb, 5);
	ft_const_bound(mb, 6);
	ft_const_bound(mb, 7);

	mb[16] = "LLLLL";
	mb[54] = "PPPPPP";
	mb[32] = "aaaaaa";

	const_iterator nn = mb.find(16);
	iterator n = mb.find(16);

	std::cout << nn->first << std::endl;
	std::cout << n->first << std::endl;

	mb[16] = "KKKK";
	std::cout << mb.count(16) << std::endl;

	mb.clear();
	m.clear();
	m_range.clear();

	print_content(mb);
	print_content(m);
	print_content(m_range);
}
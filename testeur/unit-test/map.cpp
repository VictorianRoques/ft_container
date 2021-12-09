#include "map.hpp"

void	print_content(TESTED_NAMESPACE::map<int, int> &m)
{
	TESTED_NAMESPACE::map<int, int>::iterator	it = m.begin();
	TESTED_NAMESPACE::map<int, int>::iterator	ite = m.end();

	TESTED_NAMESPACE::map<int, int>::reverse_iterator	rev = m.rbegin();
	TESTED_NAMESPACE::map<int, int>::reverse_iterator	reve = m.rend();

	std::cout << "Content :\n";
	for (; it != ite; ++it)
		std::cout << "\t\t" << "Key: " << it->first << "\tVal: " << it->second << '\n';
	std::cout << "\n";

	std::cout << "Reverse content :\n";
	for (; rev != reve; ++rev)
		std::cout << "\t\t" << "Key: " << rev->first << "\tVal: " << rev->second << '\n';
	std::cout << "\n";
}

void	print_size(TESTED_NAMESPACE::map<int, int> &v)
{
	std::cout << "EMPTY\t\t" << v.empty() << std::endl;
	std::cout << "SIZE\t\t" << v.size() << std::endl;
	std::cout << "MAX_SIZE\t" << v.max_size() << std::endl;
}

void    map(std::string unit_test)
{
    std::cout << "\n\nMAP\n\n";
	std::cout << "********************\n\n";

	std::cout << "constructor & insert\n";
	std::cout << "#################################\n";

	TESTED_NAMESPACE::map<int, int>	m;
	TESTED_NAMESPACE::map<int, int>	m1;
	TESTED_NAMESPACE::map<int, int>	const m2;

	m1.insert(TESTED_NAMESPACE::make_pair(10, 20));
	m1.insert(TESTED_NAMESPACE::make_pair(30, 78));
	m1.insert(TESTED_NAMESPACE::make_pair(2, 198));
	m1.insert(TESTED_NAMESPACE::make_pair(12, 78));
	m1.insert(TESTED_NAMESPACE::make_pair(10, 19));
	m1.insert(TESTED_NAMESPACE::make_pair(85, 5));
	m1.insert(TESTED_NAMESPACE::make_pair(38, 2));
	m1.insert(TESTED_NAMESPACE::make_pair(0, 56));
	m1.insert(TESTED_NAMESPACE::make_pair(1, 2));
	m1.insert(TESTED_NAMESPACE::make_pair(99, 7845));
	m1.insert(TESTED_NAMESPACE::make_pair(89732, 2));
	m1.insert(TESTED_NAMESPACE::make_pair(-1982, 2));

	TESTED_NAMESPACE::map<int, int>	m_range(++m1.begin(), --m1.end());
	TESTED_NAMESPACE::map<int, int>	m_copy(m_range);

	std::cout << "\nempty map\n";
	std::cout << "#################################\n";
	print_content(m); print_size(m);

	std::cout << "\ninsert(val)\n";
	std::cout << "#################################\n";
	print_content(m1); print_size(m1);

	std::cout << "\nrange map\n";
	std::cout << "#################################\n";
	print_content(m_range); print_size(m_range);

	std::cout << "\ncopy map\n";
	std::cout << "#################################\n";
	print_content(m_copy); print_size(m_copy);

  	TESTED_NAMESPACE::pair <int,int>			elem;
	elem = TESTED_NAMESPACE::make_pair(-8, 76823);
	m_copy.insert(++(++(m_copy.begin())), elem);

	std::cout << "\ninsert map (pos, val)\n";
	std::cout << "#################################\n";
	print_content(m_copy); print_size(m_copy);

	std::cout << "\ninsert map (begin, end)\n";
	std::cout << "#################################\n";
	m.insert(m_copy.begin(), --(--(m_copy.end())));
	print_content(m); print_size(m);

	std::cout << "\nerase(pos)\n";
	std::cout << "#################################\n";
	std::cout << "* Before erase:\n";
	print_content(m_copy); print_size(m_copy);

	m_copy.erase(++m_copy.begin());

	std::cout << "* After erase:\n";
	print_content(m_copy); print_size(m_copy);

	std::cout << "\nerase(key)\n";
	std::cout << "#################################\n";
	std::cout << "* Before erase:\n";
	print_content(m_copy); print_size(m_copy);

	m_copy.erase(12);

	std::cout << "* After erase:\n";
	print_content(m_copy); print_size(m_copy);

	std::cout << "\nerase(begin, end)\n";
	std::cout << "#################################\n";
	std::cout << "* Before erase:\n";


	print_content(m_copy); print_size(m_copy);
	m_copy.erase(m_copy.begin(), --m_copy.end());
	std::cout << "* After erase:\n";
	print_content(m_copy); print_size(m_copy);

	std::cout << "\nswap\n";
	std::cout << "#################################\n";
	std::cout << "* Before swap:\n";
	print_content(m_copy); print_size(m_copy);
	print_content(m); print_size(m);

	m_copy.swap(m);

	std::cout << "* After swap:\n";
	print_content(m_copy); print_size(m_copy);
	print_content(m); print_size(m);

	std::cout << "\nFind\n";
	std::cout << "#################################\n";
	std::cout << "res: " << m_copy.find(38)->first << std::endl;

	std::cout << "\nCount\n";
	std::cout << "#################################\n";
	std::cout << "res: " << m_copy.count(38) << std::endl;

	std::cout << "\nClear\n";
	std::cout << "#################################\n";
	m_copy.clear();
	print_content(m_copy); print_size(m_copy);
}
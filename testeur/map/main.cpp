#include "../../container/map.hpp"
#include <map>

#ifndef TESTED_NAMESPACE
# define TESTED_NAMESPACE ft
#endif

#define T1 int
#define T2 std::string
typedef TESTED_NAMESPACE::map<T1, T2>::iterator iterator;

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

int        main()
{
    std::cout << "MAP" << std::endl;
    TESTED_NAMESPACE::map<T1, T2> m;
    print_content(m);
}
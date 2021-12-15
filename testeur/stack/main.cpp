#include <stack>
#include "../../container/stack.hpp"

#ifndef TESTED_NAMESPACE
# define TESTED_NAMESPACE ft
#endif

#define TESTED_TYPE int

typedef TESTED_NAMESPACE::stack<TESTED_TYPE> _stack;

static int i = 0;

template <typename T_STACK>
void	printSize(T_STACK &stck, bool print_content = 1)
{
	std::cout << "size: " << stck.size() << std::endl;
	if (print_content)
	{
		std::cout << std::endl << "Content was:" << std::endl;
		while (stck.size() != 0) {
			std::cout << "- " << stck.top() << std::endl;
			stck.pop();
		}
	}
	std::cout << "###############################################" << std::endl;
}

void        comp(const _stack &s1, _stack &s2)
{
    std::cout << "###########[" << i++ << "]##########" << std::endl;
    std::cout << "eq: " << (s1 == s2) << " | ne: " << (s1 != s2) << std::endl;
	std::cout << "lt: " << (s1 <  s2) << " | le: " << (s1 <= s2) << std::endl;
	std::cout << "gt: " << (s1 >  s2) << " | ge: " << (s1 >= s2) << std::endl;
}
int main()
{
    _stack s;

    std::cout << "empty: " << s.empty() << std::endl;
    std::cout << "size: " << s.size() << std::endl;

    for (int i = 0; i < 10; i++)
        s.push(i);
    printSize(s);

    _stack s1;
    s1.push(25);
    s1.push(553);
    s1.push(6543);
    s1.push(511);
    s1.push(0);

    _stack s2;

    s1.push(84);
    s1.push(41);
    s1.push(2313);
    s1.push(0);

    comp(s1, s2);

    _stack s3;
    s1.push(25);
    s1.push(553);
    s1.push(6543);
    s1.push(511);
    s1.push(0);

    comp(s1, s3);

    _stack s4;

    s4.push(2);
    s4.push(63);
    s4.push(63);

    comp(s1, s4);
    comp(s2, s4);

    printSize(s1);
    printSize(s2);
    printSize(s3);
    printSize(s4);
}
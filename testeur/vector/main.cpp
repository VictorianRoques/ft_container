#include "../../container/vector.hpp"
#include <vector>

#ifndef TESTED_NAMESPACE
# define TESTED_NAMESPACE ft
#endif

#define TESTED_TYPE int

void	printSize(TESTED_NAMESPACE::vector<TESTED_TYPE> const &vct, bool print_content = true)
{
	const size_t size = vct.size();
	const size_t capacity = vct.capacity();
	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity: " << isCapacityOk << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator it = vct.begin();
		TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

void		at()
{
	std::cout << "AT" << std::endl;
	TESTED_NAMESPACE::vector<TESTED_TYPE>vct(7);

	for (unsigned long int i = 0; i <vct.size(); ++i)
	{
		vct.at(i) = (vct.size() - i) * 3;
		std::cout << "vct.at(): " <<vct.at(i) << " | ";
		std::cout << "vct[]: " <<vct[i] << std::endl;
	}
	vct.front();
	vct.back();
	printSize(vct);
	TESTED_NAMESPACE::vector<TESTED_TYPE> const vct_c(vct);

	std::cout << "front(): " <<vct.front() << " " <<vct_c.front() << std::endl;
	std::cout << "back(): " <<vct.back() << " " << vct_c.back() << std::endl;
	try {
		vct.at(10) = 42;
	}
	catch (std::out_of_range &e) {
		std::cout << "Catch out_of_range exception!" << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Catch exception: " << e.what() << std::endl;
	}
	
}
void	assign()
{
	std::cout << "ASSIGN" << std::endl;
	TESTED_NAMESPACE::vector<TESTED_TYPE> v(10);
	TESTED_NAMESPACE::vector<TESTED_TYPE> v1(12);

	for (unsigned long int i = 0; i < 10; ++i)
		v[i] = (v.size() - i) * 3;
	for (unsigned long int i = 0; i < 10; ++i)
		v1[i] = (v1.size() - i) * 5;
	printSize(v);
	printSize(v1);

	TESTED_NAMESPACE::vector<TESTED_TYPE> v_fill(v.begin(), v.end());
	TESTED_NAMESPACE::vector<TESTED_TYPE> v_copy(v1);
	v.assign(6, 23);
	v1.assign(v.begin(), v.end());

	printSize(v);
	printSize(v1);
	printSize(v_fill);
	printSize(v_copy);
}

void	insert()
{
	std::cout << "INSERT" << std::endl;
	TESTED_NAMESPACE::vector<TESTED_TYPE> v;

	for (unsigned int i = 0; i < 10; i++)
		v.insert(v.begin(), (v.size() - 1) * 3);
	
	TESTED_NAMESPACE::vector<TESTED_TYPE> v_fill;
	v_fill.push_back(12);
	v_fill.push_back(14);
	v_fill.insert(++(v_fill.begin()), 10, 12);

	TESTED_NAMESPACE::vector<TESTED_TYPE> v_range;
	v_range.push_back(5);
	v_range.push_back(9);
	v_range.insert(++(v_range.begin()), v_fill.begin(), v_fill.end());

	v.insert(v.begin() + 2, 16);
	v.insert(v.end() - 2, 1, 12);
	v.insert(v.begin() + 1, v_fill.begin(), v_fill.end());

	v_fill.insert(v_fill.begin() + 1, 15);
	v_fill.insert(v_fill.end(), 2, 6);

	printSize(v);
	printSize(v_fill);
	printSize(v_range);

}

void	erase()
{
	std::cout << "ERASE" << std::endl;
	TESTED_NAMESPACE::vector<TESTED_TYPE> v;
	for (unsigned int i = 0; i < 10; i++)
		v.insert(v.begin(), (v.size() - 1) * 3);
	TESTED_NAMESPACE::vector<TESTED_TYPE> v_fill;
	v_fill.insert(v_fill.begin(), 10, 12);
	TESTED_NAMESPACE::vector<TESTED_TYPE> v_range;
	v_range.insert(v_range.begin(), v_fill.begin(), v_fill.end());

	v.erase(v.begin() + 2);
	v.erase(v.end()- 2);
	v_fill.erase(v_fill.begin() + 1, v_fill.end() - 2);
	v_range.erase(v_range.begin() + 1, v_range.end());
	
	printSize(v);
	printSize(v_fill);
	printSize(v_range);

	TESTED_NAMESPACE::vector<TESTED_TYPE> v1(10);
	for (unsigned long int i = 0; i < v1.size(); ++i)
		v1[i] = i;
	
	v1.erase((v1.begin() + 3));
	v1.erase((v1.begin() + 2));
	v1.erase((v1.end() - 2));
	v1.erase((v1.end() - 1));
	v1.erase(v1.begin(), ++(v1.begin()));
}

void	push_back()
{
	std::cout << "PUSH BACK" << std::endl;
	TESTED_NAMESPACE::vector<TESTED_TYPE> v(6);
	TESTED_NAMESPACE::vector<TESTED_TYPE> v1;
	for (unsigned int i = 0; i < 10; i++)
	{
		v.push_back((v.size() - 1) * 3);
	}
	for (unsigned int i = 0; i < 7; i++)
	{
		v1.push_back((v1.size() - 2) * 3);
	}
	printSize(v);
	printSize(v1);
}

void	pop_back()
{
	std::cout << "POP BACK" << std::endl;
	TESTED_NAMESPACE::vector<TESTED_TYPE> v;
	for (unsigned int i = 0; i < 10; i++)
		v.push_back((v.size() - 1) * 3);

	TESTED_NAMESPACE::vector<TESTED_TYPE> v1(v);
	for (unsigned int i = 0; i < 5; i++)
		v.pop_back();
	for (unsigned int i = 0; i < 7; i++)
		v1.pop_back();
	printSize(v);
	printSize(v1);
}

void    iterator()
{
	std::cout << "ITERATOR" << std::endl;
    TESTED_NAMESPACE::vector<TESTED_TYPE> vi(10);
		for (unsigned long int i = 0; i < 10; ++i)
		vi[i] = (vi.size() - i) * 3;

	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = vi.begin();
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator ite = vi.end();

	std::cout << *(++it) << std::endl;
	std::cout << *(it++) << std::endl;
	std::cout << *it++ << std::endl;
	std::cout << *++it << std::endl;

	std::cout << *(--ite) << std::endl;
	std::cout << *(ite--) << std::endl;
	std::cout << *--ite << std::endl;
	std::cout << *ite-- << std::endl;


	std::cout << *(--it) << std::endl;
	std::cout << *(it--) << std::endl;
	std::cout << *it-- << std::endl;
	std::cout << *--it << std::endl;

	std::cout << *(it += 2) << std::endl;
	std::cout << *(it -= 2) << std::endl;

	std::cout << *(it + 3) << std::endl;
	std::cout << *(ite - 3) << std::endl;

	TESTED_NAMESPACE::vector<TESTED_TYPE>::reverse_iterator rit = vi.rbegin();
	TESTED_NAMESPACE::vector<TESTED_TYPE>::reverse_iterator rite = vi.rend();

	std::cout << *(++rit) << std::endl;
	std::cout << *(rit++) << std::endl;
	std::cout << *rit++ << std::endl;
	std::cout << *++rit << std::endl;

	std::cout << *(--rite) << std::endl;
	std::cout << *(rite--) << std::endl;
	std::cout << *--rite << std::endl;
	std::cout << *rite-- << std::endl;


	std::cout << *(--rit) << std::endl;
	std::cout << *(rit--) << std::endl;
	std::cout << *rit-- << std::endl;
	std::cout << *--rit << std::endl;

	std::cout << *(rit += 2) << std::endl;
	std::cout << *(rit -= 2) << std::endl;

	std::cout << *(rit + 3) << std::endl;
	std::cout << *(rite - 3) << std::endl;

	// CONST COMPARE OPERATOR
	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator cit(it);
	std::cout << (ite == cit) << std::endl;
	std::cout << (ite != cit) << std::endl;
	std::cout << (ite < cit) << std::endl;
	std::cout << (ite <= cit) << std::endl;
	std::cout << (ite > cit) << std::endl;
	std::cout << (ite >= cit) << std::endl;

	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator crite(rite);

	std::cout << (rit == crite) << std::endl;
	std::cout << (rit != crite) << std::endl;
	std::cout << (rit < crite) << std::endl;
	std::cout << (rit <= crite) << std::endl;
	std::cout << (rit > crite) << std::endl;
	std::cout << (rit >= crite) << std::endl;

}

void	swap()
{
	std::cout << "SWAP" << std::endl;
	TESTED_NAMESPACE::vector<TESTED_TYPE> foo(3, 15);
	TESTED_NAMESPACE::vector<TESTED_TYPE> bar(5, 42);
	
	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator it_foo = foo.begin();
	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator it_bar = bar.begin();
	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator ite_foo = foo.end();
	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator ite_bar = bar.end();

	std::cout << "BEFORE SWAP" << std::endl;

	std::cout << "foo contains:" << std::endl;
	printSize(foo);
	std::cout << "bar contains:" << std::endl;
	printSize(bar);

	foo.swap(bar);

	std::cout << "AFTER SWAP" << std::endl;

	std::cout << "foo contains:" << std::endl;
	printSize(foo);
	std::cout << "bar contains:" << std::endl;
	printSize(bar);

	std::cout << "Iterator validity:" << std::endl;
	std::cout << (it_foo == bar.begin()) << std::endl;
	std::cout << (it_bar == foo.begin()) << std::endl;
	std::cout << (ite_foo == bar.end()) << std::endl;
	std::cout << (ite_bar == foo.end()) << std::endl;
}

int     main()
{
	at();
	assign();
	insert();
	erase();
	push_back();
	pop_back();
	iterator();
	swap();
}
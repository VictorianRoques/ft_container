#include "vector.hpp"
#include <vector>

int		main()
{
	// std::vector<int> toto(3, 3);

	// std::vector<int>::iterator it = toto.begin();
	// std::vector<int>::iterator ite = toto.end();

	// std::cout << "Ha:" << toto.capacity() << std::endl;
	// toto.insert(it, 4); 
	// std::cout << toto.capacity() << std::endl;

	// std::vector<int>::iterator a = toto.begin();
	// std::vector<int>::iterator b = toto.end();

	// while (a != b)
	// {
	// 	std::cout << *a << std::endl;
	// 	a++;
	// }

	std::vector<int> foo (10,100);   // three ints with a value of 100
	std::vector<int> bar(3, 200);

	// ft::vector<int>::iterator it = foo.begin();
	// ft::vector<int>::iterator ite = foo.end();
	// ft::vector<int>::iterator a = bar.begin();
	// ft::vector<int>::iterator b = bar.end();

	std::cout << "cap: " << foo.capacity() << std::endl;
	std::cout << "cap: " << foo.size() << std::endl;

	std::cout << "foo contains:";
  	for (unsigned i=0; i<foo.size(); i++)
    	std::cout << ' ' << foo[i];
  	std::cout << '\n';

	foo.assign(17, 4);
	std::cout << "cap: " << foo.capacity() << std::endl;
	std::cout << "cap: " << foo.size() << std::endl;
	std::cout << "foo contains:";
  	for (unsigned i=0; i<foo.size(); i++)
    	std::cout << ' ' << foo[i];
  	std::cout << '\n';

}
#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"
# include <string>

std::string convertToString(char* a, int size)
{
    int i;
    std::string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

int		main(int ac, char **argv)
{
	std::string unit_test;
	if (ac == 1)
	{
		vector(unit_test);
		map(unit_test);
		stack(unit_test);
	}
	else if (ac == 2)
	{
		std::string container(argv[1]);
		if (container == "vector")
			vector(unit_test);
		else if (container == "map")
			map(unit_test);
		else if (container == "stack")
			stack(unit_test);
	}
	else if (ac == 3)
	{
		std::string container(argv[1]);
		std::string unit_test(argv[2]);
		if (container == "vector")
			vector(unit_test);
		else if (container == "map")
			map(unit_test);
		else if (container == "stack")
			stack(unit_test);
	}

}

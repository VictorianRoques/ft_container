#include "stack.hpp"

void        stack(std::string unit_test)
{
    std::cout << "\n\nSTACK\n\n";
	std::cout << "********************\n\n";

	std::cout << "\nconstructor & empty & size\n";
	std::cout << "#################################\n";

	TESTED_NAMESPACE::stack<int> stack;
	TESTED_NAMESPACE::stack<int> copy_stack;

	std::cout << stack.size() << std::endl;
	std::cout << stack.empty() << std::endl;

	stack.push(10);
	stack.push(2);
	stack.push(4);
	stack.push(18);

	std::cout << stack.size() << std::endl;
	std::cout << stack.empty() << std::endl;

	std::cout << "\ncopy stack\n";
	std::cout << "#################################\n";

	copy_stack = stack;
	std::cout << "SIZE\t| Srcs: " << stack.size() << '\t' << "Copy: " << copy_stack.size() << std::endl;
	std::cout << "EMPTY\t| Srcs: " << stack.empty() << '\t' << "Copy: " << copy_stack.empty() << std::endl;
	std::cout << "TOP\t| Srcs: " << stack.top() << '\t' << "Copy: " << copy_stack.top() << std::endl;

	std::cout << "\npop last elem (18)\n";
	std::cout << "#################################\n";

	stack.pop();

	std::cout << "SIZE\t| Srcs: " << stack.size() << '\t' << "Copy: " << copy_stack.size() << std::endl;
	std::cout << "EMPTY\t| Srcs: " << stack.empty() << '\t' << "Copy: " << copy_stack.empty() << std::endl;
	std::cout << "TOP\t| Srcs: " << stack.top() << '\t' << "Copy: " << copy_stack.top() << std::endl;

	std::cout << "\ncompare stack1 < stack2\n";
	std::cout << "#################################\n";

	std::cout << "stack1 = stack2:\t" << (stack == copy_stack) << std::endl;
	std::cout << "stack1 != stack2:\t" << (stack != copy_stack) << std::endl;
	std::cout << "stack1 < stack2:\t" << (stack < copy_stack) << std::endl;
	std::cout << "stack1 > stack2:\t" << (stack > copy_stack) << std::endl;

	std::cout << "\nswap\n";
	std::cout << "#################################\n";
	std::cout << "* Before swap:\n";
	std::cout << "SIZE\t| Srcs: " << stack.size() << '\t' << "Copy: " << copy_stack.size() << std::endl;
	std::cout << "EMPTY\t| Srcs: " << stack.empty() << '\t' << "Copy: " << copy_stack.empty() << std::endl;
	std::cout << "TOP\t| Srcs: " << stack.top() << '\t' << "Copy: " << copy_stack.top() << std::endl;
	std::cout << "SIZE\t| Srcs: " << copy_stack.size() << '\t' << "Copy: " << copy_stack.size() << std::endl;
	std::cout << "EMPTY\t| Srcs: " << copy_stack.empty() << '\t' << "Copy: " << copy_stack.empty() << std::endl;
	std::cout << "TOP\t| Srcs: " << copy_stack.top() << '\t' << "Copy: " << copy_stack.top() << std::endl;

	swap(stack, copy_stack);

	std::cout << "* After swap:\n";
	std::cout << "SIZE\t| Srcs: " << stack.size() << '\t' << "Copy: " << copy_stack.size() << std::endl;
	std::cout << "EMPTY\t| Srcs: " << stack.empty() << '\t' << "Copy: " << copy_stack.empty() << std::endl;
	std::cout << "TOP\t| Srcs: " << stack.top() << '\t' << "Copy: " << copy_stack.top() << std::endl;
	std::cout << "SIZE\t| Srcs: " << copy_stack.size() << '\t' << "Copy: " << copy_stack.size() << std::endl;
	std::cout << "EMPTY\t| Srcs: " << copy_stack.empty() << '\t' << "Copy: " << copy_stack.empty() << std::endl;
	std::cout << "TOP\t| Srcs: " << copy_stack.top() << '\t' << "Copy: " << copy_stack.top() << std::endl;
}
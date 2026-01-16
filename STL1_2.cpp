#include<iostream>
#include <set>

int main()
{
	int amount_el, num;
	std::set<int, std::greater<int>> numbers;

	std::cout << "Enter amount of elements: ";
	std::cin >> amount_el;
	std::cout << "[IN]: " << std::endl;

	for (int i = 0; i < amount_el; ++i)
	{
		std::cin >> num;
		numbers.insert(num);
	}

	std::cout << "[OUT]: " << std::endl;

	for (int n : numbers)
	{
		std::cout << n << std::endl;
	}
}
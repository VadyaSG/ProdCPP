#include<iostream>
#include <vector>
#include <list>
#include <set>
#include <string>

template<typename TContainer>
void print_container(const TContainer& container,const std::string& seporator)
{
	auto it = container.begin();
	if (it == container.end())
	{
		std::cout << "Container is empty" << std::endl;
		return;
	}
	std::cout << *it;
	++it;
	for (; it != container.end(); ++it)
	{
		std::cout << "," << *it;
	}
	std::cout << std::endl;
}

int main()
{
	std::set<std::string> test_set = { "one", "two", "three", "four" };
	std::cout << "set"<<std::endl;
	print_container(test_set, ",");

	std::list<std::string> test_list = { "one", "two", "three", "four" };
	std::cout << "list" << std::endl;
	print_container(test_list, ",");

	std::vector<std::string> test_vector = { "one", "two", "three", "four" };
	std::cout << "vector" << std::endl;
	print_container(test_vector, ",");
}
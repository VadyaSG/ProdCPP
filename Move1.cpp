#include <iostream>
#include <vector>
#include <string>

template<typename T>
void move_vectors(std::vector<T>& source, std::vector<T>& moved)
{
	moved = std::move(source);
}

int main()
{
	std::vector <std::string> one = { "test_string1", "test_string2" };
	std::vector <std::string> two;
	
	move_vectors(one, two);

	std::cout<<"Vector 'one': " << one.size() << std::endl;
	std::cout << "Vector 'two': ";

	for (const auto& str : two)
	{
		std::cout << str<<" ";
	}
}
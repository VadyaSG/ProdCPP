#include<iostream>
#include<vector>

template<typename T>
void sqr(T val)
{
	std::cout << "[IN]: " << val << std::endl;
	std::cout << "[OUT]: " << val * val << std::endl;	
}

template<typename T>
void sqr(std::vector<T> val)
{
	std::cout << "[IN]: ";

	for (size_t i=0;i<val.size();++i)
	{
		std::cout << val[i];
		if (i < val.size() - 1)
		{
			std::cout << ", ";
		}
	}

	std::cout << std::endl;
	std::cout << "[OUT]: ";

	for (size_t i = 0; i < val.size(); ++i)
	{
		std::cout << val[i]*val[i];
		if (i < val.size() - 1)
		{
			std::cout << ", ";
		}
	}
	std::cout << std::endl;
}

int main()
{
 std::vector<int> vector = { 2,3,4,5,6 };

 sqr(5);
 sqr(vector);
}
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
void del_duble(std::vector<T>& num)
{
	std::sort(num.begin(), num.end());

	auto s = std::unique(num.begin(), num.end());

	num.erase(s, num.end());
}

template <typename T>
void print_vector(std::vector<T>& nums)
{
	for (const auto& i : nums)
	{
		std::cout << i<<" ";
	}
	std::cout << std::endl;
}

int main()
{
	std::vector<int> nums = { 1,1,2,5,6,1,2,4 };

	std::cout << "[IN]: ";
	print_vector(nums);
	
	del_duble(nums);

	std::cout << "[OUT]: ";
	print_vector(nums);
}

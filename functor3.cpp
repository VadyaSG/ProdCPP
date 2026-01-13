#include<iostream>
#include<vector>
#include<algorithm>

class Functor
{
private:
	int sum = 0;
	int count = 0;
public:
	void operator()(int& num)
	{
		if (num % 3 == 0)
		{
			++count;
			sum += num;
		}
	}

	int get_sum()const { return sum; }
	int get_count()const { return count; }
};

void print_arr(const std::vector<int>& nums);

int main()
{
	std::vector<int> nums = { 4,1,3,6,25,54 };
	Functor counter;
	counter = std::for_each(nums.begin(), nums.end(), counter);
	print_arr(nums);

	std::cout << "[OUT]: " << "get_sum() = " << counter.get_sum() << std::endl;
	std::cout << "[OUT]: " << "get_count() = " << counter.get_count() << std::endl;
}

void print_arr(const std::vector<int>& nums)
{
	std::cout << "[IN]: ";
	for (int i = 0; i < nums.size(); ++i)
	{
		std::cout << nums[i] << " ";
	}
	std::cout << std::endl;
}

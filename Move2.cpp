#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

class Big_nums
{
private:
	std::vector<int> nums;
public:
	
	Big_nums(const std::string& num) 
	{
		for (char ch : num)
		{
			nums.push_back(ch-'0');
		}
		std::reverse(nums.begin(), nums.end());
	}

	Big_nums(const Big_nums& other) :nums(other.nums) {}
	Big_nums(Big_nums&& other) noexcept : nums(std::move(other.nums)) {}


	Big_nums& operator=(Big_nums&& other) noexcept
	{
		if (this != &other) { nums = std::move(other.nums); }
		return *this;
	}

	Big_nums operator+(const Big_nums& other)const 
	{
		Big_nums result("");
		int carry = 0;
		size_t max_size = std::max(this->nums.size(), other.nums.size());
		
		for (size_t i = 0; i < max_size || carry; ++i)
		{
			int digit1 = (i < this->nums.size()) ? this->nums[i] : 0;
			int digit2 = (i < other.nums.size()) ? other.nums[i] : 0;

			int sum = digit1 + digit2 + carry;
			result.nums.push_back(sum % 10);
			carry = sum / 10;	
		}
		while (result.nums.size() > 1 && result.nums.back() == 0) { result.nums.pop_back(); }
		return result;
	}

	Big_nums operator*(int num)const
	{
		if (num == 0) { return Big_nums("0"); }
		if (num == 1) { return *this; }
		if (num < 0) { return Big_nums("in development"); }

		Big_nums result("");
		int carry = 0;

		for (int digit : this->nums)
		{
			long long mult = (long long)digit * num + carry;
			result.nums.push_back(mult % 10);
			carry = mult / 10;
		}
		while (carry > 0)
		{
			result.nums.push_back(carry % 10);
			carry /= 10;
		}
		while (result.nums.size() > 1 && result.nums.back() == 0) { result.nums.pop_back(); }
		return result;
	}

	std::string to_string()const
	{
		if (nums.empty()) { return "0"; }

		std::string result;
		std::vector<int> temp_nums = nums;
		std::reverse(temp_nums.begin(), temp_nums.end());

		for (int num : temp_nums)
		{
			result += std::to_string(num) ;
		}

		if (result.empty()) { return "0"; }

		return result;
	}

	friend std::ostream& operator<<(std::ostream& os, const Big_nums& num)
	{
		os << num.to_string();
		return os;
	}
};

int main()
{
	auto number1 = Big_nums("114575");
	auto number2 = Big_nums("78524");
	auto result = number1 + number2;
	std::cout << result; // 193099
}
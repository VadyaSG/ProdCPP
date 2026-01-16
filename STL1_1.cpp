#include<iostream>
#include<string>
#include <map>
#include<vector>
#include<algorithm>

int main()
{
	std::string text;
	std::map<char, int> counts_of_sym;
	std::vector<std::pair<char, int>> sorted_sym;

	std::cout << "[IN]: ";
	std::getline(std::cin, text);

	for (char sym: text)
	{
			counts_of_sym[sym]++;
	}

	for (const auto& pair : counts_of_sym)
	{
		sorted_sym.push_back(pair);
	}

	std::sort(sorted_sym.begin(), sorted_sym.end(), [](const std::pair<char, int>& a, const std::pair<char, int>& b)
		{
			if (a.second != b.second)
			{
				return a.second > b.second;
			}
			return a.first < b.first;
		});

	std::cout << "[OUT]: " << std::endl;
	for (const auto& pair : sorted_sym)
	{
		std::cout << pair.first << ": " << pair.second << std::endl;
	}
}
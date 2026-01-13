#include<iostream>
#include<vector>

template<typename T>
class Table
{
private:
	size_t rows, columns;
	std::vector<std::vector<T>>vector;
public:
	Table(size_t r, size_t c):rows(r),columns(c) 
	{
		vector.resize(rows, std::vector<T>(columns));
	}

	std::vector<T>& operator[](size_t row_ix) { return vector[row_ix]; }
	const std::vector<T>& operator[](size_t row_ix)const { return vector[row_ix]; }
	size_t size()const { return rows * columns; }
};

int main()
{
	auto test = Table<int>(2, 3);
	test[0][0] = 4;
	std::cout << test[0][0]<<std::endl;
	std::cout << "size: " << test.size();
}
#include<iostream>
#include<stdexcept>

class Smart_array
{
private:
	int* arr;
	int size;
	int index;
public:
	Smart_array(int nsize) :size(nsize), index(0)
	{
		if (size < 0)
		{
			throw std::invalid_argument("размер массива должен быть положительным");
		}
		arr = new int[size];
	}
	void add_element(int num)
	{
		if (index >= size)
		{
			throw std::out_of_range("Массив переполнен");
		}
		arr[index++] = num;
	}
	int get_element(int index)
	{
		if (index < 0 || index >= size)
		{
			throw std::out_of_range("индекс выходит за пределы массива");
		}
		return arr[index];
	}
	~Smart_array()
	{
		delete[] arr;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");

	try {
		Smart_array arr(5);
		arr.add_element(1);
		arr.add_element(4);
		arr.add_element(155);
		arr.add_element(14);
		arr.add_element(15);
		std::cout << arr.get_element(3) << std::endl;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}

	return 0;
}
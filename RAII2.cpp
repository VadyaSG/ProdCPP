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
	Smart_array(const Smart_array& other) :index(other.index), size(other.size)
	{
		arr = new int[size];

		for (int i{ 0 }; i < other.size; ++i)
		{
			arr[i] = other.arr[i];
		}
	}
	Smart_array& operator=(const Smart_array& other)
	{
		if (this != &other)
		{
			int* new_arr = new int[other.size];
			for (int i{ 0 }; i < index; ++i)
			{
				arr[i] = other.arr[i];
			}
			delete[] arr;
			index = other.index;
			size = other.size;
			arr = new int[size];
		}
		return *this;
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
	
		Smart_array arr(5);
		arr.add_element(1);
		arr.add_element(4);
		arr.add_element(155);

		Smart_array new_array(2);
		new_array.add_element(44);
		new_array.add_element(34);
	
		arr = new_array;
	return 0;
}
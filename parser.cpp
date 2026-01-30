#include<iostream>
#include<map>
#include<string>
#include <fstream>
#include<algorithm>

//--------------------------------------------------------------------------------------------------------------------------
std::string trim(const std::string& str)
{
	size_t first = str.find_first_not_of(" \t");
	if (std::string::npos == first)
	{
		return str;
	}
	size_t last = str.find_last_not_of(" \t");
	return str.substr(first, (last - first + 1));
}
//--------------------------------------------------------------------------------------------------------------------------
class Ini_parser
{
private:
	std::ifstream file;
	std::map<std::string, std::map<std::string, std::string>> data;
	std::string current_section;

	template<typename T>
	T convert_value(const std::string& str_value)const;
	//--------------------------------------------------------------------------------------------------------------------------
	bool is_comment(const std::string& line)const
	{
		std::string trimmed_line = trim(line);
		return !trimmed_line.empty() && trimmed_line[0] == ';';
	}
	//--------------------------------------------------------------------------------------------------------------------------
	bool parse_section(const std::string& line)
	{
		if (line.length() >= 2 && line[0] == '[' && line.back() == ']')
		{
			current_section = trim(line.substr(1, line.length() - 2));
			data[current_section];
			return true;
		}
		return false;
	}
	//--------------------------------------------------------------------------------------------------------------------------
	bool parse_variable(const std::string& line)
	{
		size_t eq_pos = line.find('=');
		if (eq_pos != std::string::npos)
		{
			if (current_section.empty())
			{
				return false;
			}

			std::string var_name = trim(line.substr(0, eq_pos));
			std::string var_value = trim(line.substr(eq_pos + 1));

			size_t comment_start = var_value.find(';');
			if (comment_start != std::string::npos)
			{
				var_value = trim(var_value.substr(0, comment_start));
			}
			if (!var_name.empty())
			{
				data[current_section][var_name] = var_value;
				return true;
			}
		}
		return false;
	}
	//--------------------------------------------------------------------------------------------------------------------------
	void process_line(const std::string& raw_line)
	{
		std::string line = trim(raw_line);
		if(line.empty()||is_comment(line)){return;}
		if (parse_section(line)) { return; }
		if (parse_variable(line)) { return; }
	}
	//--------------------------------------------------------------------------------------------------------------------------
	void parse_file()
	{
		std::string line;
		while (std::getline(file, line))
		{
			process_line(line);
		}
	}
	//--------------------------------------------------------------------------------------------------------------------------
public:
	Ini_parser(const std::string& file_name)
	{
		
		file.open(file_name);
		if (!file.is_open())
		{
			throw std::runtime_error("can''t open a file: " + file_name);
		}
		parse_file();
		file.close();
	}
	//--------------------------------------------------------------------------------------------------------------------------
	template<typename T>
	T get_value(const std::string& path)const
	{
		size_t dot_pos = path.find('.');
		if (dot_pos == std::string::npos)
		{
			throw std::runtime_error("incorrect path format: " + path + "the expected format was 'section.variable");
		}
		std::string section_name = path.substr(0, dot_pos);
		std::string var_name = path.substr(dot_pos + 1);

		auto section_it = data.find(section_name);
		if (section_it == data.end())
		{
			throw std::runtime_error("section " + section_name + " not found");
		}

		auto var_it = section_it->second.find(var_name);
		if (var_it == section_it->second.end())
		{
			throw std::runtime_error("Variable" + var_name + "not found in section" + section_name);
		}
		return convert_value<T>(var_it->second);
	}
};
//--------------------------------------------------------------------------------------------------------------------------
template<>
int Ini_parser::convert_value<int>(const std::string& str_value)const
{
	try
	{
		return std::stoi(str_value);
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error("Error converting the value" + str_value + "in int:" + e.what());
	}
}
//--------------------------------------------------------------------------------------------------------------------------
template<>
double Ini_parser::convert_value<double>(const std::string& str_value)const
{
	try
	{
		return std::stod(str_value);
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error("Error converting the value" + str_value + "in int:" + e.what());
	}
}
//--------------------------------------------------------------------------------------------------------------------------
template <>
std::string Ini_parser::convert_value<std::string>(const std::string& str_value) const { return str_value; }
//--------------------------------------------------------------------------------------------------------------------------

int main()
{
	std::ofstream test_ini("test.ini");
	if (test_ini.is_open()) {
		test_ini << "[Section1]\n";
		test_ini << "var1=5\n";
		test_ini << "var2=hello world ; comment for param\n";
		test_ini << "var3=3.14\n";
		test_ini << "\n";

		test_ini << "[ Section2 ]\n"; 
		test_ini << "varA=100\n";
		test_ini << "varB = Another string\n"; 
		test_ini << "\n";
		test_ini << "; general comment\n";

		test_ini << "[Section3]\n";
		test_ini << "Mode=\n";
		test_ini << "Value=some_value\n";
		test_ini << "[Section1]\n";
		test_ini << "var1=10\n";
		test_ini.close();

		std::cout << "created test.ini\n" << std::endl;
	}
	else {
		std::cerr << "failed to create test.ini" << std::endl;
		return 1;
	}


	try 
	{
		Ini_parser parser("test.ini");

		int val1 = parser.get_value<int>("Section1.var1");
		std::cout << "Section1.var1 (int): " << val1 << std::endl; 

		std::string val2 = parser.get_value<std::string>("Section1.var2");
		std::cout << "Section1.var2 (string): " << val2 << std::endl;

		double val3 = parser.get_value<double>("Section1.var3");
		std::cout << "Section1.var3 (double): " << val3 << std::endl;

		int valA = parser.get_value<int>("Section2.varA");
		std::cout << "Section2.varA (int): " << valA << std::endl;

		std::string valB = parser.get_value<std::string>("Section2.varB");
		std::cout << "Section2.varB (string): " << valB << std::endl;

		std::string empty_val = parser.get_value<std::string>("Section3.Mode");
		std::cout << "Section3.Mode (string, empty): '" << empty_val << "'" << std::endl; 

		try 
		{
			int non_existent_val = parser.get_value<int>("Section1.non_existent_var");
			std::cout << "It should not be deduced: " << non_existent_val << std::endl;
		}
		catch (const std::runtime_error& e) 
		{
			std::cerr << "Error(variable is not found): " << e.what() << std::endl;
		}

		try 
		{
			int wrong_type_val = parser.get_value<int>("Section1.var2");
			std::cout << "It should not be deduced: " << wrong_type_val << std::endl;
		}
		catch (const std::runtime_error& e) 
		{
			std::cerr << "Error(incorrect type): " << e.what() << std::endl;
		}

		try 
		{
			std::string non_existent_section = parser.get_value<std::string>("NonExistentSection.some_var");
			std::cout << "It should not be deduced: " << non_existent_section << std::endl;
		}
		catch (const std::runtime_error& e) 
		{
			std::cerr << "Error (section not found): " << e.what() << std::endl;
		}

	}
	catch (const std::runtime_error& e)
	{
		std::cerr << "parser error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}
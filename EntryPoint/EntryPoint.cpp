#include <iostream>
#include <sstream>

#include "../ToeLibrary/matrix.h"
#include "../ToeLibrary/circuit.h"
#include "../ToeLibrary/csv_reader.h"
#include "../ToeLibrary/branches_data.h"

std::vector<std::string> ReadData(const std::string& path);

int main()
{
	
	auto result = ReadData("../circuit_dc_data/circuit_data_1.csv");

	toe::branches_data data;
	
	for(auto& item : result)
	{
		std::stringstream ss(item);
		ss >> data;
	}

	
	setlocale(LC_ALL, "ru");
	std::cout.precision(3);
	std::cout.setf(std::ios::fixed);

	toe::circuit circuit(std::move(data));

	toe::matrix IR = circuit.calculate();
	
	std::cout << "Токи в сопротивлениях ветвей, А\n";
	std::cout << IR.get_transposed() << std::endl;

	return 0;
}

std::vector<std::string> ReadData(const std::string& path)
{
	toe::csv_reader reader(path);
	return reader.Read();
}
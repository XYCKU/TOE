﻿#include <iostream>
#include <sstream>

#include "../ToeLibrary/Matrix.h"
#include "../ToeLibrary/Circuit.h"
#include "../ToeLibrary/CsvReader.h"
#include "../ToeLibrary/BranchesData.h"

std::vector<std::string> ReadData(const std::string& path);

int main()
{
	setlocale(LC_ALL, "ru");
	std::cout.precision(3);
	std::cout.setf(std::ios::fixed);

	auto result = ReadData("../circuit_dc_data/circuit_data_1.csv");

	toe::BranchesData data;
	
	for(auto& item : result)
	{
		std::stringstream ss(item);
		ss >> data;
	}
	
	toe::Circuit circuit(std::move(data));

	toe::Matrix IR = circuit.Calculate();

	std::cout << "Токи в сопротивлениях ветвей, А\n";
	std::cout << IR.GetTransposedMatrix() << std::endl;

	return 0;
}

std::vector<std::string> ReadData(const std::string& path)
{
	toe::CsvReader reader(path);
	return reader.Read();
}
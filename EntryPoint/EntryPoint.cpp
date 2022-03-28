#include <chrono>
#include <iostream>
#include <random>
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

	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<int> dist{ 1, 3 };

	auto begin = std::chrono::steady_clock::now();

	std::string fileNumber = std::to_string(dist(eng));
	std::cout << fileNumber << "\n";

	auto result = ReadData("../circuit_dc_data/circuit_data_" + fileNumber + ".csv");

	toe::BranchesData data;
	
	for(auto& item : result)
	{
		std::stringstream ss(item);
		ss >> data;
	}
	
	toe::Circuit circuit(std::move(data));

	toe::Matrix IR{ circuit.Calculate() };

	std::cout << "Токи в сопротивлениях ветвей, А\n";
	std::cout << IR.GetTransposedMatrix() << std::endl;

	auto end = std::chrono::steady_clock::now();

	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

	return 0;
}

std::vector<std::string> ReadData(const std::string& path)
{
	toe::CsvReader reader(path);
	return reader.Read();
}
#include <chrono>
#include <iostream>
#include <string>
#include <random>
#include <sstream>

#include "../ToeLibrary/Matrix.h"
#include "../ToeLibrary/Circuit.h"
#include "../ToeLibrary/CsvReader.h"
#include "../ToeLibrary/BranchesData.h"
#include "../ToeLibrary/PotentialCircuitSolver.h"

std::vector<std::string> ReadData(const std::string& path);

template <typename T>
T aga(const std::vector<T>& a)
{
	return a.front();
}

int main()
{
	setlocale(LC_ALL, "ru");
	std::cout.precision(3);
	std::cout.setf(std::ios::fixed);

	auto begin = std::chrono::steady_clock::now();

	auto result = ReadData("../circuit_dc_data/circuit_data_1.csv");

	using matrix_type = double;
	toe::BranchesData<matrix_type> data;

	for(auto& item : result)
	{
		std::stringstream ss(item);
		ss >> data;
	}

	aga(data._branchNumber);
	
	toe::Circuit circuit(std::move(data));
	auto solver = toe::PotentialCircuitSolver<matrix_type>();

	toe::Matrix IR{ solver.Solve(circuit) };

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
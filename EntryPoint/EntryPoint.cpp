#include <iostream>
#include "../ToeLibrary/matrix.h"
#include "../ToeLibrary/circuit.h"
#include "../ToeLibrary/csv_reader.h"

using namespace std;
using namespace toe;

int main()
{
	csv_reader reader("../circuit_dc_data/circuit_data_1.csv");
	auto result = reader.Read();

	for (auto& str : result)
	{
		std::cout << str << '\n';
	}

	return 0;
}

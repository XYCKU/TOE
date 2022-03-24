#include "csv_reader.h"

#include <algorithm>
#include <sstream>

namespace toe
{
	csv_reader::csv_reader(const std::string& path, char delimiter)
		: file_reader(path), _delimiter(delimiter) { }


	std::vector<std::string> csv_reader::Read()
	{
		std::vector<std::string> result;

		std::string line;
		std::size_t lineIndex = 0;
		while (std::getline(_in, line))
		{
			std::replace(line.begin(), line.end(), _delimiter, ' ');
			result.emplace_back(line);
			++lineIndex;
		}

		return result;
	}
}

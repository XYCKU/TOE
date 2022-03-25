#include "CsvReader.h"

#include <algorithm>
#include <sstream>

namespace toe
{
	CsvReader::CsvReader(const std::string& path, char delimiter)
		: FileReader(path), _delimiter(delimiter) { }


	std::vector<std::string> CsvReader::Read()
	{
		std::vector<std::string> result;

		std::string line;
		std::size_t lineIndex = 0;
		while (std::getline(_in, line))
		{
			std::ranges::replace(line, _delimiter, ' ');
			result.emplace_back(line);
			++lineIndex;
		}

		return result;
	}
}

#pragma once
#include "FileReader.h"

namespace toe
{
	class CsvReader :
		public FileReader
	{
	private:
		char _delimiter = ',';
	public:
		explicit CsvReader(const std::string& path, char delimiter = ',');
		~CsvReader() override = default;
		std::vector<std::string> Read() override;
	};
}
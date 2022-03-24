#pragma once
#include "file_reader.h"

namespace toe
{
	class csv_reader :
		public file_reader
	{
	private:
		char _delimiter = ',';
	public:
		explicit csv_reader(const std::string& path, char delimiter = ',');
		~csv_reader() override = default;
		std::vector<std::string> Read() override;
	};
}


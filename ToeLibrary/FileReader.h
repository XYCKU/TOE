#pragma once
#include <fstream>
#include <vector>
#include <string>

namespace toe
{
	class FileReader
	{
	protected:
		std::ifstream _in;
	public:
		explicit FileReader(const std::string& path) : _in(path) { }
		virtual std::vector<std::string> Read() = 0;
		virtual ~FileReader() = default;
	};
}
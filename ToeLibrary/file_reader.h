#pragma once
#include <fstream>
#include <vector>
#include <string>

namespace toe
{
	class file_reader
	{
	protected:
		std::ifstream _in;
	public:
		explicit file_reader(const std::string& path) : _in(path) { }
		virtual std::vector<std::string> Read() = 0;
		virtual ~file_reader() = default;
	};
}


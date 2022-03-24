#pragma once
#include <istream>
#include <vector>

namespace toe
{
	struct branch
	{
		static constexpr std::size_t argumentsAmount = 6;
		std::size_t _branchNumber;
		std::size_t _branchBegin;
		std::size_t _branchEnd;
		double _resistorValue;
		double _voltageValue;
		double _amperageValue;

		branch(std::size_t branchNumber, std::size_t branchBegin, std::size_t branchEnd, double resistorValue, double voltageValue, double amperageValue);
		friend std::istream& operator>>(std::istream& in, branch& item);
	};
}


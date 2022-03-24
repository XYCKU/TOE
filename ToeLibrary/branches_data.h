#pragma once
#include <istream>
#include <vector>

namespace toe
{
	struct branches_data
	{
		static constexpr std::size_t argumentsAmount = 6;
		std::size_t _nodesAmount = 0;
		std::vector<std::size_t> _branchNumber;
		std::vector<std::size_t> _branchBegin;
		std::vector<std::size_t> _branchEnd;
		std::vector<double> _resistorValue;
		std::vector<double> _voltageValue;
		std::vector<double> _amperageValue;

		branches_data() = default;
		branches_data(const branches_data& other) = default;
		branches_data(branches_data&& other) noexcept = default;
		branches_data(std::vector<std::size_t>&& branchesNumber, std::vector<std::size_t>&& branchesBegin, std::vector<std::size_t>&& branchesEnd,
					std::vector<double>&& resistorValues, std::vector<double>&& voltageValues, std::vector<double>&& amperageValues);
		branches_data(const std::vector<std::size_t>& branchesNumber, const std::vector<std::size_t>& branchesBegin,
									const std::vector<std::size_t>& branchesEnd, const std::vector<double>& resistorValues,
									const std::vector<double>& voltageValues, const std::vector<double>& amperageValues);
		~branches_data() = default;

		void resize(std::size_t newSize);
		friend std::istream& operator>>(std::istream& in, branches_data& item);
	};
}


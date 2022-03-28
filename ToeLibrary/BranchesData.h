#pragma once
#include <istream>
#include <vector>

namespace toe
{
	struct BranchesData
	{
		static constexpr std::size_t argumentsAmount = 6;
		std::size_t _nodesAmount = 0;
		std::vector<std::size_t> _branchNumber;
		std::vector<std::size_t> _branchBegin;
		std::vector<std::size_t> _branchEnd;
		std::vector<double> _resistorValues;
		std::vector<double> _voltageValues;
		std::vector<double> _amperageValues;

		BranchesData() = default;
		BranchesData(const BranchesData& other) = default;
		BranchesData(BranchesData&& other) noexcept = default;
		BranchesData(std::vector<std::size_t>&& branchesNumber, std::vector<std::size_t>&& branchesBegin, std::vector<std::size_t>&& branchesEnd,
					std::vector<double>&& resistorValues, std::vector<double>&& voltageValues, std::vector<double>&& amperageValues);
		BranchesData(const std::vector<std::size_t>& branchesNumber, const std::vector<std::size_t>& branchesBegin,
									const std::vector<std::size_t>& branchesEnd, const std::vector<double>& resistorValues,
									const std::vector<double>& voltageValues, const std::vector<double>& amperageValues);
		~BranchesData() = default;

		void Resize(std::size_t newSize);
		friend std::istream& operator>>(std::istream& in, BranchesData& item);
	};
}


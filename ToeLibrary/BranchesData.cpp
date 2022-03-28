#include "BranchesData.h"

namespace toe
{
	BranchesData::BranchesData(std::vector<std::size_t>&& branchesNumber, std::vector<std::size_t>&& branchesBegin,
		std::vector<std::size_t>&& branchesEnd, std::vector<double>&& resistorValues,
		std::vector<double>&& voltageValues, std::vector<double>&& amperageValues)
			: _branchNumber(std::move(branchesNumber))
			, _branchBegin(std::move(branchesBegin))
			, _branchEnd(std::move(branchesEnd))
			, _resistorValues(std::move(resistorValues))
			, _voltageValues(std::move(voltageValues))
			, _amperageValues(std::move(amperageValues)) { }

	BranchesData::BranchesData(const std::vector<std::size_t>& branchesNumber, const std::vector<std::size_t>& branchesBegin,
		const std::vector<std::size_t>& branchesEnd, const std::vector<double>& resistorValues,
		const std::vector<double>& voltageValues, const std::vector<double>& amperageValues)
		: _branchNumber(branchesNumber)
		, _branchBegin(branchesBegin)
		, _branchEnd(branchesEnd)
		, _resistorValues(resistorValues)
		, _voltageValues(voltageValues)
		, _amperageValues(amperageValues) { }

	void BranchesData::Resize(std::size_t newSize)
	{
		_branchNumber.resize(newSize);
		_branchBegin.resize(newSize);
		_branchEnd.resize(newSize);
		_resistorValues.resize(newSize);
		_voltageValues.resize(newSize);
		_amperageValues.resize(newSize);
	}

	std::istream& operator>>(std::istream& in, BranchesData& item)
	{
		std::size_t branchNumber;
		std::size_t branchBegin;
		std::size_t branchEnd;
		double resistorValue;
		double voltageValue;
		double amperageValue;

		in >> branchNumber >> branchBegin >> branchEnd >> resistorValue >> voltageValue >> amperageValue;

		item._nodesAmount = std::max(item._nodesAmount, branchBegin);
		item._nodesAmount = std::max(item._nodesAmount, branchEnd);

		item._branchNumber.emplace_back(branchNumber);
		item._branchBegin.emplace_back(branchBegin - 1);
		item._branchEnd.emplace_back(branchEnd - 1);
		item._resistorValues.emplace_back(resistorValue);
		item._voltageValues.emplace_back(voltageValue);
		item._amperageValues.emplace_back(amperageValue);

		return in;
	}
}

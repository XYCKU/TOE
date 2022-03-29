#include "BranchesData.h"
#include <iostream>

namespace toe
{
	template <typename T>
	BranchesData<T>::BranchesData(std::vector<std::size_t>&& branchesNumber, std::vector<std::size_t>&& branchesBegin,
		std::vector<std::size_t>&& branchesEnd, std::vector<T>&& resistorValues,
		std::vector<T>&& voltageValues, std::vector<T>&& amperageValues)
			: _branchNumber(std::move(branchesNumber))
			, _branchBegin(std::move(branchesBegin))
			, _branchEnd(std::move(branchesEnd))
			, _resistorValues(std::move(resistorValues))
			, _voltageValues(std::move(voltageValues))
			, _amperageValues(std::move(amperageValues)) { }

	template <typename T>
	BranchesData<T>::BranchesData(const std::vector<std::size_t>& branchesNumber, const std::vector<std::size_t>& branchesBegin,
		const std::vector<std::size_t>& branchesEnd, const std::vector<T>& resistorValues,
		const std::vector<T>& voltageValues, const std::vector<T>& amperageValues)
		: _branchNumber(branchesNumber)
		, _branchBegin(branchesBegin)
		, _branchEnd(branchesEnd)
		, _resistorValues(resistorValues)
		, _voltageValues(voltageValues)
		, _amperageValues(amperageValues) { }

	template <typename T>
	void BranchesData<T>::Resize(std::size_t newSize)
	{
		_branchNumber.resize(newSize);
		_branchBegin.resize(newSize);
		_branchEnd.resize(newSize);
		_resistorValues.resize(newSize);
		_voltageValues.resize(newSize);
		_amperageValues.resize(newSize);
	}
}

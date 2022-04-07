#pragma once
#include <iostream>
#include <vector>

namespace toe
{
	template <typename T>
	concept Readable = requires(std::istream& is, T item)
	{
		is << item;
	};

	template <typename T>
	struct BranchesData
	{
		static constexpr std::size_t argumentsAmount = 6;
		std::size_t _nodesAmount = 0;
		std::vector<std::size_t> _branchNumber;
		std::vector<std::size_t> _branchBegin;
		std::vector<std::size_t> _branchEnd;
		std::vector<T> _resistorValues;
		std::vector<T> _voltageValues;
		std::vector<T> _amperageValues;

		BranchesData() = default;
		BranchesData(const BranchesData<T>& other) = default;
		BranchesData(BranchesData<T>&& other) noexcept = default;
		BranchesData(std::vector<std::size_t>&& branchesNumber, std::vector<std::size_t>&& branchesBegin, std::vector<std::size_t>&& branchesEnd,
					std::vector<T>&& resistorValues, std::vector<T>&& voltageValues, std::vector<T>&& amperageValues);
		BranchesData(const std::vector<std::size_t>& branchesNumber, const std::vector<std::size_t>& branchesBegin,
									const std::vector<std::size_t>& branchesEnd, const std::vector<T>& resistorValues,
									const std::vector<T>& voltageValues, const std::vector<T>& amperageValues);
		~BranchesData() = default;

		void Resize(std::size_t newSize);

		friend std::istream& operator>>(std::istream& in, BranchesData<T>& item)
		{
			std::size_t branchNumber;
			std::size_t branchBegin;
			std::size_t branchEnd;
			T resistorValue;
			T voltageValue;
			T amperageValue;

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
	};

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


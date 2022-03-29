// файл "toe.h"
// в данном файле описан класс Circuit для работы с графом электрической цепи

#pragma once

#include <iosfwd>
#include <string>
#include <vector>

#include "Matrix.h"
#include "BranchesData.h"

namespace toe
{
	template <typename T>
	class Circuit
	{
		BranchesData<T> _data;
	public:
		Circuit(const Circuit<T>& other) = default;
		Circuit(Circuit<T>&& other) noexcept = default;
		explicit Circuit(BranchesData<T>&& branches)
			: _data(std::move(branches)) { }
		~Circuit() = default;
		
		[[nodiscard]] const std::vector<T>& GetResistorValues() const
		{
			return _data._resistorValues;
		}

		[[nodiscard]] const std::vector<T>& GetVoltageValues() const
		{
			return _data._voltageValues;
		}

		[[nodiscard]] const std::vector<T>& GetAmperageValues() const
		{
			return _data._amperageValues;
		}

		[[nodiscard]] Matrix<T> GetNodesMatrix() const
		{
			std::vector<std::vector<T>> nodesMatrix(_data._nodesAmount - 1, std::vector<T>(_data._branchNumber.size()));

			for (std::size_t i = 0; i < nodesMatrix.size(); ++i)
			{
				for (std::size_t j = 0; j < nodesMatrix.front().size(); ++j)
				{
					if (_data._branchBegin[j] == i)
					{
						nodesMatrix[i][j] = 1;
					}
					else if (_data._branchEnd[j] == i)
					{
						nodesMatrix[i][j] = -1;
					}
				}
			}

			return Matrix{ nodesMatrix };
		}
	};
}

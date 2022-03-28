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
	class Circuit
	{
		BranchesData _data;
	public:
		Circuit(const Circuit& other) = default;
		Circuit(Circuit&& other) noexcept = default;
		explicit Circuit(BranchesData&& branches);
		~Circuit() = default;
		
		[[nodiscard]] const std::vector<double>& GetResistorValues() const;
		[[nodiscard]] const std::vector<double>& GetVoltageValues() const;
		[[nodiscard]] const std::vector<double>& GetAmperageValues() const;
		[[nodiscard]] Matrix GetNodesMatrix() const;
		[[nodiscard]] Matrix Calculate() const;
	};
}

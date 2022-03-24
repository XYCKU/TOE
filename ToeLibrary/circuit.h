// файл "toe.h"
// в данном файле описан класс circuit для работы с графом электрической цепи

#pragma once

#include <iosfwd>
#include <string>
#include <vector>

#include "matrix.h"
#include "branches_data.h"

namespace toe
{
	class circuit
	{
		branches_data _data;
	public:
		circuit(const circuit& other) = default;
		circuit(circuit&& other) noexcept = default;
		explicit circuit(branches_data&& branches);
		~circuit() = default;

		[[nodiscard]] matrix get_nodes() const;
		[[nodiscard]] matrix calculate() const;
	};
}

// ���� "toe.h"
// � ������ ����� ������ ����� Circuit ��� ������ � ������ ������������� ����

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
		
		[[]]
		[[nodiscard]] Matrix GetNodesMatrix() const;
		[[nodiscard]] Matrix Calculate() const;
	};
}

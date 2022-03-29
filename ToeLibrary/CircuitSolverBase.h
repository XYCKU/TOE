#pragma once

#include "Circuit.h"

namespace toe
{
	template <typename T>
	class CircuitSolverBase
	{
	public:
		CircuitSolverBase() = default;
		virtual ~CircuitSolverBase() = default;
		virtual Matrix<T> Solve(const Circuit<T>& circuit) = 0;
	};
}


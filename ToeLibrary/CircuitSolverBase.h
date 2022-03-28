#pragma once

#include "Circuit.h"

namespace toe
{
	class CircuitSolverBase
	{
	public:
		CircuitSolverBase() = default;
		virtual ~CircuitSolverBase() = default;
		virtual Matrix Solve(const Circuit& circuit) = 0;
	};
}


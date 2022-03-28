#pragma once

#include "CircuitSolverBase.h"

namespace toe
{
	class PotentialCircuitSolver :
		public CircuitSolverBase
	{
	public:
		PotentialCircuitSolver() = default;
		~PotentialCircuitSolver() override = default;
		Matrix Solve(const Circuit& circuit) override;
	};
}


#pragma once

#include "CircuitSolverBase.h"

namespace toe
{
	template <typename T>
	class PotentialCircuitSolver :
		public CircuitSolverBase<T>
	{
	public:
		PotentialCircuitSolver() = default;
		~PotentialCircuitSolver() override = default;
		Matrix<T> Solve(const Circuit<T>& circuit) override;
	};

	template <typename T>
	Matrix<T> PotentialCircuitSolver<T>::Solve(const Circuit<T>& circuit)
	{
		Matrix<T> resistorMatrix(circuit.GetResistorValues());
		Matrix<T> voltageMatrix(circuit.GetVoltageValues());
		Matrix<T> amperageMatrix(circuit.GetAmperageValues());

		Matrix<T> resistorDiagonalMatrix = resistorMatrix.GetDiagonalMatrix();

		Matrix<T> circuitGraph = circuit.GetNodesMatrix();
		Matrix<T> transposedCircuitGraph = circuitGraph.GetTransposedMatrix();

		Matrix<T> conductivityMatrix = resistorDiagonalMatrix.GetInverseMatrix();

		// вычисляем потенциалы всех узлов цепи по отношению к базисному узлу
		Matrix<T> potentialMatrix = (circuitGraph * conductivityMatrix * transposedCircuitGraph).GetInverseMatrix()
			* (-circuitGraph * conductivityMatrix * voltageMatrix - circuitGraph * amperageMatrix);

		// вычисляем напряжение на всех ветвях цепи
		Matrix<T> u_matrix = transposedCircuitGraph * potentialMatrix;

		// вычисляем токи в сопротивлениях ветвей
		Matrix<T> resultMatrix = conductivityMatrix * (u_matrix + voltageMatrix);

		return resultMatrix;
	}
}


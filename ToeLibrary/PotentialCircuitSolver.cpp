#include "PotentialCircuitSolver.h"

namespace toe
{
	Matrix PotentialCircuitSolver::Solve(const Circuit& circuit)
	{
		Matrix resistorMatrix(circuit.GetResistorValues());
		Matrix voltageMatrix(circuit.GetVoltageValues());
		Matrix amperageMatrix(circuit.GetAmperageValues());

		Matrix resistorDiagonalMatrix = resistorMatrix.GetDiagonalMatrix();

		Matrix circuitGraph = circuit.GetNodesMatrix();
		Matrix transposedCircuitGraph = circuitGraph.GetTransposedMatrix();

		Matrix conductivityMatrix = resistorDiagonalMatrix.GetInverseMatrix();

		// вычисляем потенциалы всех узлов цепи по отношению к базисному узлу
		Matrix potentialMatrix = (circuitGraph * conductivityMatrix * transposedCircuitGraph).GetInverseMatrix()
			* (-circuitGraph * conductivityMatrix * voltageMatrix - circuitGraph * amperageMatrix);

		// вычисляем напряжение на всех ветвях цепи
		Matrix u_matrix = transposedCircuitGraph * potentialMatrix;

		// вычисляем токи в сопротивлениях ветвей
		Matrix resultMatrix = conductivityMatrix * (u_matrix + voltageMatrix);

		return resultMatrix;
	}
}

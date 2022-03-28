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

		// ��������� ���������� ���� ����� ���� �� ��������� � ��������� ����
		Matrix potentialMatrix = (circuitGraph * conductivityMatrix * transposedCircuitGraph).GetInverseMatrix()
			* (-circuitGraph * conductivityMatrix * voltageMatrix - circuitGraph * amperageMatrix);

		// ��������� ���������� �� ���� ������ ����
		Matrix u_matrix = transposedCircuitGraph * potentialMatrix;

		// ��������� ���� � �������������� ������
		Matrix resultMatrix = conductivityMatrix * (u_matrix + voltageMatrix);

		return resultMatrix;
	}
}

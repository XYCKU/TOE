#include "Circuit.h"
#include <iostream>
#include <fstream>
#include <vector>

namespace toe
{
	Circuit::Circuit(BranchesData&& branches)
		: _data(std::move(branches)) { }

	// ������� �������������� ������� ������� �� ����� �������� ����
	Matrix Circuit::GetNodesMatrix() const
	{
		std::vector<std::vector<double>> nodesMatrix(_data._nodesAmount - 1, std::vector<double>(_data._branchNumber.size()));

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

	// ������� ������� ������������� ���� ������� ������� �����������
	Matrix Circuit::Calculate() const
	{
		Matrix resistorMatrix(_data._resistorValue);
		Matrix voltageMatrix(_data._voltageValue);
		Matrix amperageMatrix(_data._amperageValue);

		Matrix resistorDiagonalMatrix = resistorMatrix.GetDiagonalMatrix();

		Matrix circuitGraph = this->GetNodesMatrix();
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
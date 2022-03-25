#include "Circuit.h"
#include <iostream>
#include <fstream>
#include <vector>

namespace toe
{
	Circuit::Circuit(BranchesData&& branches)
		: _data(std::move(branches)) { }

	// ������� �������������� ������� ������� �� ����� �������� ����
	Matrix Circuit::GetNodes() const
	{
		std::vector<std::vector<double>> nodesMatrix(_data._nodesAmount - 1, std::vector<double>(_data._branchNumber.size(), 0));

		for (std::size_t i = 0; i < nodesMatrix.size(); ++i)
		{
			for (std::size_t j = 0; j < nodesMatrix[0].size(); ++j)
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
		Matrix resistorMatrix{ _data._resistorValue };
		Matrix voltageMatrix{ _data._voltageValue };
		Matrix amperageMatrix{ _data._amperageValue };
		
		Matrix resistorDiagonalMatrix = resistorMatrix.GetTransposed().GetDiagonalMatrix();

		Matrix circuitGraph = GetNodes();

		Matrix conductivityMatrix = resistorDiagonalMatrix.GetInverse();

		// ��������� ���������� ���� ����� ���� �� ��������� � ��������� ����
		Matrix potentialMatrix = (circuitGraph * conductivityMatrix * circuitGraph.GetTransposed()).GetInverse()
							* (-circuitGraph * conductivityMatrix * voltageMatrix - circuitGraph * amperageMatrix);

		// ��������� ���������� �� ���� ������ ����
		Matrix u_matrix = circuitGraph.GetTransposed() * potentialMatrix;

		// ��������� ���� � �������������� ������
		Matrix resistorAmperageMatrix = conductivityMatrix * (u_matrix + voltageMatrix);

		return resistorAmperageMatrix;
	}
}
#include "circuit.h"
#include <iostream>
#include <fstream>
#include <vector>

namespace toe
{
	circuit::circuit(branches_data&& branches)
		: _data(std::move(branches)) { }

	// ������� �������������� ������� ������� �� ����� �������� ����
	matrix circuit::get_nodes() const
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

		return matrix{ nodesMatrix };
	}

	// ������� ������� ������������� ���� ������� ������� �����������
	matrix circuit::calculate() const
	{
		matrix resistorMatrix{ _data._resistorValue };
		matrix voltageMatrix{ _data._voltageValue };
		matrix amperageMatrix{ _data._amperageValue };
		
		matrix resistorDiagonalMatrix = resistorMatrix.get_transposed().get_diagonal_matrix();

		matrix circuitGraph = get_nodes();

		matrix conductivityMatrix = resistorDiagonalMatrix.get_inverse();

		// ��������� ���������� ���� ����� ���� �� ��������� � ��������� ����
		matrix potentialMatrix = (circuitGraph * conductivityMatrix * circuitGraph.get_transposed()).get_inverse()
							* (-circuitGraph * conductivityMatrix * voltageMatrix - circuitGraph * amperageMatrix);

		// ��������� ���������� �� ���� ������ ����
		matrix u_matrix = circuitGraph.get_transposed() * potentialMatrix;

		// ��������� ���� � �������������� ������
		matrix resistorAmperageMatrix = conductivityMatrix * (u_matrix + voltageMatrix);

		return resistorAmperageMatrix;
	}
}
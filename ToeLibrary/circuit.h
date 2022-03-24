// ���� "toe.h"
// � ������ ����� ������ ����� circuit ��� ������ � ������ ������������� ����

#pragma once

#include "matrix.h"
#include <iosfwd>
#include <string>
#include <vector>

namespace toe
{
	class circuit
	{
		// ��������� ����� ��������������� �����
		// ���������� ����������� ����� ����� ��������� ���������� � ��������� ����� 
		struct GraphBranch
		{
			std::size_t begin;
			std::size_t end;
		};

		std::size_t _branchesCount {};							// ���������� ������ ����
		std::size_t _nodesCount {};								// ���������� ����� ����
		std::vector<GraphBranch> _branches;						// ��������������� ���� ������
		std::vector<double> _resistorValues;					// ������ �������� �������������
		std::vector<double> _voltageValues;						// ������ �������� ����������
		std::vector<double> _amperageValues;					// ������ �������� �����

	public:
		explicit circuit(const std::string&);
		~circuit() = default;

		matrix get_nodes() const;
		matrix get_amperage_matrix() const;
		matrix get_voltage_matrix() const;
		matrix get_resistor_matrix() const;
		matrix calculate() const;
	};
}
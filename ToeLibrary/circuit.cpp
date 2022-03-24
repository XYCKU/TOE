// файл "toe._rows"
// в данном файле реализован класс circuit для работы с графом электрической цепи


#include "circuit.h"
#include <iostream>
#include <fstream>
#include <vector>

namespace toe
{
	// считывает исходные данные цепи из файла и на их основе формирует граф электрической цепи
	circuit::circuit(const std::string& path)
	{
		std::ifstream input_file(path);

		std::size_t valuei;
		std::size_t branchBegin;
		std::size_t branchEnd;
		double valuef;
		char skipLine[256];

		input_file.getline(skipLine, 256);
		input_file.getline(skipLine, 256);

		while (!input_file.eof())
		{
			input_file >> _branchesCount;

			input_file >> valuei;
			if ((branchBegin = valuei / 10) > _nodesCount)
			{
				_nodesCount = branchBegin;
			}
			if ((branchEnd = valuei % 10) > _nodesCount)
			{
				_nodesCount = branchEnd;
			}

			_branches.emplace_back(branchBegin - 1, branchEnd - 1);

			input_file >> valuef;
			_resistorValues.emplace_back(valuef);

			input_file >> valuef;
			_voltageValues.emplace_back(valuef);

			input_file >> valuef;
			_amperageValues.emplace_back(valuef);
		}

		input_file.close();
	}

	// создает топологическую узловую матрицу по графу исходной цепи
	toe::matrix circuit::get_nodes() const
	{
		toe::matrix nodesMatrix(_nodesCount - 1, _branchesCount);

		for (std::size_t i = 0; i < nodesMatrix.get_rows(); i++)
		{
			for (std::size_t j = 0; j < nodesMatrix.get_columns(); j++)
			{
				if (_branches[j].begin == i)
				{
					nodesMatrix.at(i, j) = 1;
				}
				else if (_branches[j].end == i)
				{
					nodesMatrix.at(i, j) = -1;
				}
				else
				{
					nodesMatrix.at(i, j) = 0;
				}
			}
		}

		return nodesMatrix;
	}

	// создает матрицу источников тока для исходной цепи 
	toe::matrix circuit::get_amperage_matrix() const
	{
		toe::matrix J(_branchesCount, 1);

		for (std::size_t i = 0; i < _branchesCount; i++)
		{
			J.at(i, 0) = _amperageValues[i];
		}

		return J;
	}

	// создает матрицу источников напряжения для исходной цепи
	toe::matrix circuit::get_voltage_matrix() const
	{
		toe::matrix E(_branchesCount, 1);

		for (std::size_t i = 0; i < _branchesCount; i++)
		{
			E.at(i, 0) = _voltageValues[i];
		}

		return E;
	}

	// создает матрицу сопротивлений для исходной цепи
	toe::matrix circuit::get_resistor_matrix() const
	{
		toe::matrix R(_branchesCount, 1);

		for (std::size_t i = 0; i < _branchesCount; i++)
		{
			R.at(i, 0) = _resistorValues[i] < std::numeric_limits<double>::epsilon()
							? std::numeric_limits<double>::epsilon()
							: _resistorValues[i];
		}

		return R;
	}

	// функция расчета электрической цепи методом узловых потенциалов
	toe::matrix circuit::calculate() const
	{
		// задаем матрицы с исходными данными
		toe::matrix resistorMatrix = get_resistor_matrix();
		toe::matrix voltageMatrix = get_voltage_matrix();
		toe::matrix amperageMatrix = get_amperage_matrix();

		// формируем диагональную матрицу RD из матрицы R
		toe::matrix RD = resistorMatrix.get_diagonal_matrix();

		// формируем матрицу соединений A для графа цепи
		toe::matrix A = get_nodes();
		//toe::matrix A(1, 1, -1);

		// формируем матрицу проводимости G из матрицы RD
		toe::matrix G = RD.get_inverse();

		// вычисляем потенциалы всех узлов цепи по отношению к базисному узлу
		toe::matrix F = (A * G * A.transpose()).get_inverse() * (-A * G * voltageMatrix - A * amperageMatrix);

		// вычисляем напряжение на всех ветвях цепи
		toe::matrix U = A.transpose() * F;

		// вычисляем токи в сопротивлениях ветвей
		toe::matrix IR = G * (U + voltageMatrix);

		return IR;
	}

}
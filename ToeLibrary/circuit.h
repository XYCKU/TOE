// файл "toe.h"
// в данном файле описан класс circuit для работы с графом электрической цепи

#pragma once

#include "matrix.h"
#include <iosfwd>
#include <string>
#include <vector>

namespace toe
{
	class circuit
	{
		// структура ветви ориентированный графа
		// определяет направление ветви графа индексами начального и конечного узлов 
		struct GraphBranch
		{
			std::size_t begin;
			std::size_t end;
		};

		std::size_t _branchesCount {};							// количество ветвей цепи
		std::size_t _nodesCount {};								// количество узлов цепи
		std::vector<GraphBranch> _branches;						// ориентированный граф ветвей
		std::vector<double> _resistorValues;					// массив значений сопротивлений
		std::vector<double> _voltageValues;						// массив значений напряжений
		std::vector<double> _amperageValues;					// массив значений токов

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
// файл "toe.cpp"
// в данном файле реализован класс matrix для работы с матрицами

#include "matrix.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace toe
{
	matrix::matrix(std::vector<std::vector<double>>&& source)
		: _data(std::move(source))
		, _rows(_data.size())
		, _columns(_data.front().size())
		, _rank(_rows == _columns ? _rows : 0)
	{
		for (const auto& line : _data)
		{
			if (line.size() != _columns)
			{
				throw std::length_error("Invalid source row length.");
			}
		}
	}

	matrix::matrix(const std::vector<std::vector<double>>& source)
		: matrix(std::vector<std::vector<double>>(source)) { }

	matrix::matrix(std::vector<double>&& matrix)
		: matrix(std::vector<std::vector<double>>{ std::move(matrix) }) { }

	matrix::matrix(const std::vector<double>& source)
		: matrix(std::vector<double>(source)) { }

	matrix::matrix(std::size_t rows, std::size_t columns, double value)
		: _data(std::vector<std::vector<double>>{ rows, std::vector<double>(columns, value) })
		, _rows(rows)
		, _columns(columns)
		, _rank(_rows == _columns ? _rows : 0) { }

	matrix::matrix(std::size_t rows, std::size_t columns)
		: _data(std::vector<std::vector<double>>{ rows, std::vector<double>(columns) })
		, _rows(rows)
		, _columns(columns)
		, _rank(_rows == _columns ? _rows : 0) { }

	bool matrix::is_compatible(const matrix& other) const
	{
		return _columns == other._rows;
	}

	bool matrix::is_equal_size(const matrix& other) const
	{
		return _columns == other._columns && _rows == other._rows;
	}

	bool matrix::is_square() const
	{
		return _rank != 0;
	}

	bool matrix::is_single_column() const
	{
		return _columns == 1;
	}

	double& matrix::at(std::size_t i, std::size_t j)
	{
		return _data[i][j];
	}
	
	std::ostream& operator<<(std::ostream& os, const matrix& matrix)
	{
		for (const auto& line : matrix._data)
		{
			for (const auto& item : line)
			{
				os << std::setw(10) << item;
			}
			os << '\n';
		}

		return os;
	}
	
	matrix operator*(const matrix& lhs, const matrix& rhs)
	{
		if (!lhs.is_compatible(rhs))
		{
			throw std::length_error("Matrices have incompatible sizes.");
		}

		matrix result(lhs._rows, rhs._columns, 0);

		for (std::size_t i = 0; i < result._rows; ++i)
		{
			for (std::size_t j = 0; j < result._columns; ++j)
			{
				for (std::size_t k = 0; k < lhs._columns; ++k)
				{
					result._data[i][j] += lhs._data[i][k] * rhs._data[k][j];
				}
			}
		}

		return result;
	}
	
	matrix operator*(const matrix& source, const double x)
	{
		matrix result = source;

		for (auto& line : result._data)
		{
			for (auto& element : line)
			{
				element *= x;
			}
		}

		return result;
	}

	bool matrix::operator==(const matrix& other) const
	{
		return _data == other._data;
	}
	
	matrix operator+(const matrix& lhs, const matrix& rhs)
	{
		if (!lhs.is_equal_size(rhs))
		{
			throw std::length_error("Matrices have different sizes.");
		}

		matrix result(lhs._rows, lhs._columns);

		for (std::size_t i = 0; i < result._rows; ++i)
		{
			for (std::size_t j = 0; j < result._columns; ++j)
			{
				result._data[i][j] = lhs._data[i][j] + rhs._data[i][j];
			}
		}

		return result;
	}

	matrix operator-(const matrix& lhs, const matrix& rhs)
	{
		if (!lhs.is_equal_size(rhs))
		{
			throw std::length_error("Matrices have different sizes.");
		}

		matrix result(lhs._rows, lhs._columns);

		for (std::size_t i = 0; i < result._rows; ++i)
		{
			for (std::size_t j = 0; j < result._columns; ++j)
			{
				result._data[i][j] = lhs._data[i][j] - rhs._data[i][j];
			}
		}

		return result;
	}
	
	matrix matrix::operator-() const
	{
		matrix result = *this;

		for (std::size_t i = 0; i < result._rows; ++i)
		{
			for (std::size_t j = 0; j < result._columns; ++j)
			{
				result._data[i][j] *= -1;
			}
		}

		return result;
	}
	
	double matrix::get_minor(std::size_t minor_row, std::size_t minor_column) const
	{
		const matrix minorMatrix = get_minor_matrix(minor_row, minor_column);

		if (minorMatrix._rank > 1)
		{
			double result = 0;
			int multiplier = 1;

			for (std::size_t i = 0; i < _rank - 1; ++i)
			{
				result += multiplier * minorMatrix._data[i][0] * minorMatrix.get_minor(i, 0);
				multiplier *= -1;
			}

			return result;
		}

		return minorMatrix._data[0][0];
	}

	matrix matrix::get_minor_matrix(std::size_t minor_row, std::size_t minor_column) const
	{
		if (!is_square())
		{
			throw std::length_error("Matrix is not square.");
		}

		if (minor_row >= _rows)
		{
			throw std::out_of_range("minor_row is greater than source_matrix height.");
		}

		if (minor_column >= _columns)
		{
			throw std::out_of_range("minor_column is greater than source_matrix width.");
		}

		std::vector<std::vector<double>> newData(_rank - 1, std::vector<double>(_rank - 1));
		
		for (std::size_t i = 0; i < minor_row; ++i)
		{
			auto minorColumnIterator = std::next(_data[i].cbegin(), minor_column);

			std::copy(_data[i].cbegin(), minorColumnIterator, newData[i].begin());
			std::copy(++minorColumnIterator, _data[i].cend(), newData[i].begin() + minor_column);
		}

		for (std::size_t i = minor_row + 1; i < _rows; ++i)
		{
			auto minorColumnIterator = std::next(_data[i].cbegin(), minor_column);

			std::copy(_data[i].cbegin(), minorColumnIterator, newData[i - 1].begin());
			std::copy(++minorColumnIterator, _data[i].cend(), newData[i - 1].begin() + minor_column);
		}

		return matrix(std::move(newData));
	}
	
	double matrix::get_determiner() const
	{
		if (!is_square())
		{
			throw std::out_of_range("Can't calculate determiner for not square matrix.");
		}

		if (_rank == 1)
		{
			return _data[0][0];
		}
		
		double result = 0;
		int multiplier = 1;

		for (std::size_t i = 0; i < _rank; ++i)
		{
			result += _data[i][0] * multiplier * get_minor(i, 0);
			multiplier *= -1;
		}

		return result;
	}

	matrix matrix::get_inverse() const
	{
		if (!is_square())
		{
			throw std::out_of_range("Can't inverse matrix because matrix is not square");
		}

		const double determiner = get_determiner();

		if (std::abs(determiner) < std::numeric_limits<double>::epsilon())
		{
			throw std::out_of_range("Can't inverse matrix because determiner is 0");
		}

		if (_rank == 1)
		{
			return matrix { 1, 1, 1 / _data[0][0] };
		}

		matrix result(_rank, _rank);

		int multiplier = 1;
		for (std::size_t i = 0; i < _rank; i++)
		{
			for (std::size_t j = 0; j < _rank; j++)
			{
				result._data[i][j] = multiplier * get_minor(j, i) / determiner;
				multiplier *= -1;
			}
		}

		return result ;
	}
	
	matrix matrix::get_diagonal_matrix() const
	{
		if (!is_single_column())
		{
			throw std::out_of_range("Matrix is not single column");
		}

		matrix result(_columns, _columns, 0);

		for (std::size_t i = 0; i < _columns; i++)
		{
			result._data[i][i] = _data[i][0];
		}

		return result;
	}
	
	matrix matrix::get_transposed() const
	{
		matrix result(_columns, _rows);

		for (std::size_t i = 0; i < _rows; i++)
		{
			for (std::size_t j = 0; j < _columns; j++)
			{
				result._data[j][i] = _data[i][j];
			}
		}

		return result;
	}

	std::size_t matrix::get_rows() const
	{
		return _rows;
	}

	std::size_t matrix::get_columns() const
	{
		return _columns;
	}

}

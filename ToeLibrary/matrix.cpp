// файл "toe.cpp"
// в данном файле реализован класс Matrix для работы с матрицами

#include "Matrix.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace toe
{
	void Matrix::Validate() const
	{
		if (_rows == 0)
		{
			throw std::out_of_range("Rows amount cannot be 0");
		}

		if (_columns == 0)
		{
			throw std::out_of_range("Columns amount cannot be 0");
		}

		for (const auto& line : _data)
		{
			if (line.size() != _columns)
			{
				throw std::length_error("Column has different length.");
			}
		}
	}

	Matrix::Matrix(std::vector<std::vector<double>>&& source)
		: _data(std::move(source))
		, _rows(_data.size())
		, _columns(_data.front().size())
		, _rank(_rows == _columns ? _rows : 0)
	{
		this->Validate();
	}

	Matrix::Matrix(const std::vector<std::vector<double>>& source)
		: Matrix(std::vector<std::vector<double>>(source)) { }

	Matrix::Matrix(const std::vector<double>& matrix)
		: _data(std::vector<std::vector<double>>(matrix.size()))
		, _rows(matrix.size())
		, _columns(1)
		, _rank(_rows == _columns ? _rows : 0)
	{
		auto it = matrix.cbegin();
		for (auto& line : _data)
		{
			line.reserve(1);
			line.emplace_back(*it);
			++it;
		}

		this->Validate();
	}

	Matrix::Matrix(std::size_t rows, std::size_t columns, double value)
		: _data(std::vector<std::vector<double>>{ rows, std::vector<double>(columns, value) })
		, _rows(rows)
		, _columns(columns)
		, _rank(_rows == _columns ? _rows : 0)
	{
		this->Validate();
	}

	bool Matrix::IsCompatible(const Matrix& other) const
	{
		return _columns == other._rows;
	}

	bool Matrix::IsEqualSize(const Matrix& other) const
	{
		return _columns == other._columns && _rows == other._rows;
	}

	bool Matrix::IsSquare() const
	{
		return _rank > 0;
	}

	bool Matrix::IsSingleColumn() const
	{
		return _columns == 1;
	}

	double& Matrix::at(std::size_t i, std::size_t j)
	{
		return _data.at(i).at(j);
	}
	
	std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
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
	
	Matrix operator*(const Matrix& lhs, const Matrix& rhs)
	{
		if (!lhs.IsCompatible(rhs))
		{
			throw std::length_error("Matrices have incompatible sizes.");
		}

		std::vector<std::vector<double>> resultMatrix(lhs._rows);
		
		for (std::size_t i = 0; i < lhs._rows; ++i)
		{
			resultMatrix[i].reserve(rhs._columns);
			for (std::size_t j = 0; j < rhs._columns; ++j)
			{
				resultMatrix[i].emplace_back();
				for (std::size_t k = 0; k < lhs._columns; ++k)
				{
					resultMatrix[i][j] += lhs[i][k] * rhs[k][j];
				}
			}
		}

		return Matrix{ std::move(resultMatrix) };
	}
	
	Matrix operator*(const Matrix& source, const double x)
	{
		std::vector resultMatrix(source._data);
		for (auto& line : resultMatrix)
		{
			for (auto& element : line)
			{
				element *= x;
			}
		}

		return Matrix{ std::move(resultMatrix) };
	}

	const std::vector<double>& Matrix::operator[](std::size_t index) const
	{
		return _data[index];
	}

	bool Matrix::operator==(const Matrix& other) const
	{
		return _data == other._data;
	}
	
	Matrix operator+(const Matrix& lhs, const Matrix& rhs)
	{
		if (!lhs.IsEqualSize(rhs))
		{
			throw std::length_error("Matrices have different sizes.");
		}

		std::vector<std::vector<double>> resultMatrix(lhs._rows);
		
		for (std::size_t i = 0; i < lhs._rows; ++i)
		{
			resultMatrix[i].reserve(lhs._columns);
			for (std::size_t j = 0; j < lhs._columns; ++j)
			{
				resultMatrix[i].emplace_back(lhs[i][j] + rhs[i][j]);
			}
		}

		return Matrix{ std::move(resultMatrix) };
	}

	Matrix operator-(const Matrix& lhs, const Matrix& rhs)
	{
		if (!lhs.IsEqualSize(rhs))
		{
			throw std::length_error("Matrices have different sizes.");
		}

		std::vector<std::vector<double>> resultMatrix(lhs._rows);

		for (std::size_t i = 0; i < lhs._rows; ++i)
		{
			resultMatrix[i].reserve(lhs._columns);
			for (std::size_t j = 0; j < lhs._columns; ++j)
			{
				resultMatrix[i].emplace_back(lhs[i][j] - rhs[i][j]);
			}
		}
		
		return Matrix{ std::move(resultMatrix) };
	}
	
	Matrix Matrix::operator-() const
	{
		std::vector<std::vector<double>> resultMatrix(_rows);

		for (std::size_t i = 0; i < _rows; ++i)
		{
			resultMatrix[i].reserve(_columns);
			for (std::size_t j = 0; j < _columns; ++j)
			{
				resultMatrix[i].emplace_back(-_data[i][j]);
			}
		}

		return Matrix{ std::move(resultMatrix) };
	}
	
	double Matrix::GetMinor(std::size_t minor_row, std::size_t minor_column) const
	{
		return GetMinorMatrix(minor_row, minor_column).GetDeterminer();
	}

	Matrix Matrix::GetMinorMatrix(std::size_t minor_row, std::size_t minor_column) const
	{
		if (!IsSquare())
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

		std::vector<std::vector<double>> resultMatrix(_rank - 1, std::vector<double>(_rank - 1));
		
		for (std::size_t i = 0; i < minor_row; ++i)
		{
			auto minorColumnIterator = std::next(_data[i].cbegin(), minor_column);

			std::copy(_data[i].cbegin(), minorColumnIterator, resultMatrix[i].begin());
			std::copy(++minorColumnIterator, _data[i].cend(), resultMatrix[i].begin() + minor_column);
		}

		for (std::size_t i = minor_row + 1; i < _rows; ++i)
		{
			auto minorColumnIterator = std::next(_data[i].cbegin(), minor_column);

			std::copy(_data[i].cbegin(), minorColumnIterator, resultMatrix[i - 1].begin());
			std::copy(++minorColumnIterator, _data[i].cend(), resultMatrix[i - 1].begin() + minor_column);
		}

		return Matrix(std::move(resultMatrix));
	}
	
	double Matrix::GetDeterminer() const
	{
		if (!IsSquare())
		{
			throw std::out_of_range("Can't calculate determiner for not square matrix.");
		}

		if (_rank == 1)
		{
			return _data[0][0];
		}

		if (_rank == 2)
		{
			return _data[0][0] * _data[1][1] - _data[0][1] * _data[1][0];
		}

		if (_rank == 3)
		{
			return _data[0][0] * _data[1][1] * _data[2][2]
				+ _data[2][0] * _data[0][1] * _data[1][2]
				+ _data[1][0] * _data[2][1] * _data[0][2]
				- _data[2][0] * _data[1][1] * _data[0][2]
				- _data[0][0] * _data[2][1] * _data[1][2]
				- _data[1][0] * _data[0][1] * _data[2][2];
		}
		
		double result = 0;
		int multiplier = 1;

		for (std::size_t i = 0; i < _rank; ++i)
		{
			result += multiplier * _data[i][0] * GetMinor(i, 0);
			multiplier = -multiplier;
		}

		return result;
	}

	Matrix Matrix::GetInverseMatrix() const
	{
		if (!IsSquare())
		{
			throw std::out_of_range("Can't inverse Matrix because Matrix is not square");
		}

		const double determiner = GetDeterminer();

		if (std::abs(determiner) < std::numeric_limits<double>::epsilon())
		{
			throw std::out_of_range("Can't inverse Matrix because determiner is 0");
		}

		if (_rank == 1)
		{
			return Matrix { 1, 1, 1 / _data[0][0] };
		}
		
		double multiplier = 1 / determiner;
		std::vector<std::vector<double>> resultMatrix(_rank, std::vector<double>(_rank));
		
		for (std::size_t i = 0; i < _rank; i++)
		{
			for (std::size_t j = 0; j < _rank; j++)
			{
				resultMatrix[i][j] = multiplier * GetMinor(j, i);
				multiplier = -multiplier;
			}

			if ((_rank & 1) == 0)
			{
				multiplier = -multiplier;
			}
		}

		return Matrix{ std::move(resultMatrix) };
	}
	
	Matrix Matrix::GetDiagonalMatrix() const
	{
		if (!IsSingleColumn())
		{
			throw std::out_of_range("Matrix is not single column");
		}

		std::vector<std::vector<double>> resultMatrix(_rows, std::vector<double>(_rows, 0));
		
		for (std::size_t i = 0; i < _rows; i++)
		{
			resultMatrix[i][i] = _data[i][0];
		}

		return Matrix{ std::move(resultMatrix) };
	}
	
	Matrix Matrix::GetTransposedMatrix() const
	{
		std::vector<std::vector<double>> resultMatrix(_columns, std::vector<double>(_rows));
		
		for (std::size_t i = 0; i < _rows; i++)
		{
			for (std::size_t j = 0; j < _columns; j++)
			{
				resultMatrix[j][i] = _data[i][j];
			}
		}

		return Matrix{ std::move(resultMatrix) };
	}

	std::size_t Matrix::GetRows() const
	{
		return _rows;
	}

	std::size_t Matrix::GetColumns() const
	{
		return _columns;
	}

}

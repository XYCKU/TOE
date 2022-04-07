#pragma once

#include <algorithm>
#include <complex>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace toe
{
	template<typename T>
	class Matrix
	{
		static constexpr double eps = 1e-15;
		static constexpr T zero{ 0 };

		std::vector<std::vector<T>> _data;	
		std::size_t _rows {};
		std::size_t _columns {};
		std::size_t _rank {};

		[[nodiscard]] static bool IsZero(T value);
		[[nodiscard]] static bool IsZero(const std::complex<double>& value);
		void Validate() const;
	public:
		explicit Matrix(std::vector<std::vector<T>>&& source);
		explicit Matrix(const std::vector<std::vector<T>>& source);
		explicit Matrix(const std::vector<T>& source);
		Matrix(std::size_t rows, std::size_t columns, const T& value = T());
		Matrix(const Matrix<T>& other) = default;
		Matrix(Matrix<T>&& other) noexcept = default;
		
		~Matrix() = default;

		T& at(std::size_t i, std::size_t j);

		const std::vector<T>& operator[](std::size_t index) const;
		Matrix<T> operator-() const;
		Matrix<T>& operator=(const Matrix<T>&) = default;
		Matrix<T>& operator=(Matrix<T>&&) noexcept = default;
		bool operator==(const Matrix<T>& other) const;
		auto operator<=>(const Matrix<T>& other) const = default;
		friend Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs)
		{
			if (!lhs.IsEqualSize(rhs))
			{
				throw std::length_error("Matrices have different sizes.");
			}

			std::vector<std::vector<T>> resultMatrix(lhs._rows);

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
		friend Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs)
		{
			if (!lhs.IsEqualSize(rhs))
			{
				throw std::length_error("Matrices have different sizes.");
			}

			std::vector<std::vector<T>> resultMatrix(lhs._rows);

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
		friend Matrix<T> operator*(const Matrix<T>& source, const T& x)
		{
			std::vector<std::vector<T>> resultMatrix(source._data);
			for (auto& line : resultMatrix)
			{
				for (auto& element : line)
				{
					element *= x;
				}
			}

			return Matrix{ std::move(resultMatrix) };
		}
		friend Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs)
		{
			if (!lhs.IsCompatible(rhs))
			{
				throw std::length_error("Matrices have incompatible sizes.");
			}

			std::vector<std::vector<T>> resultMatrix(lhs._rows);

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
		friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix)
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

		[[nodiscard]] T GetDeterminer() const;
		[[nodiscard]] T GetMinor(std::size_t minor_row, std::size_t minor_column) const;
		[[nodiscard]] Matrix<T> GetMinorMatrix(std::size_t minor_row, std::size_t minor_column) const;
		[[nodiscard]] Matrix<T> GetInverseMatrix() const;
		[[nodiscard]] Matrix<T> GetDiagonalMatrix() const;
		[[nodiscard]] Matrix<T> GetTransposedMatrix() const;
		
		[[nodiscard]] bool IsCompatible(const Matrix<T>& other) const;
		[[nodiscard]] bool IsEqualSize(const Matrix<T>& other) const;
		[[nodiscard]] bool IsSquare() const;
		[[nodiscard]] bool IsSingleColumn() const;

		[[nodiscard]] std::size_t GetRows() const;
		[[nodiscard]] std::size_t GetColumns() const;
	};

	template <typename T>
	bool Matrix<T>::IsZero(T value)
	{
		return std::abs(value) < eps;
	}
	
	template <typename T>
	bool Matrix<T>::IsZero(const std::complex<double>& value)
	{
		return std::abs(value.real() < eps) && std::abs(value.imag() < eps);
	}

	template <typename T>
	void Matrix<T>::Validate() const
	{
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
	}

	template <typename T>
	Matrix<T>::Matrix(std::vector<std::vector<T>>&& source)
		: _data(std::move(source))
		, _rows(_data.size())
		, _columns(_data.front().size())
		, _rank(_rows == _columns ? _rows : 0)
	{
		this->Validate();
	}

	template <typename T>
	Matrix<T>::Matrix(const std::vector<std::vector<T>>& source)
		: Matrix(std::vector<std::vector<T>>(source)) { }

	template <typename T>
	Matrix<T>::Matrix(const std::vector<T>& source)
		: _data(std::vector<std::vector<T>>(source.size()))
		, _rows(source.size())
		, _columns(1)
		, _rank(_rows == _columns ? _rows : 0)
	{
		auto it = source.cbegin();
		for (auto& line : _data)
		{
			line.reserve(1);
			line.emplace_back(*it);
			++it;
		}

		this->Validate();
	}

	template <typename T>
	Matrix<T>::Matrix(std::size_t rows, std::size_t columns, const T& value)
		: _data(std::vector<std::vector<T>>{ rows, std::vector<T>(columns, value) })
		, _rows(rows)
		, _columns(columns)
		, _rank(_rows == _columns ? _rows : 0)
	{
		this->Validate();
	}

	template <typename T>
	T& Matrix<T>::at(std::size_t i, std::size_t j)
	{
		return _data.at(i).at(j);
	}

	template <typename T>
	Matrix<T> Matrix<T>::operator-() const
	{
		std::vector<std::vector<T>> resultMatrix(_rows);

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

	template <typename T>
	const std::vector<T>& Matrix<T>::operator[](std::size_t index) const
	{
		return _data[index];
	}

	template <typename T>
	bool Matrix<T>::operator==(const Matrix<T>& other) const
	{
		return _data == other._data;
	}

	template <typename T>
	T Matrix<T>::GetMinor(std::size_t minor_row, std::size_t minor_column) const
	{
		return GetMinorMatrix(minor_row, minor_column).GetDeterminer();
	}

	template <typename T>
	Matrix<T> Matrix<T>::GetMinorMatrix(std::size_t minor_row, std::size_t minor_column) const
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

		std::vector<std::vector<T>> resultMatrix(_rank - 1, std::vector<T>(_rank - 1));

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

	template <typename T>
	T Matrix<T>::GetDeterminer() const
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

		T result = 0;
		int multiplier = 1;

		for (std::size_t i = 0; i < _rank; ++i)
		{
			result += multiplier * _data[i][0] * GetMinor(i, 0);
			multiplier = -multiplier;
		}

		return result;
	}

	template <typename T>
	Matrix<T> Matrix<T>::GetInverseMatrix() const
	{

		if (!IsSquare())
		{
			throw std::logic_error("Can't inverse non-square matrix");
		}

		const T determiner = GetDeterminer();
		
		if (IsZero(determiner))
		{
			throw std::logic_error("Can't inverse matrix with zero determinant");
		}

		if (_rank == 1)
		{
			return Matrix{ 1, 1, 1 / _data[0][0] };
		}

		T multiplier = 1 / determiner;
		std::vector<std::vector<T>> resultMatrix(_rank, std::vector<T>(_rank));

		for (std::size_t i = 0; i < _rank; i++)
		{
			for (std::size_t j = 0; j < _rank; j++)
			{
				resultMatrix[i][j] = multiplier * GetMinor(j, i);
				multiplier = -multiplier;
			}

			if (_rank % 2 == 0)
			{
				multiplier = -multiplier;
			}
		}

		return Matrix{ std::move(resultMatrix) };
	}

	template <typename T>
	Matrix<T> Matrix<T>::GetDiagonalMatrix() const
	{
		if (!IsSingleColumn())
		{
			throw std::out_of_range("Matrix is not single column");
		}

		std::vector<std::vector<T>> resultMatrix(_rows, std::vector<T>(_rows, 0));

		for (std::size_t i = 0; i < _rows; i++)
		{
			resultMatrix[i][i] = _data[i][0];
		}

		return Matrix{ std::move(resultMatrix) };
	}

	template <typename T>
	Matrix<T> Matrix<T>::GetTransposedMatrix() const
	{
		std::vector<std::vector<T>> resultMatrix(_columns, std::vector<T>(_rows));

		for (std::size_t i = 0; i < _rows; i++)
		{
			for (std::size_t j = 0; j < _columns; j++)
			{
				resultMatrix[j][i] = _data[i][j];
			}
		}

		return Matrix{ std::move(resultMatrix) };
	}

	template <typename T>
	bool Matrix<T>::IsCompatible(const Matrix<T>& other) const
	{
		return _columns == other._rows;
	}

	template <typename T>
	bool Matrix<T>::IsEqualSize(const Matrix<T>& other) const
	{
		return _columns == other._columns && _rows == other._rows;
	}

	template <typename T>
	bool Matrix<T>::IsSquare() const
	{
		return _rank > 0;
	}

	template <typename T>
	bool Matrix<T>::IsSingleColumn() const
	{
		return _columns == 1;
	}
	
	template <typename T>
	std::size_t Matrix<T>::GetRows() const
	{
		return _rows;
	}

	template <typename T>
	std::size_t Matrix<T>::GetColumns() const
	{
		return _columns;
	}
}

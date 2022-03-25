#pragma once

#include <iosfwd>
#include <vector>

namespace toe
{
	class Matrix
	{
		std::vector<std::vector<double>> _data;
		std::size_t _rows {};
		std::size_t _columns {};
		std::size_t _rank {};

	public:
		explicit Matrix(std::vector<std::vector<double>>&& source);
		explicit Matrix(const std::vector<std::vector<double>>& source);
		explicit Matrix(std::vector<double>&& matrix);
		explicit Matrix(const std::vector<double>& source);
		Matrix(std::size_t rows, std::size_t columns, double value);
		Matrix(std::size_t rows, std::size_t columns);
		Matrix(const Matrix& other) = default;
		Matrix(Matrix&& other) noexcept = default;
		
		~Matrix() = default;

		double& at(std::size_t, std::size_t);

		Matrix operator-() const;
		Matrix& operator=(const Matrix&) = default;
		Matrix& operator=(Matrix&&) = default;
		const std::vector<double>& operator[](std::size_t index);
		bool operator==(const Matrix& other) const;
		auto operator<=>(const Matrix& other) const = default;
		friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);
		friend Matrix operator-(const Matrix& lhs, const Matrix& rhs);
		friend Matrix operator*(const Matrix& source, const double x);
		friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);
		friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

		[[nodiscard]] double GetMinor(std::size_t minor_row, std::size_t minor_column) const;
		[[nodiscard]] Matrix GetMinorMatrix(std::size_t minor_row, std::size_t minor_column) const;
		[[nodiscard]] double GetDeterminer() const;
		[[nodiscard]] Matrix GetInverseMatrix() const;
		[[nodiscard]] Matrix GetDiagonalMatrix() const;
		[[nodiscard]] Matrix GetTransposedMatrix() const;
		
		[[nodiscard]] bool IsCompatible(const Matrix& other) const;
		[[nodiscard]] bool IsEqualSize(const Matrix& other) const;
		[[nodiscard]] bool IsSquare() const;
		[[nodiscard]] bool IsSingleColumn() const;

		[[nodiscard]] std::size_t GetRows() const;
		[[nodiscard]] std::size_t GetColumns() const;
	};

}

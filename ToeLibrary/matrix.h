#pragma once

#include <iosfwd>
#include <vector>

namespace toe
{
	class matrix
	{
		std::vector<std::vector<double>> _data;
		std::size_t _rows {};
		std::size_t _columns {};
		std::size_t _rank {};

	public:
		explicit matrix(std::vector<std::vector<double>>&& source);
		explicit matrix(const std::vector<std::vector<double>>& source);
		explicit matrix(std::vector<double>&& matrix);
		explicit matrix(const std::vector<double>& source);
		matrix(std::size_t rows, std::size_t columns, double value);
		matrix(std::size_t rows, std::size_t columns);
		matrix(const matrix& other) = default;
		matrix(matrix&& other) noexcept = default;
		
		~matrix() = default;

		double& at(std::size_t, std::size_t);

		matrix operator-() const;
		matrix& operator=(const matrix&) = default;
		matrix& operator=(matrix&&) = default;
		bool operator==(const matrix& other) const;
		auto operator<=>(const matrix& other) const = default;
		friend matrix operator+(const matrix& lhs, const matrix& rhs);
		friend matrix operator-(const matrix& lhs, const matrix& rhs);
		friend matrix operator*(const matrix& source, const double x);
		friend matrix operator*(const matrix& lhs, const matrix& rhs);
		friend std::ostream& operator<<(std::ostream& os, const matrix& matrix);

		[[nodiscard]] double get_minor(std::size_t minor_row, std::size_t minor_column) const;
		[[nodiscard]] matrix get_minor_matrix(std::size_t minor_row, std::size_t minor_column) const;
		[[nodiscard]] double get_determiner() const;
		[[nodiscard]] matrix get_inverse() const;
		[[nodiscard]] matrix get_diagonal_matrix() const;
		[[nodiscard]] matrix get_transposed() const;
		
		[[nodiscard]] bool is_compatible(const matrix& other) const;
		[[nodiscard]] bool is_equal_size(const matrix& other) const;
		[[nodiscard]] bool is_square() const;
		[[nodiscard]] bool is_single_column() const;

		[[nodiscard]] std::size_t get_rows() const;
		[[nodiscard]] std::size_t get_columns() const;
	};

}

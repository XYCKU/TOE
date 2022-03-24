#include "pch.h"

TEST(GetRows_Tests, ReturnRowsAmount_0to1000) {
	for (std::size_t i = 0; i < 1000; ++i)
	{
		toe::matrix m{ i,1 };
		EXPECT_EQ(m.get_rows(), i);
	}
}

TEST(GetColumns_Tests, ReturnColumnsAmount_0to1000) {
	for (std::size_t i = 0; i < 1000; ++i)
	{
		toe::matrix m{ 1,i };
		EXPECT_EQ(m.get_columns(), i);
	}
}

TEST(Ctor_Tests, OneRowMatrix)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_real_distribution<double> dist{ -100, 100 };

	auto gen = [&dist, &eng]() {return dist(eng); };

	for (std::size_t i = 0; i < 1000; ++i)
	{
		std::vector<double> sourceVector(i);
		std::generate(sourceVector.begin(), sourceVector.end(), gen);

		toe::matrix result(sourceVector);

		toe::matrix expected(std::vector<std::vector<double>> {sourceVector});

		ASSERT_EQ(result, expected);
	}
}

TEST(Ctor_Tests, CopyCtor)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_real_distribution<double> dist{ -100, 100 };

	auto gen = [&dist, &eng]()
	{
		return dist(eng);
	};

	auto genVector = [&dist, &eng, &gen](std::size_t length)
	{
		std::vector<double> result(length);
		std::generate(result.begin(), result.end(), gen);
		return result;
	};

	for (std::size_t i = 1; i < 100; ++i)
	{
		std::vector<std::vector<double>> sourceVector(i);
		std::generate(sourceVector.begin(), sourceVector.end(), [&genVector, i]() {return genVector(i); });

		toe::matrix expected(sourceVector);

		toe::matrix result(expected);

		ASSERT_EQ(result, expected);
	}
}

TEST(GetTransposed_Tests, GetTransposed_Tests_MatrixSize1x1_Test)
{
	toe::matrix actual(1, 1, 5);
	toe::matrix expected(1, 1, 5);
	actual = actual.get_transposed();
	ASSERT_EQ(actual, expected);
}

TEST(GetTransposed_Tests, GetTransposed_Tests_MatrixSize4x3_Test)
{
	std::vector<std::vector<double>> vector = { {4,3,2}, {4,3,2}, {4,3,2}, {4,3,2} };
	toe::matrix actual(vector);
	toe::matrix expected({{4,4,4,4},{3,3,3,3},{2,2,2,2}});
	actual = actual.get_transposed();
	ASSERT_EQ(actual, expected);
}

TEST(GetTransposed_Tests, GetTransposed_Tests_MatrixSize3x3_Test)
{
	std::vector<std::vector<double>> vector = { {4,4,4}, {4,4,4}, {4,4,4}, {4,4,4} };
	toe::matrix actual(vector);
	toe::matrix expected({ {4,4,4,4},{4,4,4,4},{4,4,4,4} });
	actual = actual.get_transposed();
	ASSERT_EQ(actual, expected);
}

TEST(GetMinorMatrix_Tests, GetMinorMatrix_Tests_MatrixSize3x3_Minor_0_0_Test)
{
	std::vector<std::vector<double>> vector { {1,2,3},{4,5,6},{7,8,9} };
	toe::matrix actual(std::move(vector));
	actual = actual.get_minor_matrix(0, 0);
	toe::matrix expected({ { 5,6 }, { 8,9 } });
	ASSERT_EQ(actual, expected);
}

TEST(GetMinorMatrix_Tests, GetMinorMatrix_Tests_MatrixSize3x3_Minor_0_1_Test)
{
	std::vector<std::vector<double>> vector{ {1,2,3},{4,5,6},{7,8,9} };
	toe::matrix actual(std::move(vector));
	actual = actual.get_minor_matrix(0, 1);
	toe::matrix expected({ { 4,6 }, { 7,9 } });
	ASSERT_EQ(actual, expected);
}

TEST(GetMinorMatrix_Tests, GetMinorMatrix_Tests_MatrixSize3x3_Minor_2_2_Test)
{
	std::vector<std::vector<double>> vector{ {1,2,3},{4,5,6},{7,8,9} };
	toe::matrix actual(std::move(vector));
	actual = actual.get_minor_matrix(2, 2);
	toe::matrix expected({ { 1,2 }, { 4,5 } });
	ASSERT_EQ(actual, expected);
}

TEST(GetMinor_Tests, GetMinor_Tests_MatrixSize3x3_Minor_0_0_Test)
{
	std::vector<std::vector<double>> vector  { {1,2,3},{4,5,6},{7,8,9} };
	toe::matrix m(std::move(vector));
	double actual = m.get_minor(0, 0);
	double expected = -3;
	ASSERT_EQ(actual, expected);
}


TEST(GetMinor_Tests, GetMinor_Tests_MatrixSize3x3_Minor_0_1_Test)
{
	std::vector<std::vector<double>> vector{ {1,2,3},{4,5,6},{7,8,9} };
	toe::matrix m(std::move(vector));
	double actual = m.get_minor(0, 1);
	double expected = -6;
	ASSERT_EQ(actual, expected);
}

TEST(GetMinor_Tests, GetMinor_Tests_MatrixSize3x3_Minor_0_2_Test)
{
	std::vector<std::vector<double>> vector{ {1,2,3},{4,5,6},{7,8,9} };
	toe::matrix m(std::move(vector));
	double actual = m.get_minor(0, 2);
	double expected = -3;
	ASSERT_EQ(actual, expected);
}

TEST(GetMinor_Tests, GetMinor_Tests_MatrixSize3x3_Minor_1_0_Test)
{
	std::vector<std::vector<double>> vector{ {1,2,3},{4,5,6},{7,8,9} };
	toe::matrix m(std::move(vector));
	double actual = m.get_minor(1, 0);
	double expected = -6;
	ASSERT_EQ(actual, expected);
}

TEST(GetMinor_Tests, GetMinor_Tests_MatrixSize3x3_Minor_1_1_Test)
{
	std::vector<std::vector<double>> vector{ {1,2,3},{4,5,6},{7,8,9} };
	toe::matrix m(std::move(vector));
	double actual = m.get_minor(1, 1);
	double expected = -12;
	ASSERT_EQ(actual, expected);
}

TEST(GetMinor_Tests, GetMinor_Tests_MatrixSize3x3_Minor_1_2_Test)
{
	std::vector<std::vector<double>> vector{ {1,2,3},{4,5,6},{7,8,9} };
	toe::matrix m(std::move(vector));
	double actual = m.get_minor(1, 2);
	double expected = -6;
	ASSERT_EQ(actual, expected);
}

TEST(GetMinor_Tests, GetMinor_Tests_MatrixSize3x3_Minor_2_0_Test)
{
	std::vector<std::vector<double>> vector{ {1,2,3},{4,5,6},{7,8,9} };
	toe::matrix m(std::move(vector));
	double actual = m.get_minor(2, 0);
	double expected = -3;
	ASSERT_EQ(actual, expected);
}

TEST(GetMinor_Tests, GetMinor_Tests_MatrixSize3x3_Minor_2_1_Test)
{
	std::vector<std::vector<double>> vector{ {1,2,3},{4,5,6},{7,8,9} };
	toe::matrix m(std::move(vector));
	double actual = m.get_minor(2, 1);
	double expected = -6;
	ASSERT_EQ(actual, expected);
}

TEST(GetMinor_Tests, GetMinor_Tests_MatrixSize3x3_Minor_2_2_Test)
{
	std::vector<std::vector<double>> vector{ {1,2,3},{4,5,6},{7,8,9} };
	toe::matrix m(std::move(vector));
	double actual = m.get_minor(2, 2);
	double expected = -3;
	ASSERT_EQ(actual, expected);
}

TEST(GetDeterminer_Tests, GetDeternimer_Tests_MatrixSize4x4_Test)
{
	std::vector<std::vector<double>> vector{ {1,25,3,0},{1,8,2,6},{9,10,11,12}, {13,14,15,16} };
	toe::matrix m(std::move(vector));
	double actual = m.get_determiner();
	double expected = 852;
	ASSERT_EQ(actual, expected);
}

TEST(GetDeterminer_Tests, GetDeternimer_Tests_MatrixSize3x3_Test)
{
	std::vector<std::vector<double>> vector{ {1,2,3},{4,5,6},{7,8,9} };
	toe::matrix m(std::move(vector));
	double actual = m.get_determiner();
	double expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(GetDeterminer_Tests, GetDeternimer_Tests_MatrixSize2x2_Test)
{
	std::vector<std::vector<double>> vector{ {1,2},{3,4}};
	toe::matrix m(std::move(vector));
	double actual = m.get_determiner();
	double expected = -2;
	ASSERT_EQ(actual, expected);
}

TEST(GetDeterminer_Tests, GetDeternimer_Tests_MatrixSize1x1_Test)
{
	std::vector<std::vector<double>> vector{ {1} };
	toe::matrix m(std::move(vector));
	double actual = m.get_determiner();
	double expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(IsCompatible_Tests, IsCompatible_Tests_MatrixSize3x3_ReturnsTrue_Test)
{
	toe::matrix actual(3, 3, 0);
	toe::matrix other(3, 3, 1);
	ASSERT_TRUE(actual.is_compatible(other));
}

TEST(IsCompatible_Tests, IsCompatible_Tests_MatrixSize3x4_ReturnsTrue_Test)
{
	toe::matrix actual(3, 4, 0);
	toe::matrix other(4, 3, 1);
	ASSERT_TRUE(actual.is_compatible(other));
}

TEST(IsCompatible_Tests, IsCompatible_Tests_MatrixSize3x4_ReturnsFalse_Test)
{
	toe::matrix actual(3, 4, 0);
	toe::matrix other(3, 4, 1);
	ASSERT_FALSE(actual.is_compatible(other));
}

TEST(IsEqualSize_Tests, IsCompatible_Tests_MatrixSize3x3_ReturnsTrue_Test)
{
	toe::matrix actual(3, 3, 0);
	toe::matrix other(3, 3, 1);
	ASSERT_TRUE(actual.is_equal_size(other));
}
TEST(IsEqualSize_Tests, IsCompatible_Tests_MatrixSize3x4_ReturnsTrue_Test)
{
	toe::matrix actual(3, 4, 0);
	toe::matrix other(3, 4, 1);
	ASSERT_TRUE(actual.is_equal_size(other));
}
TEST(IsEqualSize_Tests, IsCompatible_Tests_MatrixSize3x3_ReturnsFalse_Test)
{
	toe::matrix actual(3, 4, 0);
	toe::matrix other(4, 3, 1);
	ASSERT_FALSE(actual.is_equal_size(other));
}
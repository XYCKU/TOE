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

	for (std::size_t i = 1; i < 500; ++i)
	{
		std::vector<std::vector<double>> sourceVector(i);
		std::generate(sourceVector.begin(), sourceVector.end(), [&genVector, i]() {return genVector(i); });

		toe::matrix expected(sourceVector);

		toe::matrix result(expected);

		ASSERT_EQ(result, expected);
	}
}
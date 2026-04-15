#include "../src/CDate.h"
#include <gtest/gtest.h>

TEST(CDateDifferenceTests, PositiveDifference)
{
	CDate d1(1, Month::JANUARY, 2010);
	CDate d2(30, Month::DECEMBER, 2009);

	EXPECT_EQ(d1 - d2, 2); // timestamp difference
}

TEST(CDateDifferenceTests, NegativeDifference)
{
	CDate d1(1, Month::JANUARY, 2010);
	CDate d2(3, Month::JANUARY, 2010);

	EXPECT_EQ(d1 - d2, -2);
}

TEST(CDateDifferenceTests, ZeroDifference)
{
	CDate d1(1, Month::JANUARY, 2010);

	EXPECT_EQ(d1 - d1, 0);
}

TEST(CDateDifferenceTests, ValidMinusInvalidReturnsZero)
{
	CDate valid(1, Month::JANUARY, 2010);
	CDate invalid(32, Month::JANUARY, 2020);

	EXPECT_EQ(valid - invalid, 0);
}

TEST(CDateDifferenceTests, InvalidMinusValidReturnsZero)
{
	CDate valid(1, Month::JANUARY, 2010);
	CDate invalid(32, Month::JANUARY, 2020);

	EXPECT_EQ(invalid - valid, 0);
}

TEST(CDateDifferenceTests, InvalidMinusInvalidReturnsZero)
{
	CDate invalid1(32, Month::JANUARY, 2020);
	CDate invalid2(0, Month::FEBRUARY, 2020);

	EXPECT_EQ(invalid1 - invalid2, 0);
}

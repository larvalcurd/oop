#include "../src/CDate.h"
#include <gtest/gtest.h>

TEST(CDateComparisonTests, EqualValidDates)
{
	CDate a(1, Month::JANUARY, 2010);
	CDate b(1, Month::JANUARY, 2010);

	EXPECT_TRUE(a == b);
	EXPECT_FALSE(a != b);
}

TEST(CDateComparisonTests, DifferentValidDates)
{
	CDate a(1, Month::JANUARY, 2010);
	CDate b(2, Month::JANUARY, 2010);

	EXPECT_FALSE(a == b);
	EXPECT_TRUE(a != b);
}

TEST(CDateComparisonTests, ValidAndInvalidAreNotEqual)
{
	CDate valid(1, Month::JANUARY, 2010);
	CDate invalid(32, Month::JANUARY, 2010);

	EXPECT_FALSE(valid == invalid);
	EXPECT_TRUE(valid != invalid);

	EXPECT_FALSE(invalid == valid);
	EXPECT_TRUE(invalid != valid);
}

TEST(CDateComparisonTests, InvalidAndInvalidAreEqual)
{
	CDate a(32, Month::JANUARY, 2010);
	CDate b(0, Month::FEBRUARY, 2020);

	EXPECT_TRUE(a == b);
	EXPECT_FALSE(a != b);
}

TEST(CDateComparisonTests, SameObjectIsEqualToItself)
{
	CDate date(28, Month::FEBRUARY, 2024);

	EXPECT_TRUE(date == date);
	EXPECT_FALSE(date != date);
}

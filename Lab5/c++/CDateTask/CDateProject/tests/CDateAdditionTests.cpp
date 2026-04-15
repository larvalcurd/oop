#include "../src/CDate.h"
#include <gtest/gtest.h>

TEST(CDateAdditionTests, AddPositiveDaysAcrossMonth)
{
	CDate date(28, Month::FEBRUARY, 2010);

	CDate result = date + 3;

	EXPECT_TRUE(result.IsValid());
	EXPECT_EQ(result.GetDay(), 3u);
	EXPECT_EQ(result.GetMonth(), Month::MARCH);
	EXPECT_EQ(result.GetYear(), 2010u);
}

TEST(CDateAdditionTests, AddNegativeDaysInLeapYear)
{
	CDate date(1, Month::MARCH, 2024);

	CDate result = date + (-1);

	EXPECT_TRUE(result.IsValid());
	EXPECT_EQ(result.GetDay(), 29u);
	EXPECT_EQ(result.GetMonth(), Month::FEBRUARY);
	EXPECT_EQ(result.GetYear(), 2024u);
}

TEST(CDateAdditionTests, AddPastUpperBoundaryBecomesInvalid)
{
	CDate date(31, Month::DECEMBER, 9999);

	CDate result = date + 1;

	EXPECT_FALSE(result.IsValid());
}

TEST(CDateAdditionTests, AddPastLowerBoundaryBecomesInvalid)
{
	CDate date(1, Month::JANUARY, 1970);

	CDate result = date + (-1);

	EXPECT_FALSE(result.IsValid());
}

TEST(CDateAdditionTests, AddToInvalidDateStaysInvalid)
{
	CDate date(32, Month::JANUARY, 2024); 

	CDate result = date + 10;

	EXPECT_FALSE(result.IsValid());
}

TEST(CDateAdditionTests, AdditionDoesNotModifyOriginal)
{
	CDate date(28, Month::FEBRUARY, 2010);

	CDate result = date + 3;

	EXPECT_TRUE(date.IsValid());
	EXPECT_EQ(date.GetDay(), 28u);
	EXPECT_EQ(date.GetMonth(), Month::FEBRUARY);
	EXPECT_EQ(date.GetYear(), 2010u);

	EXPECT_TRUE(result.IsValid());
	EXPECT_EQ(result.GetDay(), 3u);
	EXPECT_EQ(result.GetMonth(), Month::MARCH);
	EXPECT_EQ(result.GetYear(), 2010u);
}

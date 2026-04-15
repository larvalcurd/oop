#include "../src/CDate.h"
#include <gtest/gtest.h>

TEST(CDateSubtractionTests, SubtractAcrossMonthAndYear)
{
	CDate date(1, Month::JANUARY, 2010);

	CDate result = date - 2;

	EXPECT_TRUE(result.IsValid());
	EXPECT_EQ(result.GetDay(), 30u);
	EXPECT_EQ(result.GetMonth(), Month::DECEMBER);
	EXPECT_EQ(result.GetYear(), 2009u);
}

TEST(CDateSubtractionTests, SubtractIntoLeapDay)
{
	CDate date(1, Month::MARCH, 2024);

	CDate result = date - 1;

	EXPECT_TRUE(result.IsValid());
	EXPECT_EQ(result.GetDay(), 29u);
	EXPECT_EQ(result.GetMonth(), Month::FEBRUARY);
	EXPECT_EQ(result.GetYear(), 2024u);
}

TEST(CDateSubtractionTests, SubtractPastLowerBoundaryBecomesInvalid)
{
	CDate date(1, Month::JANUARY, 1970);

	CDate result = date - 1;

	EXPECT_FALSE(result.IsValid());
}

TEST(CDateSubtractionTests, SubtractFromInvalidStaysInvalid)
{
	CDate date(32, Month::JANUARY, 2024); // invalid

	CDate result = date - 10;

	EXPECT_FALSE(result.IsValid());
}

TEST(CDateSubtractionTests, SubtractionDoesNotModifyOriginal)
{
	CDate date(1, Month::JANUARY, 2010);

	CDate result = date - 2;

	EXPECT_TRUE(date.IsValid());
	EXPECT_EQ(date.GetDay(), 1u);
	EXPECT_EQ(date.GetMonth(), Month::JANUARY);
	EXPECT_EQ(date.GetYear(), 2010u);

	EXPECT_TRUE(result.IsValid());
	EXPECT_EQ(result.GetDay(), 30u);
	EXPECT_EQ(result.GetMonth(), Month::DECEMBER);
	EXPECT_EQ(result.GetYear(), 2009u);
}

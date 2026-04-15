#include "../src/CDate.h"
#include <gtest/gtest.h>

TEST(CDateCompoundAssignmentTests, PlusEqualsAcrossMonth)
{
	CDate date(28, Month::FEBRUARY, 2010);

	CDate& ref = (date += 3);

	EXPECT_EQ(&ref, &date);
	EXPECT_TRUE(date.IsValid());
	EXPECT_EQ(date.GetDay(), 3u);
	EXPECT_EQ(date.GetMonth(), Month::MARCH);
	EXPECT_EQ(date.GetYear(), 2010u);
}

TEST(CDateCompoundAssignmentTests, MinusEqualsAcrossYear)
{
	CDate date(1, Month::JANUARY, 2010);

	CDate& ref = (date -= 2);

	EXPECT_EQ(&ref, &date);
	EXPECT_TRUE(date.IsValid());
	EXPECT_EQ(date.GetDay(), 30u);
	EXPECT_EQ(date.GetMonth(), Month::DECEMBER);
	EXPECT_EQ(date.GetYear(), 2009u);
}

TEST(CDateCompoundAssignmentTests, PlusEqualsUpperBoundaryBecomesInvalid)
{
	CDate date(31, Month::DECEMBER, 9999);

	date += 1;

	EXPECT_FALSE(date.IsValid());
}

TEST(CDateCompoundAssignmentTests, InvalidPlusEqualsNoOp)
{
	CDate date(32, Month::JANUARY, 2024); // invalid

	date += 10;

	EXPECT_FALSE(date.IsValid());
	EXPECT_EQ(date.GetDay(), 0u);
	EXPECT_EQ(date.GetMonth(), Month::JANUARY);
	EXPECT_EQ(date.GetYear(), 0u);
}

TEST(CDateCompoundAssignmentTests, InvalidMinusEqualsNoOp)
{
	CDate date(32, Month::JANUARY, 2024); // invalid

	date -= 10;

	EXPECT_FALSE(date.IsValid());
	EXPECT_EQ(date.GetDay(), 0u);
	EXPECT_EQ(date.GetMonth(), Month::JANUARY);
	EXPECT_EQ(date.GetYear(), 0u);
}

TEST(CDateCompoundAssignmentTests, PlusEqualsReturnsReference)
{
	static_assert(std::is_same_v<decltype(std::declval<CDate&>() += 1), CDate&>);
}

TEST(CDateCompoundAssignmentTests, MinusEqualsReturnsReference)
{
	static_assert(std::is_same_v<decltype(std::declval<CDate&>() -= 1), CDate&>);
}

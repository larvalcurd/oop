#include "../src/CDate.h"
#include <gtest/gtest.h>

TEST(CDatePostfixTests, PostfixIncrementBasic)
{
	CDate date(14, Month::APRIL, 2026);

	CDate old = date++;

	EXPECT_EQ(old.GetDay(), 14u);
	EXPECT_EQ(date.GetDay(), 15u);
}

TEST(CDatePostfixTests, PostfixDecrementBasic)
{
	CDate date(15, Month::APRIL, 2026);

	CDate old = date--;

	EXPECT_EQ(old.GetDay(), 15u);
	EXPECT_EQ(date.GetDay(), 14u);
}

TEST(CDatePostfixTests, PostfixIncrementFullCheck)
{
	CDate date(31, Month::DECEMBER, 2026);

	CDate old = date++;

	EXPECT_EQ(old.GetDay(), 31u);
	EXPECT_EQ(old.GetMonth(), Month::DECEMBER);
	EXPECT_EQ(old.GetYear(), 2026u);

	EXPECT_EQ(date.GetDay(), 1u);
	EXPECT_EQ(date.GetMonth(), Month::JANUARY);
	EXPECT_EQ(date.GetYear(), 2027u);
}

TEST(CDatePostfixTests, PostfixIncrementUpperBoundary)
{
	CDate date(31, Month::DECEMBER, 9999);

	CDate old = date++;

	EXPECT_TRUE(old.IsValid());
	EXPECT_EQ(old.GetYear(), 9999u);

	EXPECT_FALSE(date.IsValid());
}

TEST(CDatePostfixTests, PostfixDecrementLowerBoundary)
{
	CDate date(1, Month::JANUARY, 1970);

	CDate old = date--;

	EXPECT_TRUE(old.IsValid());
	EXPECT_EQ(old.GetYear(), 1970u);

	EXPECT_FALSE(date.IsValid());
}

TEST(CDatePostfixTests, PostfixIncrementInvalidNoOp)
{
	CDate date(32, Month::JANUARY, 2026); 

	CDate old = date++;

	EXPECT_FALSE(old.IsValid());
	EXPECT_FALSE(date.IsValid());
}

TEST(CDatePostfixTests, PostfixDecrementInvalidNoOp)
{
	CDate date(32, Month::JANUARY, 2026); 

	CDate old = date--;

	EXPECT_FALSE(old.IsValid());
	EXPECT_FALSE(date.IsValid());
}

TEST(CDatePostfixTests, PostfixReturnsByValue)
{
	static_assert(std::is_same_v<decltype(std::declval<CDate>()++), CDate>);
}

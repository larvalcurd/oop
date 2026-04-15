#include "../src/CDate.h"
#include <gtest/gtest.h>

TEST(CDatePrefixTests, PrefixIncrementNormalDay)	
{
	CDate date(14, Month::APRIL, 2026);

	CDate& ref = ++date;

	EXPECT_EQ(&ref, &date);
	EXPECT_TRUE(date.IsValid());
	EXPECT_EQ(date.GetDay(), 15u);
	EXPECT_EQ(date.GetMonth(), Month::APRIL);
	EXPECT_EQ(date.GetYear(), 2026u);
}

TEST(CDatePrefixTests, PrefixDecrementNormalDay)
{
	CDate date(15, Month::APRIL, 2026);

	CDate& ref = --date;

	EXPECT_EQ(&ref, &date);
	EXPECT_TRUE(date.IsValid());
	EXPECT_EQ(date.GetDay(), 14u);
	EXPECT_EQ(date.GetMonth(), Month::APRIL);
	EXPECT_EQ(date.GetYear(), 2026u);
}

TEST(CDatePrefixTests, PrefixIncrementEndOfMonth)
{
	CDate date(31, Month::JANUARY, 2026);

	++date;

	EXPECT_TRUE(date.IsValid());
	EXPECT_EQ(date.GetDay(), 1u);
	EXPECT_EQ(date.GetMonth(), Month::FEBRUARY);
	EXPECT_EQ(date.GetYear(), 2026u);
}

TEST(CDatePrefixTests, PrefixIncrementEndOfYear)
{
	CDate date(31, Month::DECEMBER, 2026);

	++date;

	EXPECT_TRUE(date.IsValid());
	EXPECT_EQ(date.GetDay(), 1u);
	EXPECT_EQ(date.GetMonth(), Month::JANUARY);
	EXPECT_EQ(date.GetYear(), 2027u);
}

TEST(CDatePrefixTests, PrefixDecrementStartOfMonth)
{
	CDate date(1, Month::MARCH, 2026);

	--date;

	EXPECT_TRUE(date.IsValid());
	EXPECT_EQ(date.GetDay(), 28u);
	EXPECT_EQ(date.GetMonth(), Month::FEBRUARY);
	EXPECT_EQ(date.GetYear(), 2026u);
}

TEST(CDatePrefixTests, PrefixDecrementStartOfYear)
{
	CDate date(1, Month::JANUARY, 1971);

	--date;

	EXPECT_TRUE(date.IsValid());
	EXPECT_EQ(date.GetDay(), 31u);
	EXPECT_EQ(date.GetMonth(), Month::DECEMBER);
	EXPECT_EQ(date.GetYear(), 1970u);
}

TEST(CDatePrefixTests, PrefixIncrementUpperBoundaryBecomesInvalid)
{
	CDate date(31, Month::DECEMBER, 9999);

	++date;

	EXPECT_FALSE(date.IsValid());
}

TEST(CDatePrefixTests, PrefixDecrementLowerBoundaryBecomesInvalid)
{
	CDate date(1, Month::JANUARY, 1970);

	--date;

	EXPECT_FALSE(date.IsValid());
}

TEST(CDatePrefixTests, PrefixOnInvalidDateIsNoOpIncrement)
{
	CDate date(32, Month::JANUARY, 2026); // invalid

	EXPECT_FALSE(date.IsValid());

	++date;

	EXPECT_FALSE(date.IsValid());
	EXPECT_EQ(date.GetDay(), 0u);
	EXPECT_EQ(date.GetMonth(), Month::JANUARY);
	EXPECT_EQ(date.GetYear(), 0u);
}

TEST(CDatePrefixTests, PrefixOnInvalidDateIsNoOpDecrement)
{
	CDate date(32, Month::JANUARY, 2026); // invalid

	EXPECT_FALSE(date.IsValid());

	--date;

	EXPECT_FALSE(date.IsValid());
	EXPECT_EQ(date.GetDay(), 0u);
	EXPECT_EQ(date.GetMonth(), Month::JANUARY);
	EXPECT_EQ(date.GetYear(), 0u);
}

TEST(CDatePrefixTests, PrefixReturnsReference)
{
	static_assert(std::is_same_v<decltype(++std::declval<CDate&>()), CDate&>);
	static_assert(std::is_same_v<decltype(--std::declval<CDate&>()), CDate&>);
}

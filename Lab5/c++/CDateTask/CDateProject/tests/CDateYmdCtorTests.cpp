#include "../src/CDate.h"
#include <gtest/gtest.h>

TEST(CDateYmdCtor, EpochDateRoundTrip)
{
	CDate d(1u, Month::JANUARY, 1970u);

	ASSERT_TRUE(d.IsValid());
	EXPECT_EQ(d.GetDay(), 1u);
	EXPECT_EQ(d.GetMonth(), Month::JANUARY);
	EXPECT_EQ(d.GetYear(), 1970u);
}

TEST(CDateYmdCtor, SecondOfJanuary1970IsNextDay)
{
	CDate d(2u, Month::JANUARY, 1970u);

	ASSERT_TRUE(d.IsValid());
	EXPECT_EQ(d.GetDay(), 2u);
	EXPECT_EQ(d.GetMonth(), Month::JANUARY);
	EXPECT_EQ(d.GetYear(), 1970u);
}

TEST(CDateYmdCtor, FirstOfMarch2024IsValid)
{
	CDate d(1u, Month::MARCH, 2024u);

	ASSERT_TRUE(d.IsValid());
	EXPECT_EQ(d.GetDay(), 1u);
	EXPECT_EQ(d.GetMonth(), Month::MARCH);
	EXPECT_EQ(d.GetYear(), 2024u);
}

TEST(CDateYmdCtor, LastDayOfYear9999IsValid)
{
	CDate d(31u, Month::DECEMBER, 9999u);

	ASSERT_TRUE(d.IsValid());
	EXPECT_EQ(d.GetDay(), 31u);
	EXPECT_EQ(d.GetMonth(), Month::DECEMBER);
	EXPECT_EQ(d.GetYear(), 9999u);
}

TEST(CDateYmdCtor, SeveralValidDatesRoundTrip)
{
	struct DateCase
	{
		unsigned day;
		Month month;
		unsigned year;
	};

	const DateCase cases[] = {
		{15u, Month::MARCH, 1970u},
		{29u, Month::FEBRUARY, 2024u},
		{1u, Month::JANUARY, 2000u},
		{28u, Month::FEBRUARY, 2023u},
		{31u, Month::DECEMBER, 9999u},
	};

	for (const auto& c : cases)
	{
		CDate d(c.day, c.month, c.year);
		ASSERT_TRUE(d.IsValid());
		EXPECT_EQ(d.GetDay(), c.day);
		EXPECT_EQ(d.GetMonth(), c.month);
		EXPECT_EQ(d.GetYear(), c.year);
	}
}

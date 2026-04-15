#include "../src/CDate.h"
#include <gtest/gtest.h>

TEST(CDateGettersFromTimestamp, EpochDate)
{
	CDate d(0u);

	ASSERT_TRUE(d.IsValid());
	EXPECT_EQ(d.GetDay(), 1u);
	EXPECT_EQ(d.GetMonth(), Month::JANUARY);
	EXPECT_EQ(d.GetYear(), 1970u);
}

TEST(CDateGettersFromTimestamp, FirstDayOfFebruary1970)
{
	CDate d(31u); 

	ASSERT_TRUE(d.IsValid());
	EXPECT_EQ(d.GetDay(), 1u);
	EXPECT_EQ(d.GetMonth(), Month::FEBRUARY);
	EXPECT_EQ(d.GetYear(), 1970u);
}

TEST(CDateGettersFromTimestamp, LeapDayFebruary2024)
{
	// 29.02.2024 relative to 01.01.1970
	CDate d(19782u);

	ASSERT_TRUE(d.IsValid());
	EXPECT_EQ(d.GetDay(), 29u);
	EXPECT_EQ(d.GetMonth(), Month::FEBRUARY);
	EXPECT_EQ(d.GetYear(), 2024u);
}

TEST(CDateGettersFromTimestamp, LastDayOfYear9999)
{
	// 31.12.9999 relative to 01.01.1970
	CDate d(2932896u);

	ASSERT_TRUE(d.IsValid());
	EXPECT_EQ(d.GetDay(), 31u);
	EXPECT_EQ(d.GetMonth(), Month::DECEMBER);
	EXPECT_EQ(d.GetYear(), 9999u);
}

TEST(CDateGettersFromTimestamp, RandomTimestampsHaveConsistentGetters)
{
	const unsigned samples[] = { 123u, 12345u, 543210u, 2000000u };

	for (unsigned ts : samples)
	{
		CDate d(ts);
		ASSERT_TRUE(d.IsValid());

		const unsigned day1 = d.GetDay();
		const Month month1 = d.GetMonth();
		const unsigned year1 = d.GetYear();

		// Consistency: repeated calls return the same values.
		EXPECT_EQ(d.GetDay(), day1);
		EXPECT_EQ(d.GetMonth(), month1);
		EXPECT_EQ(d.GetYear(), year1);

		// Basic sanity bounds.
		EXPECT_GE(day1, 1u);
		EXPECT_LE(day1, 31u);
		EXPECT_GE(static_cast<unsigned>(month1), 1u);
		EXPECT_LE(static_cast<unsigned>(month1), 12u);
		EXPECT_GE(year1, 1970u);
		EXPECT_LE(year1, 9999u);
	}
}

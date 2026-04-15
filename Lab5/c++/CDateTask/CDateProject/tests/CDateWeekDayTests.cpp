#include "../src/CDate.h"
#include <gtest/gtest.h>

TEST(CDateWeekDay, EpochIsThursday)
{
	CDate d(0u);

	ASSERT_TRUE(d.IsValid());
	EXPECT_EQ(d.GetWeekDay(), WeekDay::THURSDAY);
}

TEST(CDateWeekDay, FourthOfJanuary1970IsSunday)
{
	CDate d(3u); // 04.01.1970

	ASSERT_TRUE(d.IsValid());
	EXPECT_EQ(d.GetWeekDay(), WeekDay::SUNDAY);
}

TEST(CDateWeekDay, LeapDay2024IsThursday)
{
	CDate d(19782u); // 29.02.2024
	
	ASSERT_TRUE(d.IsValid());
	EXPECT_EQ(d.GetWeekDay(), WeekDay::THURSDAY);
}

TEST(CDateWeekDay, FirstOfJanuary2000IsSaturday)
{
	CDate d(10957u); // 01.01.2000

	ASSERT_TRUE(d.IsValid());
	EXPECT_EQ(d.GetWeekDay(), WeekDay::SATURDAY);
}

TEST(CDateWeekDay, InvalidDateReturnsThursdayByContract)
{
	CDate d(2932897u); // invalid timestamp (max is 2932896)

	ASSERT_FALSE(d.IsValid());
	EXPECT_EQ(d.GetWeekDay(), WeekDay::THURSDAY);
}

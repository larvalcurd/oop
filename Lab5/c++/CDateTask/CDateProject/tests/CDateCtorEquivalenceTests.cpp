#include "../src/CDate.h"
#include <gtest/gtest.h>

TEST(CDateCtorEquivalence, YmdAndTimestampAreEquivalentForEarlyEpochDates)
{
	CDate ymdEpoch(1u, Month::JANUARY, 1970u);
	CDate tsEpoch(0u);

	ASSERT_TRUE(ymdEpoch.IsValid());
	ASSERT_TRUE(tsEpoch.IsValid());
	EXPECT_EQ(ymdEpoch.GetDay(), tsEpoch.GetDay());
	EXPECT_EQ(ymdEpoch.GetMonth(), tsEpoch.GetMonth());
	EXPECT_EQ(ymdEpoch.GetYear(), tsEpoch.GetYear());

	CDate ymdNext(2u, Month::JANUARY, 1970u);
	CDate tsNext(1u);

	ASSERT_TRUE(ymdNext.IsValid());
	ASSERT_TRUE(tsNext.IsValid());
	EXPECT_EQ(ymdNext.GetDay(), tsNext.GetDay());
	EXPECT_EQ(ymdNext.GetMonth(), tsNext.GetMonth());
	EXPECT_EQ(ymdNext.GetYear(), tsNext.GetYear());
}

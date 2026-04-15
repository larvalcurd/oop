#include "../src/CDate.h"
#include <gtest/gtest.h>

namespace
{
constexpr unsigned kMaxTimestamp = 2932896u;
}

TEST(CDateTimestampCtor, Timestamp0IsValid)
{
	CDate date(0u);
	EXPECT_TRUE(date.IsValid());
}

TEST(CDateTimestampCtor, Timestamp1IsValid)
{
	CDate date(1u);
	EXPECT_TRUE(date.IsValid());
}

TEST(CDateTimestampCtor, Timestamp32IsValid)
{
	CDate date(32u);
	EXPECT_TRUE(date.IsValid());
}

TEST(CDateTimestampCtor, MaxTimestampIsValid)
{
	CDate date(kMaxTimestamp);
	EXPECT_TRUE(date.IsValid());
}

TEST(CDateTimestampCtor, TimestampAboveMaxIsInvalid)
{
	CDate date(kMaxTimestamp + 1u);
	EXPECT_FALSE(date.IsValid());
}

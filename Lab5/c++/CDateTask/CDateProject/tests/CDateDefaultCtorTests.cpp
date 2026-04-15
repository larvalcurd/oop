#include "../src/CDate.h"
#include <gtest/gtest.h>

TEST(CDateDefaultCtor, CreatesEpochDate)
{
	CDate date;
	EXPECT_TRUE(date.IsValid());
	EXPECT_EQ(date.GetDay(), 1u);
	EXPECT_EQ(date.GetMonth(), Month::JANUARY);
	EXPECT_EQ(date.GetYear(), 1970u);
}

TEST(CDateDefaultCtor, TwoDefaultObjectsAreEquivalent)
{
	CDate a;
	CDate b;

	EXPECT_EQ(a.IsValid(), b.IsValid());
	EXPECT_EQ(a.GetDay(), b.GetDay());
	EXPECT_EQ(a.GetMonth(), b.GetMonth());
	EXPECT_EQ(a.GetYear(), b.GetYear());
}

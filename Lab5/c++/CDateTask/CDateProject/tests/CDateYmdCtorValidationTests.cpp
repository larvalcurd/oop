#include "../src/CDate.h"
#include <gtest/gtest.h>

TEST(CDateYmdCtorValidation, April31IsInvalid)
{
	CDate d(31u, Month::APRIL, 2024u);
	EXPECT_FALSE(d.IsValid());
}

TEST(CDateYmdCtorValidation, February29InNonLeapYearIsInvalid)
{
	CDate d(29u, Month::FEBRUARY, 2023u);
	EXPECT_FALSE(d.IsValid());
}

TEST(CDateYmdCtorValidation, February29InLeapYearIsValid)
{
	CDate d(29u, Month::FEBRUARY, 2024u);
	EXPECT_TRUE(d.IsValid());
}

TEST(CDateYmdCtorValidation, YearBefore1970IsInvalid)
{
	CDate d(1u, Month::JANUARY, 1969u);
	EXPECT_FALSE(d.IsValid());
}

TEST(CDateYmdCtorValidation, Month13IsInvalid)
{
	CDate d(1u, static_cast<Month>(13), 2024u);
	EXPECT_FALSE(d.IsValid());
}

TEST(CDateYmdCtorValidation, DayZeroIsInvalid)
{
	CDate d(0u, Month::JANUARY, 2024u);
	EXPECT_FALSE(d.IsValid());
}

TEST(CDateYmdCtorValidation, MonthZeroIsInvalid)
{
	CDate d(1u, static_cast<Month>(0), 2024u);
	EXPECT_FALSE(d.IsValid());
}

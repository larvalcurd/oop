#include "../src/CDate.h"
#include <gtest/gtest.h>

namespace
{
void ExpectSameDate(const CDate& lhs, const CDate& rhs)
{
	ASSERT_EQ(lhs.IsValid(), rhs.IsValid());

	if (!lhs.IsValid())
	{
		return;
	}

	EXPECT_EQ(lhs.GetDay(), rhs.GetDay());
	EXPECT_EQ(lhs.GetMonth(), rhs.GetMonth());
	EXPECT_EQ(lhs.GetYear(), rhs.GetYear());
}
}

TEST(CDateFreeAdditionTests, DaysPlusDatePositive)
{
	CDate date(28, Month::FEBRUARY, 2010);

	CDate result = 3 + date;

	EXPECT_TRUE(result.IsValid());
	EXPECT_EQ(result.GetDay(), 3u);
	EXPECT_EQ(result.GetMonth(), Month::MARCH);
	EXPECT_EQ(result.GetYear(), 2010u);
}

TEST(CDateFreeAdditionTests, DaysPlusDateNegative)
{
	CDate date(1, Month::MARCH, 2024);

	CDate result = -1 + date;

	EXPECT_TRUE(result.IsValid());
	EXPECT_EQ(result.GetDay(), 29u);
	EXPECT_EQ(result.GetMonth(), Month::FEBRUARY);
	EXPECT_EQ(result.GetYear(), 2024u);
}

TEST(CDateFreeAdditionTests, DaysPlusInvalidDateIsInvalid)
{
	CDate invalid(32, Month::JANUARY, 2024);

	CDate result = 10 + invalid;

	EXPECT_FALSE(result.IsValid());
}

TEST(CDateFreeAdditionTests, FreeAdditionMatchesMemberAddition)
{
	const int shifts[] = { -400, -1, 0, 1, 3, 30, 365, 1000 };

	const CDate dates[] = {
		CDate(1, Month::JANUARY, 1970),
		CDate(28, Month::FEBRUARY, 2010),
		CDate(1, Month::MARCH, 2024),
		CDate(31, Month::DECEMBER, 9999),
	};

	for (const CDate& date : dates)
	{
		for (int shift : shifts)
		{
			ExpectSameDate(date + shift, shift + date);
		}
	}
}

TEST(CDateFreeAdditionTests, BoundaryMatchesMemberAddition)
{
	CDate date1(31, Month::DECEMBER, 9999);
	ExpectSameDate(date1 + 1, 1 + date1);

	CDate date2(1, Month::JANUARY, 1970);
	ExpectSameDate(date2 + (-1), -1 + date2);
}

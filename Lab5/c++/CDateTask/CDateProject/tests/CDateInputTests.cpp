#include "CDate.h"
#include <gtest/gtest.h>
#include <sstream>

TEST(CDateInputTests, ReadsValidDate)
{
	std::istringstream in("01.01.1970");
	CDate date;

	in >> date;

	EXPECT_FALSE(in.fail());
	EXPECT_TRUE(date.IsValid());
	EXPECT_EQ(date.GetDay(), 1u);
	EXPECT_EQ(date.GetMonth(), Month::JANUARY);
	EXPECT_EQ(date.GetYear(), 1970u);
}

TEST(CDateInputTests, ReadsInvalidLiteral)
{
	std::istringstream in("INVALID");
	CDate date;

	in >> date;

	EXPECT_FALSE(in.fail());
	EXPECT_FALSE(date.IsValid());
}

TEST(CDateInputTests, ReadsSemanticallyInvalidDate)
{
	std::istringstream in("31.04.2024");
	CDate date;

	in >> date;

	EXPECT_TRUE(in.fail());
	EXPECT_FALSE(date.IsValid());
}

TEST(CDateInputTests, StrictFormatRejectsSingleDigitDayAndMonth)
{
	std::istringstream in("1.1.1970");
	CDate date(2, Month::FEBRUARY, 2000); 

	in >> date;

	EXPECT_TRUE(in.fail());
	EXPECT_TRUE(date.IsValid());
	EXPECT_EQ(date.GetDay(), 2u);
	EXPECT_EQ(date.GetMonth(), Month::FEBRUARY);
	EXPECT_EQ(date.GetYear(), 2000u);
}

TEST(CDateInputTests, WrongSeparatorSetsFailbitAndKeepsObjectUnchanged)
{
	std::istringstream in("01-01-1970");
	CDate date(2, Month::FEBRUARY, 2000);

	in >> date;

	EXPECT_TRUE(in.fail());
	EXPECT_TRUE(date.IsValid());
	EXPECT_EQ(date.GetDay(), 2u);
	EXPECT_EQ(date.GetMonth(), Month::FEBRUARY);
	EXPECT_EQ(date.GetYear(), 2000u);
}

TEST(CDateInputTests, GarbageSetsFailbitAndKeepsObjectUnchanged)
{
	std::istringstream in("abc");
	CDate date(2, Month::FEBRUARY, 2000);

	in >> date;

	EXPECT_TRUE(in.fail());
	EXPECT_TRUE(date.IsValid());
	EXPECT_EQ(date.GetDay(), 2u);
	EXPECT_EQ(date.GetMonth(), Month::FEBRUARY);
	EXPECT_EQ(date.GetYear(), 2000u);
}
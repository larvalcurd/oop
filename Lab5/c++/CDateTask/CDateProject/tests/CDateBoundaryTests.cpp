#include "CDate.h"
#include <gtest/gtest.h>
#include <sstream>

namespace
{
void ExpectInvalid(const CDate& d)
{
	EXPECT_FALSE(d.IsValid());
	EXPECT_EQ(d.GetDay(), 0u);
	EXPECT_EQ(d.GetMonth(), Month::JANUARY);
	EXPECT_EQ(d.GetYear(), 0u);
}
} // namespace

TEST(CDateBoundaryTests, UpperBoundaryMutationsBecomeInvalid)
{
	CDate d1(31, Month::DECEMBER, 9999);
	CDate d2(31, Month::DECEMBER, 9999);
	CDate d3(31, Month::DECEMBER, 9999);

	++d1;
	d2 += 1;
	CDate r = d3 + 1;

	ExpectInvalid(d1);
	ExpectInvalid(d2);
	ExpectInvalid(r);
}

TEST(CDateBoundaryTests, LowerBoundaryMutationsBecomeInvalid)
{
	CDate d1(1, Month::JANUARY, 1970);
	CDate d2(1, Month::JANUARY, 1970);
	CDate d3(1, Month::JANUARY, 1970);

	--d1;
	d2 -= 1;
	CDate r = d3 - 1;

	ExpectInvalid(d1);
	ExpectInvalid(d2);
	ExpectInvalid(r);
}

TEST(CDateInvalidTests, InvalidStaysInvalidAfterMutations)
{
	CDate d1(32, Month::JANUARY, 2024);
	CDate d2(32, Month::JANUARY, 2024);
	CDate d3(32, Month::JANUARY, 2024);
	CDate d4(32, Month::JANUARY, 2024);
	CDate d5(32, Month::JANUARY, 2024);
	CDate d6(32, Month::JANUARY, 2024);

	++d1;
	--d2;
	d3 += 10;
	d4 -= 10;

	CDate r1 = d5 + 10;
	CDate r2 = d6 - 10;

	ExpectInvalid(d1);
	ExpectInvalid(d2);
	ExpectInvalid(d3);
	ExpectInvalid(d4);
	ExpectInvalid(r1);
	ExpectInvalid(r2);
}

TEST(CDateInvalidTests, InvalidComparisonPolicyIsStable)
{
	CDate a(32, Month::JANUARY, 2024);
	CDate b(0, Month::FEBRUARY, 2020);
	CDate valid(1, Month::JANUARY, 2010);

	EXPECT_TRUE(a == b);
	EXPECT_FALSE(a != b);

	EXPECT_FALSE(a < b);
	EXPECT_FALSE(a > b);
	EXPECT_TRUE(a <= b);
	EXPECT_TRUE(a >= b);

	EXPECT_FALSE(a == valid);
	EXPECT_TRUE(a != valid);
	EXPECT_FALSE(a < valid);
	EXPECT_FALSE(a > valid);
	EXPECT_FALSE(a <= valid);
	EXPECT_FALSE(a >= valid);
}

TEST(CDateOutputTests, InvalidPrintsINVALID)
{
	CDate d(32, Month::JANUARY, 2024);

	std::ostringstream out;
	out << d;

	EXPECT_EQ(out.str(), "INVALID");
}
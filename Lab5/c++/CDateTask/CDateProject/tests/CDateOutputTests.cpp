#include <gtest/gtest.h>
#include <sstream>
#include "CDate.h"

TEST(CDateOutputTests, PrintsValidDateWithLeadingZeros)
{
    CDate date(1, Month::JANUARY, 1970);

    std::ostringstream out;
    out << date;

    EXPECT_EQ(out.str(), "01.01.1970");
}

TEST(CDateOutputTests, PrintsAnotherValidDateWithLeadingZeros)
{
    CDate date(9, Month::FEBRUARY, 2024);

    std::ostringstream out;
    out << date;

    EXPECT_EQ(out.str(), "09.02.2024");
}

TEST(CDateOutputTests, PrintsInvalidAsInvalid)
{
    CDate date(32, Month::JANUARY, 2024);

    std::ostringstream out;
    out << date;

    EXPECT_EQ(out.str(), "INVALID");
}

TEST(CDateOutputTests, PrintsSeveralDatesWithoutArtifacts)
{
    CDate a(1, Month::JANUARY, 1970);
    CDate b(9, Month::FEBRUARY, 2024);
    CDate c(32, Month::JANUARY, 2024);

    std::ostringstream out;
    out << a << '|' << b << '|' << c;

    EXPECT_EQ(out.str(), "01.01.1970|09.02.2024|INVALID");
}
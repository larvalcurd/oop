#include <gtest/gtest.h>
#include "../src/CMyString.h"

TEST(ComparisonTests, OperatorEqual_SameStrings_ReturnsTrue)
{
    CMyString s1("Hello");
    CMyString s2("Hello");
    EXPECT_TRUE(s1 == s2);
    EXPECT_FALSE(s1 != s2);
}

TEST(ComparisonTests, OperatorEqual_DifferentStrings_ReturnsFalse)
{
    CMyString s1("Hello");
    CMyString s2("World");
    EXPECT_FALSE(s1 == s2);
    EXPECT_TRUE(s1 != s2);
}

TEST(ComparisonTests, OperatorLess_LexicographicalOrder_ReturnsCorrect)
{
    CMyString a("abc");
    CMyString b("abd");
    EXPECT_TRUE(a < b);
    EXPECT_TRUE(a <= b);
    EXPECT_FALSE(a > b);
    EXPECT_FALSE(a >= b);
}

TEST(ComparisonTests, OperatorLess_ShorterPrefix_ReturnsTrue)
{
    CMyString a("abc");
    CMyString b("abcd");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(ComparisonTests, OperatorLess_EmbeddedNulls_ComparesCorrectly)
{
    const char raw1[] = {'a', '\0', 'c'}; 
    const char raw2[] = {'a', '\0', 'd'}; 
    CMyString s1(raw1, 3);
    CMyString s2(raw2, 3);

    EXPECT_TRUE(s1 < s2);
    EXPECT_FALSE(s1 == s2);
    EXPECT_TRUE(s1 != s2);
}

TEST(ComparisonTests, OperatorLess_EmbeddedNullVsNoNull_ComparesAtFirstDifference)
{
    const char raw1[] = {'a', '\0', 'c'}; 
    CMyString s1(raw1, 3);
    CMyString s2("abc"); 

    EXPECT_TRUE(s1 < s2);
}

TEST(ComparisonTests, OperatorGreater_Works)
{
    CMyString a("xyz");
    CMyString b("abc");
    EXPECT_TRUE(a > b);
    EXPECT_TRUE(a >= b);
    EXPECT_FALSE(a < b);
}

TEST(ComparisonTests, OperatorEqual_EmptyStrings_ReturnsTrue)
{
    CMyString e1;
    CMyString e2;
    EXPECT_TRUE(e1 == e2);
    EXPECT_FALSE(e1 != e2);
    EXPECT_FALSE(e1 < e2);
    EXPECT_TRUE(e1 <= e2);
}

TEST(ComparisonTests, EqualStrings_AllComparisonOperatorsWorkCorrectly)
{
    CMyString s1("Hello");
    CMyString s2("Hello");

    EXPECT_TRUE(s1 == s2);
    EXPECT_FALSE(s1 != s2);
    EXPECT_FALSE(s1 < s2);
    EXPECT_TRUE(s1 <= s2);
    EXPECT_FALSE(s1 > s2);
    EXPECT_TRUE(s1 >= s2);
}

TEST(ComparisonTests, EmptyAndNonEmptyStrings_CompareCorrectly)
{
    CMyString empty;
    CMyString nonEmpty("a");

    EXPECT_TRUE(empty < nonEmpty);
    EXPECT_TRUE(empty <= nonEmpty);
    EXPECT_FALSE(empty > nonEmpty);
    EXPECT_FALSE(empty >= nonEmpty);

    EXPECT_TRUE(nonEmpty > empty);
    EXPECT_TRUE(nonEmpty >= empty);
    EXPECT_FALSE(nonEmpty < empty);
    EXPECT_FALSE(nonEmpty <= empty);
}

TEST(ComparisonTests, OperatorEqual_EmbeddedNullsEqualStrings_ReturnsTrue)
{
    const char raw1[] = {'a', '\0', 'c'};
    const char raw2[] = {'a', '\0', 'c'};

    CMyString s1(raw1, 3);
    CMyString s2(raw2, 3);

    EXPECT_TRUE(s1 == s2);
    EXPECT_FALSE(s1 != s2);
    EXPECT_FALSE(s1 < s2);
    EXPECT_TRUE(s1 <= s2);
    EXPECT_FALSE(s1 > s2);
    EXPECT_TRUE(s1 >= s2);
}

TEST(ComparisonTests, OperatorGreater_WhenOneStringIsLongerWithSamePrefix)
{
    CMyString a("abc");
    CMyString b("abcd");

    EXPECT_TRUE(a < b);
    EXPECT_TRUE(a <= b);
    EXPECT_FALSE(a > b);
    EXPECT_FALSE(a >= b);

    EXPECT_TRUE(b > a);
    EXPECT_TRUE(b >= a);
    EXPECT_FALSE(b < a);
    EXPECT_FALSE(b <= a);
}

TEST(ComparisonTests, OperatorLess_UsesUnsignedCharComparison)
{
    const char raw1[] = { static_cast<char>(200) };
    const char raw2[] = { static_cast<char>(100) };

    CMyString s1(raw1, 1);
    CMyString s2(raw2, 1);

    EXPECT_TRUE(s1 > s2);
    EXPECT_FALSE(s1 < s2);
}
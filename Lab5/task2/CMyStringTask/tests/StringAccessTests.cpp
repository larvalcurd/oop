#include <gtest/gtest.h>
#include "../src/CMyString.h"
#include <stdexcept>

TEST(StringAccessTests, NonConstOperatorIndex_ReturnsCorrectCharacters)
{
    CMyString s("Hello");

    EXPECT_EQ(s[0], 'H');
    EXPECT_EQ(s[1], 'e');
    EXPECT_EQ(s[2], 'l');
    EXPECT_EQ(s[3], 'l');
    EXPECT_EQ(s[4], 'o');
}

TEST(StringAccessTests, NonConstOperatorIndex_AllowsModification)
{
    CMyString s("Hello");

    s[0] = 'Y';
    s[4] = '!';

    EXPECT_EQ(s[0], 'Y');
    EXPECT_EQ(s[4], '!');
    EXPECT_STREQ(s.GetStringData(), "Yell!");
}

TEST(StringAccessTests, ConstOperatorIndex_ReturnsCorrectCharacters)
{
    const CMyString s("World");

    EXPECT_EQ(s[0], 'W');
    EXPECT_EQ(s[1], 'o');
    EXPECT_EQ(s[2], 'r');
    EXPECT_EQ(s[3], 'l');
    EXPECT_EQ(s[4], 'd');
}

TEST(StringAccessTests, OperatorIndex_FirstAndLastCharacter_AccessWorks)
{
    CMyString s("abcde");

    EXPECT_EQ(s[0], 'a');
    EXPECT_EQ(s[4], 'e');
}

TEST(StringAccessTests, OperatorIndex_IndexEqualToLength_Throws)
{
    CMyString s("Hello");

    EXPECT_THROW(s[5], std::out_of_range);
}

TEST(StringAccessTests, OperatorIndex_IndexGreaterThanLength_Throws)
{
    CMyString s("Hello");

    EXPECT_THROW(s[100], std::out_of_range);
}

TEST(StringAccessTests, OperatorIndex_EmptyString_Throws)
{
    CMyString s;

    EXPECT_THROW(s[0], std::out_of_range);
}

TEST(StringAccessTests, OperatorIndex_ConstEmptyString_Throws)
{
    const CMyString s;

    EXPECT_THROW(s[0], std::out_of_range);
}

TEST(StringAccessTests, OperatorIndex_EmbeddedNull_AccessWorksCorrectly)
{
    const char raw[] = { 'A', '\0', 'B' };
    CMyString s(raw, 3);

    EXPECT_EQ(s[0], 'A');
    EXPECT_EQ(s[1], '\0');
    EXPECT_EQ(s[2], 'B');
}

TEST(StringAccessTests, OperatorIndex_EmbeddedNull_CanBeModified)
{
    const char raw[] = { 'A', '\0', 'B' };
    CMyString s(raw, 3);

    s[1] = 'X';

    EXPECT_EQ(s[0], 'A');
    EXPECT_EQ(s[1], 'X');
    EXPECT_EQ(s[2], 'B');
    EXPECT_EQ(s.GetLength(), 3u);
}
#include <gtest/gtest.h>
#include "../src/CMyString.h"

TEST(SubstringTests, Substring_FromBeginningWithExactLength_ReturnsCorrectString)
{
    CMyString s("Hello");

    CMyString sub = s.Substring(0, 5);

    EXPECT_EQ(sub.GetLength(), 5u);
    EXPECT_STREQ(sub.GetStringData(), "Hello");
}

TEST(SubstringTests, Substring_FromBeginningWithSmallerLength_ReturnsPrefix)
{
    CMyString s("Hello");

    CMyString sub = s.Substring(0, 2);

    EXPECT_EQ(sub.GetLength(), 2u);
    EXPECT_STREQ(sub.GetStringData(), "He");
}

TEST(SubstringTests, Substring_FromMiddleWithExactLength_ReturnsCorrectPart)
{
    CMyString s("Hello");

    CMyString sub = s.Substring(1, 3);

    EXPECT_EQ(sub.GetLength(), 3u);
    EXPECT_STREQ(sub.GetStringData(), "ell");
}

TEST(SubstringTests, Substring_FromMiddleToEnd_WhenLengthIsTooBig_ReturnsTail)
{
    CMyString s("Hello");

    CMyString sub = s.Substring(2, 100);

    EXPECT_EQ(sub.GetLength(), 3u);
    EXPECT_STREQ(sub.GetStringData(), "llo");
}

TEST(SubstringTests, Substring_WithoutLengthArgument_ReturnsTail)
{
    CMyString s("Hello");

    CMyString sub = s.Substring(2);

    EXPECT_EQ(sub.GetLength(), 3u);
    EXPECT_STREQ(sub.GetStringData(), "llo");
}

TEST(SubstringTests, Substring_ZeroLength_ReturnsEmptyString)
{
    CMyString s("Hello");

    CMyString sub = s.Substring(2, 0);

    EXPECT_EQ(sub.GetLength(), 0u);
    EXPECT_EQ(sub.GetCapacity(), 0u);
    ASSERT_NE(sub.GetStringData(), nullptr);
    EXPECT_EQ(sub.GetStringData()[0], '\0');
}

TEST(SubstringTests, Substring_StartAtEnd_ReturnsEmptyString)
{
    CMyString s("Hello");

    CMyString sub = s.Substring(5, 3);

    EXPECT_EQ(sub.GetLength(), 0u);
    EXPECT_EQ(sub.GetCapacity(), 0u);
    ASSERT_NE(sub.GetStringData(), nullptr);
    EXPECT_EQ(sub.GetStringData()[0], '\0');
}

TEST(SubstringTests, Substring_StartPastEnd_ReturnsEmptyString)
{
    CMyString s("Hello");

    CMyString sub = s.Substring(10, 3);

    EXPECT_EQ(sub.GetLength(), 0u);
    EXPECT_EQ(sub.GetCapacity(), 0u);
    ASSERT_NE(sub.GetStringData(), nullptr);
    EXPECT_EQ(sub.GetStringData()[0], '\0');
}

TEST(SubstringTests, Substring_OnEmptyString_ReturnsEmptyString)
{
    CMyString s;

    CMyString sub = s.Substring(0, 5);

    EXPECT_EQ(sub.GetLength(), 0u);
    EXPECT_EQ(sub.GetCapacity(), 0u);
    ASSERT_NE(sub.GetStringData(), nullptr);
    EXPECT_EQ(sub.GetStringData()[0], '\0');
}

TEST(SubstringTests, Substring_SingleCharacter_ReturnsCorrectString)
{
    CMyString s("Hello");

    CMyString sub = s.Substring(1, 1);

    EXPECT_EQ(sub.GetLength(), 1u);
    EXPECT_STREQ(sub.GetStringData(), "e");
}

TEST(SubstringTests, Substring_EmbeddedNulls_PreservesAllCharacters)
{
    const char raw[] = { 'A', '\0', 'B', 'C', '\0', 'D' };
    CMyString s(raw, 6);

    CMyString sub = s.Substring(1, 4); // '\0', 'B', 'C', '\0'

    EXPECT_EQ(sub.GetLength(), 4u);

    const char* data = sub.GetStringData();
    ASSERT_NE(data, nullptr);

    EXPECT_EQ(data[0], '\0');
    EXPECT_EQ(data[1], 'B');
    EXPECT_EQ(data[2], 'C');
    EXPECT_EQ(data[3], '\0');
    EXPECT_EQ(data[4], '\0'); // завершающий ноль
}

TEST(SubstringTests, Substring_ResultIsIndependentFromSource)
{
    CMyString s("Hello");
    CMyString sub = s.Substring(1, 3); // "ell"

    s[1] = 'A';

    EXPECT_STREQ(sub.GetStringData(), "ell");
    EXPECT_STREQ(s.GetStringData(), "HAllo");
}

TEST(SubstringTests, Substring_FullStringWithoutLengthArgument_ReturnsWholeString)
{
    CMyString s("Hello");

    CMyString sub = s.Substring(0);

    EXPECT_EQ(sub.GetLength(), 5u);
    EXPECT_STREQ(sub.GetStringData(), "Hello");
}
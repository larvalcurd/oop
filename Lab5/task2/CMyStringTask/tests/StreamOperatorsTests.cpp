#include <gtest/gtest.h>
#include "../src/CMyString.h"

#include <sstream>
#include <string>

TEST(OutputOperatorTests, WritesRegularString)
{
    CMyString str("Hello");
    std::ostringstream output;

    output << str;

    EXPECT_EQ(output.str(), "Hello");
}

TEST(OutputOperatorTests, WritesEmptyString)
{
    CMyString str;
    std::ostringstream output;

    output << str;

    EXPECT_TRUE(output.str().empty());
}

TEST(OutputOperatorTests, WritesStringWithEmbeddedNulls)
{
    const char raw[] = { 'A', '\0', 'B', 'C' };
    CMyString str(raw, 4);
    std::ostringstream output;

    output << str;

    std::string result = output.str();
    ASSERT_EQ(result.size(), 4u);
    EXPECT_EQ(result[0], 'A');
    EXPECT_EQ(result[1], '\0');
    EXPECT_EQ(result[2], 'B');
    EXPECT_EQ(result[3], 'C');
}

TEST(OutputOperatorTests, WritesExactlyLengthCharacters)
{
    const char raw[] = { 'X', '\0', 'Y' };
    CMyString str(raw, 3);
    std::ostringstream output;

    output << str;

    std::string result = output.str();
    EXPECT_EQ(result.size(), 3u);
}

TEST(OutputOperatorTests, SupportsChainedOutput)
{
    CMyString first("Hello");
    CMyString second("World");
    std::ostringstream output;

    output << first << ' ' << second;

    EXPECT_EQ(output.str(), "Hello World");
}

TEST(InputOperatorTests, ReadsSingleWord)
{
    std::istringstream input("Hello");
    CMyString str;

    input >> str;

    EXPECT_TRUE(input.good() || input.eof());
    EXPECT_EQ(str.GetLength(), 5u);
    EXPECT_STREQ(str.GetStringData(), "Hello");
}

TEST(InputOperatorTests, SkipsLeadingWhitespace)
{
    std::istringstream input("   \t\nHello");
    CMyString str;

    input >> str;

    EXPECT_EQ(str.GetLength(), 5u);
    EXPECT_STREQ(str.GetStringData(), "Hello");
}

TEST(InputOperatorTests, StopsAtWhitespace)
{
    std::istringstream input("Hello World");
    CMyString str;

    input >> str;

    EXPECT_EQ(str.GetLength(), 5u);
    EXPECT_STREQ(str.GetStringData(), "Hello");
}

TEST(InputOperatorTests, ReadsMultipleWordsSequentially)
{
    std::istringstream input("Hello World Test");
    CMyString first;
    CMyString second;
    CMyString third;

    input >> first >> second >> third;

    EXPECT_STREQ(first.GetStringData(), "Hello");
    EXPECT_STREQ(second.GetStringData(), "World");
    EXPECT_STREQ(third.GetStringData(), "Test");
}

TEST(InputOperatorTests, ReadsUntilEndOfFileIfNoTrailingWhitespace)
{
    std::istringstream input("Hello");
    CMyString str;

    input >> str;

    EXPECT_EQ(str.GetLength(), 5u);
    EXPECT_STREQ(str.GetStringData(), "Hello");
    EXPECT_TRUE(input.good() || input.eof());
}

TEST(InputOperatorTests, ReadingFromEmptyStreamFails)
{
    std::istringstream input("");
    CMyString str("OldValue");

    input >> str;

    EXPECT_TRUE(input.fail());
    EXPECT_STREQ(str.GetStringData(), "OldValue");
}

TEST(InputOperatorTests, ReadingFromWhitespaceOnlyStreamFails)
{
    std::istringstream input("    \t\n   ");
    CMyString str("OldValue");

    input >> str;

    EXPECT_TRUE(input.fail());
    EXPECT_STREQ(str.GetStringData(), "OldValue");
}

TEST(InputOperatorTests, FailedReadDoesNotModifyString)
{
    std::istringstream input("");
    CMyString str("KeepMe");

    input >> str;

    EXPECT_TRUE(input.fail());
    EXPECT_STREQ(str.GetStringData(), "KeepMe");
}

TEST(InputOperatorTests, SecondReadFailsAtEndAndDoesNotModifyTarget)
{
    std::istringstream input("Hello");
    CMyString first;
    CMyString second("OldValue");

    input >> first;
    input >> second;

    EXPECT_STREQ(first.GetStringData(), "Hello");
    EXPECT_TRUE(input.fail());
    EXPECT_STREQ(second.GetStringData(), "OldValue");
}

TEST(InputOperatorTests, SupportsChainedInput)
{
    std::istringstream input("One Two");
    CMyString first;
    CMyString second;

    input >> first >> second;

    EXPECT_STREQ(first.GetStringData(), "One");
    EXPECT_STREQ(second.GetStringData(), "Two");
}

TEST(InputOperatorTests, ReadsSingleCharacterWord)
{
    std::istringstream input("A");
    CMyString str;

    input >> str;

    EXPECT_EQ(str.GetLength(), 1u);
    EXPECT_STREQ(str.GetStringData(), "A");
}

TEST(InputOperatorTests, ReplacesPreviousValueOnSuccessfulRead)
{
    std::istringstream input("NewValue");
    CMyString str("OldValue");

    input >> str;

    EXPECT_STREQ(str.GetStringData(), "NewValue");
    EXPECT_EQ(str.GetLength(), 8u);
}

TEST(InputOperatorTests, ReadsTokenContainingEmbeddedNullFromStringStream)
{
    std::string source;
    source.push_back('A');
    source.push_back('\0');
    source.push_back('B');
    source.push_back(' ');
    source.push_back('C');

    std::istringstream input(source);
    CMyString str;

    input >> str;

    ASSERT_EQ(str.GetLength(), 3u);
    EXPECT_EQ(str[0], 'A');
    EXPECT_EQ(str[1], '\0');
    EXPECT_EQ(str[2], 'B');
}

TEST(InputOperatorTests, AfterReadingFirstTokenNextExtractionReadsNextToken)
{
    std::istringstream input("abc def");
    CMyString first;
    CMyString second;

    input >> first;
    input >> second;

    EXPECT_STREQ(first.GetStringData(), "abc");
    EXPECT_STREQ(second.GetStringData(), "def");
}
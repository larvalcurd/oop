#include "ArgsParser.h"
#include <gtest/gtest.h>

class ParseArgsTest : public ::testing::Test
{
protected:
	std::optional<Args> CallParseArgs(std::vector<std::string>& args)
	{
		std::vector<char*> argv;
		for (auto& arg : args)
		{
			argv.push_back(arg.data());
		}
		return ParseArgs(static_cast<int>(argv.size()), argv.data());
	}
};

TEST_F(ParseArgsTest, ReturnsNulloptWhenNoArguments)
{
	std::vector<std::string> args = { "program" };

	std::optional<Args> result = CallParseArgs(args);

	EXPECT_FALSE(result.has_value());
}

TEST_F(ParseArgsTest, ReturnsNulloptWhenTooManyArguments)
{
	std::vector<std::string> args = { "program", "100", "extra" };

	std::optional<Args> result = CallParseArgs(args);

	EXPECT_FALSE(result.has_value());
}

TEST_F(ParseArgsTest, ParsesValidPositiveNumber)
{
	std::vector<std::string> args = { "program", "100" };

	std::optional<Args> result = CallParseArgs(args);

	ASSERT_TRUE(result.has_value());
	EXPECT_EQ(result->upperBound, 100);
}

TEST_F(ParseArgsTest, ParsesMaxUpperBound)
{
	std::vector<std::string> args = { "program", "100000000" };

	std::optional<Args> result = CallParseArgs(args);

	ASSERT_TRUE(result.has_value());
	EXPECT_EQ(result->upperBound, 100000000);
}

TEST_F(ParseArgsTest, ReturnsNulloptForZero)
{
	std::vector<std::string> args = { "program", "0" };

	std::optional<Args> result = CallParseArgs(args);

	EXPECT_FALSE(result.has_value());
}

TEST_F(ParseArgsTest, ReturnsNulloptForNegativeNumber)
{
	std::vector<std::string> args = { "program", "-5" };

	std::optional<Args> result = CallParseArgs(args);

	EXPECT_FALSE(result.has_value());
}

TEST_F(ParseArgsTest, ReturnsNulloptWhenExceedsMaxUpperBound)
{
	std::vector<std::string> args = { "program", "100000001" };

	std::optional<Args> result = CallParseArgs(args);

	EXPECT_FALSE(result.has_value());
}

TEST_F(ParseArgsTest, ReturnsNulloptForNonNumericInput)
{
	std::vector<std::string> args = { "program", "abc" };

	std::optional<Args> result = CallParseArgs(args);

	EXPECT_FALSE(result.has_value());
}

TEST_F(ParseArgsTest, ReturnsNulloptForMixedInput)
{
	std::vector<std::string> args = { "program", "123abc" };

	std::optional<Args> result = CallParseArgs(args);

	EXPECT_FALSE(result.has_value());
}

TEST_F(ParseArgsTest, ReturnsNulloptForFloatingPointInput)
{
	std::vector<std::string> args = { "program", "3.14" };

	std::optional<Args> result = CallParseArgs(args);

	EXPECT_FALSE(result.has_value());
}

TEST_F(ParseArgsTest, ReturnsNulloptForEmptyString)
{
	std::vector<std::string> args = { "program", "" };

	std::optional<Args> result = CallParseArgs(args);

	EXPECT_FALSE(result.has_value());
}

TEST_F(ParseArgsTest, ParsesMinValidValue)
{
	std::vector<std::string> args = { "program", "1" };

	std::optional<Args> result = CallParseArgs(args);

	ASSERT_TRUE(result.has_value());
	EXPECT_EQ(result->upperBound, 1);
}

TEST_F(ParseArgsTest, HandlesLeadingZeros)
{
	std::vector<std::string> args = { "program", "007" };

	std::optional<Args> result = CallParseArgs(args);

	ASSERT_TRUE(result.has_value());
	EXPECT_EQ(result->upperBound, 7);
}

TEST_F(ParseArgsTest, ReturnsNulloptForWhitespaceInput)
{
	std::vector<std::string> args = { "program", "   " };

	std::optional<Args> result = CallParseArgs(args);

	EXPECT_FALSE(result.has_value());
}

TEST_F(ParseArgsTest, ReturnsNulloptForNumberWithSpaces)
{
	std::vector<std::string> args = { "program", "1 00" };

	std::optional<Args> result = CallParseArgs(args);

	EXPECT_FALSE(result.has_value());
}
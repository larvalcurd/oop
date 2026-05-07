#include "../src/CMyString.h"

#include <algorithm>
#include <iterator>
#include <string>
#include <type_traits>

#include <gtest/gtest.h>

TEST(CMyStringIteratorTests, BeginPointsToFirstCharacter)
{
	CMyString str("abc");

	auto it = str.begin();

	EXPECT_EQ(*it, 'a');
}

TEST(CMyStringIteratorTests, EndIsAtDistanceEqualToLength)
{
	CMyString str("abcde");

	EXPECT_EQ(str.end() - str.begin(), 5);
}

TEST(CMyStringIteratorTests, ConstBeginReturnsConstIterator)
{
	const CMyString str("abc");

	auto it = str.begin();

	static_assert(std::is_same_v<decltype(it), CMyString::ConstIterator>);
	EXPECT_EQ(*it, 'a');
}

TEST(CMyStringIteratorTests, CBeginAndCEndReturnConstIterators)
{
	CMyString str("abc");

	auto begin = str.cbegin();
	auto end = str.cend();

	static_assert(std::is_same_v<decltype(begin), CMyString::ConstIterator>);
	static_assert(std::is_same_v<decltype(end), CMyString::ConstIterator>);
	EXPECT_EQ(end - begin, 3);
	EXPECT_EQ(*begin, 'a');
}

TEST(CMyStringIteratorTests, NonConstBeginAllowsChangingString)
{
	CMyString str("abc");

	*str.begin() = 'x';

	EXPECT_EQ(str[0], 'x');
	EXPECT_STREQ(str.GetStringData(), "xbc");
}

TEST(CMyStringIteratorTests, RangeBasedForReadsCharactersInForwardOrder)
{
	CMyString str("abc");

	std::string collected;
	for (char ch : str)
	{
		collected += ch;
	}

	EXPECT_EQ(collected, "abc");
}

TEST(CMyStringIteratorTests, RangeBasedForAllowsModificationOfNonConstString)
{
	CMyString str("abc");

	for (char& ch : str)
	{
		ch = static_cast<char>(ch - 'a' + 'A');
	}

	EXPECT_STREQ(str.GetStringData(), "ABC");
}

TEST(CMyStringIteratorTests, RangeBasedForWorksForConstString)
{
	const CMyString str("abc");

	std::string collected;
	for (const char& ch : str)
	{
		collected += ch;
	}

	EXPECT_EQ(collected, "abc");
}

TEST(CMyStringIteratorTests, RBeginIteratesFromLastCharacter)
{
	CMyString str("abc");

	auto it = str.rbegin();

	EXPECT_EQ(*it, 'c');
}

TEST(CMyStringIteratorTests, ReverseIterationBuildsReversedSequence)
{
	CMyString str("abcd");

	std::string collected;
	for (auto it = str.rbegin(); it != str.rend(); ++it)
	{
		collected += *it;
	}

	EXPECT_EQ(collected, "dcba");
}

TEST(CMyStringIteratorTests, ConstReverseIterationWorks)
{
	const CMyString str("abcd");

	std::string collected;
	for (auto it = str.rbegin(); it != str.rend(); ++it)
	{
		collected += *it;
	}

	EXPECT_EQ(collected, "dcba");
}

TEST(CMyStringIteratorTests, CRBeginAndCREndWork)
{
	const CMyString str("xyz");

	auto it = str.crbegin();

	static_assert(std::is_same_v<decltype(it), CMyString::ConstReverseIterator>);
	EXPECT_EQ(*it, 'z');

	std::string collected;
	for (auto current = str.crbegin(); current != str.crend(); ++current)
	{
		collected += *current;
	}

	EXPECT_EQ(collected, "zyx");
}

TEST(CMyStringIteratorTests, EmptyStringHasBeginEqualToEnd)
{
	CMyString str;

	EXPECT_EQ(str.begin(), str.end());
	EXPECT_EQ(str.cbegin(), str.cend());
}

TEST(CMyStringIteratorTests, EmptyStringHasRBeginEqualToREnd)
{
	CMyString str;

	EXPECT_EQ(str.rbegin(), str.rend());
	EXPECT_EQ(str.crbegin(), str.crend());
}

TEST(CMyStringIteratorTests, StdFindWorksWithStringIterators)
{
	CMyString str("abcde");

	auto it = std::find(str.begin(), str.end(), 'c');

	ASSERT_NE(it, str.end());
	EXPECT_EQ(*it, 'c');
}

TEST(CMyStringIteratorTests, StdFindWorksWithConstStringIterators)
{
	const CMyString str("abcde");

	auto it = std::find(str.cbegin(), str.cend(), 'd');

	ASSERT_NE(it, str.cend());
	EXPECT_EQ(*it, 'd');
}

TEST(CMyStringIteratorTests, StdSortWorksWithMutableStringIterators)
{
	CMyString str("dbca");

	std::sort(str.begin(), str.end());

	EXPECT_STREQ(str.GetStringData(), "abcd");
}

TEST(CMyStringIteratorTests, StdCountWorksWithStringIterators)
{
	CMyString str("banana");

	auto count = std::count(str.begin(), str.end(), 'a');

	EXPECT_EQ(count, 3);
}

TEST(CMyStringIteratorTests, StdCountWorksWithConstStringIterators)
{
	const CMyString str("mississippi");

	auto count = std::count(str.cbegin(), str.cend(), 's');

	EXPECT_EQ(count, 4);
}

TEST(CMyStringIteratorTests, StdReverseWorksWithMutableStringIterators)
{
	CMyString str("abcdef");

	std::reverse(str.begin(), str.end());

	EXPECT_STREQ(str.GetStringData(), "fedcba");
}

TEST(CMyStringIteratorTests, StdCopyWorksWithStringIterators)
{
	CMyString str("copy");
	std::string copied;

	std::copy(str.begin(), str.end(), std::back_inserter(copied));

	EXPECT_EQ(copied, "copy");
}

TEST(CMyStringIteratorTests, StdCopyWorksWithConstStringIterators)
{
	const CMyString str("const copy");
	std::string copied;

	std::copy(str.cbegin(), str.cend(), std::back_inserter(copied));

	EXPECT_EQ(copied, "const copy");
}

TEST(CMyStringIteratorTests, ReverseIteratorCanModifyString)
{
	CMyString str("abcd");

	*str.rbegin() = 'Z';

	EXPECT_STREQ(str.GetStringData(), "abcZ");
}

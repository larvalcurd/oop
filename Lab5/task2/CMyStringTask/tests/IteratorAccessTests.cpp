#include "../src/CMyString.h"

#include <type_traits>

#include <gtest/gtest.h>

TEST(StringIteratorAccessTests, DereferenceReturnsCurrentCharacter)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data, data, data + 3);

	EXPECT_EQ(*it, 'a');
}

TEST(StringIteratorAccessTests, NonConstDereferenceAllowsChangingCharacter)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data, data, data + 3);

	*it = 'x';

	EXPECT_EQ(data[0], 'x');
	EXPECT_STREQ(data, "xbc");
}

TEST(StringIteratorAccessTests, ConstDereferenceReturnsConstReference)
{
	const char data[] = "abc";

	using ConstIterator = StringIterator<true>;

	ConstIterator it(data, data, data + 3);

	static_assert(std::is_same_v<decltype(*it), const char&>);
	EXPECT_EQ(*it, 'a');
}

TEST(StringIteratorAccessTests, ArrowOperatorReturnsPointerToCurrentCharacter)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data, data, data + 3);

	EXPECT_EQ(it.operator->(), data);
	EXPECT_EQ(*it.operator->(), 'a');
}

TEST(StringIteratorAccessTests, ConstArrowOperatorReturnsConstPointerToCurrentCharacter)
{
	const char data[] = "abc";

	using ConstIterator = StringIterator<true>;

	ConstIterator it(data + 1, data, data + 3);

	static_assert(std::is_same_v<decltype(it.operator->()), const char*>);
	EXPECT_EQ(it.operator->(), data + 1);
	EXPECT_EQ(*it.operator->(), 'b');
}

TEST(StringIteratorAccessTests, IndexOperatorReturnsCharacterByOffset)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;

	Iterator it(data + 1, data, data + 5);

	EXPECT_EQ(it[0], 'b');
	EXPECT_EQ(it[1], 'c');
	EXPECT_EQ(it[3], 'e');
}

TEST(StringIteratorAccessTests, ConstIndexOperatorReturnsConstReference)
{
	const char data[] = "abcde";

	using ConstIterator = StringIterator<true>;

	ConstIterator it(data + 1, data, data + 5);

	static_assert(std::is_same_v<decltype(it[0]), const char&>);
	EXPECT_EQ(it[0], 'b');
	EXPECT_EQ(it[2], 'd');
}

TEST(StringIteratorAccessTests, IndexOperatorSupportsNegativeOffset)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;

	Iterator it(data + 3, data, data + 5);

	EXPECT_EQ(it[-1], 'c');
	EXPECT_EQ(it[-3], 'a');
}

TEST(StringIteratorAccessTests, NonConstIndexOperatorAllowsChangingCharacter)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;

	Iterator it(data + 1, data, data + 5);

	it[2] = 'x';

	EXPECT_STREQ(data, "abcxe");
}

TEST(StringIteratorAccessTests, NonConstIndexOperatorWithNegativeOffsetAllowsChangingCharacter)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;

	Iterator it(data + 3, data, data + 5);

	it[-1] = 'x';

	EXPECT_STREQ(data, "abxde");
}

TEST(StringItaratorAccessTests, NonConstIteratorConvertsToConstIterator)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;
	using ConstIterator = StringIterator<true>;

	Iterator it(data + 1, data, data + 3);
	ConstIterator cit = it;

	EXPECT_EQ(*cit, 'b');
	static_assert(std::is_constructible_v<ConstIterator, Iterator>);
}

TEST(StringItaratorAccessTests, ConstIteratorConvertToNonConstIterator)
{
	using Iterator = StringIterator<false>;
	using ConstIterator = StringIterator<true>;

	static_assert(!std::is_constructible_v<Iterator, ConstIterator>);
}
#include "../src/CMyString.h"

#include <type_traits>

#include <gtest/gtest.h>

TEST(StringIteratorMovementTests, PrefixIncrementMovesIteratorForward)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data, data, data + 3);

	++it;

	EXPECT_EQ(*it, 'b');
}

TEST(StringIteratorMovementTests, PrefixIncrementCanMoveFromLastCharacterToEnd)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data + 2, data, data + 3);

	++it;
	--it;

	EXPECT_EQ(*it, 'c');
}

TEST(StringIteratorMovementTests, PostfixIncrementReturnsOldIteratorAndMovesCurrentForward)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data, data, data + 3);

	Iterator old = it++;

	EXPECT_EQ(*old, 'a');
	EXPECT_EQ(*it, 'b');
}

TEST(StringIteratorMovementTests, PostfixIncrementCanMoveFromLastCharacterToEnd)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data + 2, data, data + 3);

	Iterator old = it++;

	EXPECT_EQ(*old, 'c');

	--it;
	EXPECT_EQ(*it, 'c');
}

TEST(StringIteratorMovementTests, PrefixDecrementMovesIteratorBackward)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data + 2, data, data + 3);

	--it;

	EXPECT_EQ(*it, 'b');
}

TEST(StringIteratorMovementTests, PrefixDecrementCanMoveFromEndToLastCharacter)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data + 3, data, data + 3);

	--it;

	EXPECT_EQ(*it, 'c');
}

TEST(StringIteratorMovementTests, PostfixDecrementReturnsOldIteratorAndMovesCurrentBackward)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data + 2, data, data + 3);

	Iterator old = it--;

	EXPECT_EQ(*old, 'c');
	EXPECT_EQ(*it, 'b');
}

TEST(StringIteratorMovementTests, PostfixDecrementCanMoveFromEndToLastCharacter)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data + 3, data, data + 3);

	Iterator old = it--;

	EXPECT_EQ(*it, 'c');
	--old;
	EXPECT_EQ(*old, 'c');
}

TEST(StringIteratorMovementTests, PrefixIncrementReturnsReferenceToIterator)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data, data, data + 3);

	static_assert(std::is_same_v<decltype(++it), Iterator&>);
}

TEST(StringIteratorMovementTests, PostfixIncrementReturnsIteratorByValue)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data, data, data + 3);

	static_assert(std::is_same_v<decltype(it++), Iterator>);
}

TEST(StringIteratorMovementTests, PrefixDecrementReturnsReferenceToIterator)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data + 1, data, data + 3);

	static_assert(std::is_same_v<decltype(--it), Iterator&>);
}

TEST(StringIteratorMovementTests, PostfixDecrementReturnsIteratorByValue)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data + 1, data, data + 3);

	static_assert(std::is_same_v<decltype(it--), Iterator>);
}

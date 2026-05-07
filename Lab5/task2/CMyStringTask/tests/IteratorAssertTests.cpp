#include "../src/CMyString.h"

#include <gtest/gtest.h>

#ifndef NDEBUG

TEST(StringIteratorAssertTests, DereferencingEndIteratorFailsAssertion)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data + 3, data, data + 3);

	EXPECT_DEATH(*it, "Dereferencing out of range");
}

TEST(StringIteratorAssertTests, IndexOutOfRangeFailsAssertion)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data, data, data + 3);

	EXPECT_DEATH(it[3], "Indexing out of range");
}

TEST(StringIteratorAssertTests, IncrementingEndIteratorFailsAssertion)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data + 3, data, data + 3);

	EXPECT_DEATH(++it, "Incrementing past end");
}

TEST(StringIteratorAssertTests, DecrementingBeginIteratorFailsAssertion)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data, data, data + 3);

	EXPECT_DEATH(--it, "Decrementing before begin");
}

TEST(StringIteratorAssertTests, ArrowOperatorOnEndIteratorFailsAssertion)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data + 3, data, data + 3);

	EXPECT_DEATH(it.operator->(), "Dereferencing out of range");
}

TEST(StringIteratorAssertTests, NegativeIndexOutOfRangeFailsAssertion)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data + 1, data, data + 3);

	EXPECT_DEATH(it[-2], "Indexing out of range");
}

TEST(StringIteratorAssertTests, PlusNPastEndFailsAssertion)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data + 1, data, data + 3);

	EXPECT_DEATH(it + 3, "Iterator \\+ n out of range");
}

TEST(StringIteratorAssertTests, MinusNBeforeBeginFailsAssertion)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data + 1, data, data + 3);

	EXPECT_DEATH(it - 2, "Iterator - n out of range");
}

TEST(StringIteratorAssertTests, PlusEqualsPastEndFailsAssertion)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data + 2, data, data + 3);

	EXPECT_DEATH(it += 2, "Iterator \\+= n out of range");
}

TEST(StringIteratorAssertTests, MinusEqualsBeforeBeginFailsAssertion)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data + 1, data, data + 3);

	EXPECT_DEATH(it -= 2, "Iterator -= n out of range");
}

TEST(StringIteratorAssertTests, NPlusIteratorPastEndFailsAssertion)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data + 2, data, data + 3);

	EXPECT_DEATH(3 + it, "Iterator \\+ n out of range");
}

#endif

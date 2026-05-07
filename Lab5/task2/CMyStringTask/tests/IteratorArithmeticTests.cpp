#include "../src/CMyString.h"

#include <type_traits>

#include <gtest/gtest.h>

TEST(StringIteratorArithmeticTests, PlusNReturnsIteratorMovedForward)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;

	Iterator it(data, data, data + 5);

	Iterator result = it + 3;

	EXPECT_EQ(*result, 'd');
}

TEST(StringIteratorArithmeticTests, PlusZeroReturnsSamePosition)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;

	Iterator it(data + 2, data, data + 5);

	Iterator result = it + 0;

	EXPECT_EQ(*result, 'c');
}

TEST(StringIteratorArithmeticTests, PlusNCanReachEnd)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data, data, data + 3);

	Iterator result = it + 3;

	--result;
	EXPECT_EQ(*result, 'c');
}

TEST(StringIteratorArithmeticTests, PlusNegativeMovesBackward)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;

	Iterator it(data + 4, data, data + 5);

	Iterator result = it + (-2);

	EXPECT_EQ(*result, 'c');
}

TEST(StringIteratorArithmeticTests, MinusNReturnsIteratorMovedBackward)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;

	Iterator it(data + 4, data, data + 5);

	Iterator result = it - 2;

	EXPECT_EQ(*result, 'c');
}

TEST(StringIteratorArithmeticTests, MinusZeroReturnsSamePosition)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;

	Iterator it(data + 2, data, data + 5);

	Iterator result = it - 0;

	EXPECT_EQ(*result, 'c');
}

TEST(StringIteratorArithmeticTests, MinusNCanReachBegin)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data + 3, data, data + 3);

	Iterator result = it - 3;

	EXPECT_EQ(*result, 'a');
}

TEST(StringIteratorArithmeticTests, MinusNegativeMovesForward)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;

	Iterator it(data + 1, data, data + 5);

	Iterator result = it - (-2);

	EXPECT_EQ(*result, 'd');
}

TEST(StringIteratorArithmeticTests, PlusEqualsMovesIteratorForward)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;

	Iterator it(data, data, data + 5);

	it += 3;

	EXPECT_EQ(*it, 'd');
}

TEST(StringIteratorArithmeticTests, PlusEqualsZeroDoesNothing)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;

	Iterator it(data + 2, data, data + 5);

	it += 0;

	EXPECT_EQ(*it, 'c');
}

TEST(StringIteratorArithmeticTests, PlusEqualsCanReachEnd)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data, data, data + 3);

	it += 3;
	--it;

	EXPECT_EQ(*it, 'c');
}

TEST(StringIteratorArithmeticTests, PlusEqualsNegativeMovesBackward)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;

	Iterator it(data + 4, data, data + 5);

	it += (-2);

	EXPECT_EQ(*it, 'c');
}

TEST(StringIteratorArithmeticTests, PlusEqualsReturnsReferenceToSelf)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data, data, data + 3);

	static_assert(std::is_same_v<decltype(it += 1), Iterator&>);

	Iterator& ref = (it += 1);

	EXPECT_EQ(&ref, &it);
}

TEST(StringIteratorArithmeticTests, MinusEqualsMovesIteratorBackward)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;

	Iterator it(data + 4, data, data + 5);

	it -= 2;

	EXPECT_EQ(*it, 'c');
}

TEST(StringIteratorArithmeticTests, MinusEqualsZeroDoesNothing)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;

	Iterator it(data + 2, data, data + 5);

	it -= 0;

	EXPECT_EQ(*it, 'c');
}

TEST(StringIteratorArithmeticTests, MinusEqualsCanReachBegin)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data + 3, data, data + 3);

	it -= 3;

	EXPECT_EQ(*it, 'a');
}

TEST(StringIteratorArithmeticTests, MinusEqualsNegativeMovesForward)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;

	Iterator it(data + 1, data, data + 5);

	it -= (-2);

	EXPECT_EQ(*it, 'd');
}

TEST(StringIteratorArithmeticTests, MinusEqualsReturnsReferenceToSelf)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator it(data + 2, data, data + 3);

	static_assert(std::is_same_v<decltype(it -= 1), Iterator&>);

	Iterator& ref = (it -= 1);

	EXPECT_EQ(&ref, &it);
}

TEST(StringIteratorArithmeticTests, DifferenceBetweenIteratorsReturnsDistance)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;

	Iterator a(data + 1, data, data + 5);
	Iterator b(data + 4, data, data + 5);

	EXPECT_EQ(b - a, 3);
	EXPECT_EQ(a - b, -3);
}

TEST(StringIteratorArithmeticTests, DifferenceBetweenSameIteratorsIsZero)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;

	Iterator it(data + 2, data, data + 5);

	EXPECT_EQ(it - it, 0);
}

TEST(StringIteratorArithmeticTests, DifferenceWithBeginGivesOffset)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;

	Iterator begin(data, data, data + 5);
	Iterator end(data + 5, data, data + 5);

	EXPECT_EQ(end - begin, 5);
}

TEST(StringIteratorArithmeticTests, DifferenceReturnsCorrectType)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;

	Iterator a(data, data, data + 3);
	Iterator b(data + 1, data, data + 3);

	static_assert(std::is_same_v<decltype(b - a), std::ptrdiff_t>);
}

TEST(StringIteratorArithmeticTests, NPlusIteratorMovesForward)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;

	Iterator it(data, data, data + 5);

	Iterator result = 3 + it;

	EXPECT_EQ(*result, 'd');
}

TEST(StringIteratorArithmeticTests, NPlusConstIteratorMovesForward)
{
	const char data[] = "abcde";

	using ConstIterator = StringIterator<true>;

	ConstIterator it(data + 1, data, data + 5);

	ConstIterator result = 2 + it;

	EXPECT_EQ(*result, 'd');
}

TEST(StringIteratorArithmeticTests, NPlusIteratorMatchesIteratorPlusN)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;

	Iterator it(data + 1, data, data + 5);

	Iterator r1 = it + 2;
	Iterator r2 = 2 + it;

	EXPECT_EQ(*r1, *r2);
	EXPECT_EQ(r1 - it, r2 - it);
}

TEST(StringIteratorArithmeticTests, ConstIteratorPlusNWorks)
{
	const char data[] = "abcde";

	using ConstIterator = StringIterator<true>;

	ConstIterator it(data, data, data + 5);

	ConstIterator result = it + 2;

	EXPECT_EQ(*result, 'c');
}

TEST(StringIteratorArithmeticTests, ConstIteratorMinusNWorks)
{
	const char data[] = "abcde";

	using ConstIterator = StringIterator<true>;

	ConstIterator it(data + 4, data, data + 5);

	ConstIterator result = it - 3;

	EXPECT_EQ(*result, 'b');
}

TEST(StringIteratorArithmeticTests, ConstIteratorDifferenceWorks)
{
	const char data[] = "abcde";

	using ConstIterator = StringIterator<true>;

	ConstIterator a(data, data, data + 5);
	ConstIterator b(data + 5, data, data + 5);

	EXPECT_EQ(b - a, 5);
}

TEST(StringIteratorArithmeticTests, ChainedArithmeticWorks)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;

	Iterator it(data, data, data + 5);

	Iterator result = (it + 4) - 2;

	EXPECT_EQ(*result, 'c');
}

TEST(StringIteratorArithmeticTests, PlusEqualsChainedWorks)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;

	Iterator it(data, data, data + 5);

	(it += 3) -= 1;

	EXPECT_EQ(*it, 'c');
}

TEST(StringIteratorArithmeticTests, NonConstMinusConstIteratorReturnsDistance)
{
	char data[] = "acbde";

	using Iterator = StringIterator<false>;
	using ConstIterator = StringIterator<true>;

	Iterator it(data + 4, data, data + 5);
	ConstIterator cit(data + 1, data, data + 5);

	EXPECT_EQ(it - cit, 3);
}

TEST(StringIteratorArithmeticTests, ConstMinusNonConstIteratorReturnsDistance)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;
	using ConstIterator = StringIterator<true>;

	ConstIterator cit(data + 4, data, data + 5);
	Iterator it(data + 1, data, data + 5);

	EXPECT_EQ(cit - it, 3);
}

TEST(StringIteratorArithmeticTests, MixedDifferenceCanBeNegative)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;
	using ConstIterator = StringIterator<true>;

	Iterator it(data + 1, data, data + 5);
	ConstIterator cit(data + 4, data, data + 5);

	EXPECT_EQ(it - cit, -3);
}

TEST(StringIteratorArithmeticTests, MixedDifferenceSamePositionIsZero)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;
	using ConstIterator = StringIterator<true>;

	Iterator it(data + 2, data, data + 5);
	ConstIterator cit(data + 2, data, data + 5);

	EXPECT_EQ(it - cit, 0);
	EXPECT_EQ(cit - it, 0);
}

TEST(StringIteratorArithmeticTests, MixedDifferenceBeginToEndGivesLength)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;
	using ConstIterator = StringIterator<true>;

	Iterator it(data + 5, data, data + 5);
	ConstIterator cit(data, data, data + 5);

	EXPECT_EQ(it - cit, 5);
	EXPECT_EQ(cit - it, -5);
}

TEST(StringIteratorArithmeticTests, MixedDifferenceReturnsCorrectType)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;
	using ConstIterator = StringIterator<true>;

	Iterator it(data + 1, data, data + 3);
	ConstIterator cit(data, data, data + 3);

	static_assert(std::is_same_v<decltype(it - cit), std::ptrdiff_t>);
	static_assert(std::is_same_v<decltype(cit - it), std::ptrdiff_t>);
}

TEST(StringIteratorArithmeticTests, MixedEqualityComprasionWorks)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;
	using ConstIterator = StringIterator<true>;

	Iterator it(data + 2, data, data + 5);
	ConstIterator cit(data + 2, data, data + 5);

	EXPECT_TRUE(it == cit);
	EXPECT_TRUE(cit == it);
	EXPECT_FALSE(it != cit);
	EXPECT_FALSE(cit != it);
}

TEST(StringIteratorArithmeticTests, MixedOrderingComparisonWorks)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;
	using ConstIterator = StringIterator<true>;

	Iterator it(data + 1, data, data + 5);
	ConstIterator cit(data + 3, data, data + 5);

	EXPECT_TRUE(it < cit);
	EXPECT_TRUE(it <= cit);
	EXPECT_FALSE(it > cit);
	EXPECT_FALSE(it >= cit);

	EXPECT_TRUE(cit > it);
	EXPECT_TRUE(cit >= it);
	EXPECT_FALSE(cit < it);
	EXPECT_FALSE(cit <= it);
}

TEST(StringIteratorArithmeticTests, MixedComparisonAtSamePositionWorks)
{
	char data[] = "abcde";

	using Iterator = StringIterator<false>;
	using ConstIterator = StringIterator<true>;

	Iterator it(data + 4, data, data + 5);
	ConstIterator cit(data + 4, data, data + 5);

	EXPECT_TRUE(it <= cit);
	EXPECT_TRUE(it >= cit);
	EXPECT_TRUE(cit <= it);
	EXPECT_TRUE(cit >= it);
}

TEST(StringIteratorArithmeticTests, ComparisonOperatorsReturnBoolForMixedIterators)
{
	char data[] = "abc";

	using Iterator = StringIterator<false>;
	using ConstIterator = StringIterator<true>;

	Iterator it(data, data, data + 3);
	ConstIterator cit(data + 1, data, data + 3);

	static_assert(std::is_same_v<decltype(it == cit), bool>);
	static_assert(std::is_same_v<decltype(it != cit), bool>);
	static_assert(std::is_same_v<decltype(it < cit), bool>);
	static_assert(std::is_same_v<decltype(it <= cit), bool>);
	static_assert(std::is_same_v<decltype(it > cit), bool>);
	static_assert(std::is_same_v<decltype(it >= cit), bool>);
}
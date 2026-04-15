//#include "../src/CDate.h"
//#include <gtest/gtest.h>
//
//namespace
//{
//constexpr unsigned kMaxTimestamp = 2932896u;
//}
//
//TEST(CDateDefaultCtor, CreatesEpochDate)
//{
//	CDate date;
//	EXPECT_TRUE(date.IsValid());
//	EXPECT_EQ(date.GetDay(), 1u);
//	EXPECT_EQ(date.GetMonth(), Month::JANUARY);
//	EXPECT_EQ(date.GetYear(), 1970u);
//}
//
//TEST(CDateDefaultCtor, TwoDefaultObjectsAreEquivalent)
//{
//	CDate a;
//	CDate b;
//
//	EXPECT_EQ(a.IsValid(), b.IsValid());
//	EXPECT_EQ(a.GetDay(), b.GetDay());
//	EXPECT_EQ(a.GetMonth(), b.GetMonth());
//	EXPECT_EQ(a.GetYear(), b.GetYear());
//}
//
//TEST(CDateTimestampCtor, Timestamp0IsValid)
//{
//	CDate date(0u);
//	EXPECT_TRUE(date.IsValid());
//}
//
//TEST(CDateTimestampCtor, Timestamp1IsValid)
//{
//	CDate date(1u);
//	EXPECT_TRUE(date.IsValid());
//}
//
//TEST(CDateTimestampCtor, Timestamp32IsValid)
//{
//	CDate date(32u);
//	EXPECT_TRUE(date.IsValid());
//}
//
//TEST(CDateTimestampCtor, MaxTimestampIsValid)
//{
//	CDate date(kMaxTimestamp);
//	EXPECT_TRUE(date.IsValid());
//}
//
//TEST(CDateTimestampCtor, TimestampAboveMaxIsInvalid)
//{
//	CDate date(kMaxTimestamp + 1u);
//	EXPECT_FALSE(date.IsValid());
//}
//
//TEST(CDateGettersFromTimestamp, EpochDate)
//{
//	CDate d(0u);
//
//	ASSERT_TRUE(d.IsValid());
//	EXPECT_EQ(d.GetDay(), 1u);
//	EXPECT_EQ(d.GetMonth(), Month::JANUARY);
//	EXPECT_EQ(d.GetYear(), 1970u);
//}
//
//TEST(CDateGettersFromTimestamp, FirstDayOfFebruary1970)
//{
//	CDate d(31u); 
//
//	ASSERT_TRUE(d.IsValid());
//	EXPECT_EQ(d.GetDay(), 1u);
//	EXPECT_EQ(d.GetMonth(), Month::FEBRUARY);
//	EXPECT_EQ(d.GetYear(), 1970u);
//}
//
//TEST(CDateGettersFromTimestamp, LeapDayFebruary2024)
//{
//	// 29.02.2024 relative to 01.01.1970
//	CDate d(19782u);
//
//	ASSERT_TRUE(d.IsValid());
//	EXPECT_EQ(d.GetDay(), 29u);
//	EXPECT_EQ(d.GetMonth(), Month::FEBRUARY);
//	EXPECT_EQ(d.GetYear(), 2024u);
//}
//
//TEST(CDateGettersFromTimestamp, LastDayOfYear9999)
//{
//	// 31.12.9999 relative to 01.01.1970
//	CDate d(2932896u);
//
//	ASSERT_TRUE(d.IsValid());
//	EXPECT_EQ(d.GetDay(), 31u);
//	EXPECT_EQ(d.GetMonth(), Month::DECEMBER);
//	EXPECT_EQ(d.GetYear(), 9999u);
//}
//
//TEST(CDateGettersFromTimestamp, RandomTimestampsHaveConsistentGetters)
//{
//	const unsigned samples[] = { 123u, 12345u, 543210u, 2000000u };
//
//	for (unsigned ts : samples)
//	{
//		CDate d(ts);
//		ASSERT_TRUE(d.IsValid());
//
//		const unsigned day1 = d.GetDay();
//		const Month month1 = d.GetMonth();
//		const unsigned year1 = d.GetYear();
//
//		// Consistency: repeated calls return the same values.
//		EXPECT_EQ(d.GetDay(), day1);
//		EXPECT_EQ(d.GetMonth(), month1);
//		EXPECT_EQ(d.GetYear(), year1);
//
//		// Basic sanity bounds.
//		EXPECT_GE(day1, 1u);
//		EXPECT_LE(day1, 31u);
//		EXPECT_GE(static_cast<unsigned>(month1), 1u);
//		EXPECT_LE(static_cast<unsigned>(month1), 12u);
//		EXPECT_GE(year1, 1970u);
//		EXPECT_LE(year1, 9999u);
//	}
//}
//
//TEST(CDateYmdCtor, EpochDateRoundTrip)
//{
//	CDate d(1u, Month::JANUARY, 1970u);
//
//	ASSERT_TRUE(d.IsValid());
//	EXPECT_EQ(d.GetDay(), 1u);
//	EXPECT_EQ(d.GetMonth(), Month::JANUARY);
//	EXPECT_EQ(d.GetYear(), 1970u);
//}
//
//TEST(CDateYmdCtor, SecondOfJanuary1970IsNextDay)
//{
//	CDate d(2u, Month::JANUARY, 1970u);
//
//	ASSERT_TRUE(d.IsValid());
//	EXPECT_EQ(d.GetDay(), 2u);
//	EXPECT_EQ(d.GetMonth(), Month::JANUARY);
//	EXPECT_EQ(d.GetYear(), 1970u);
//}
//
//TEST(CDateYmdCtor, FirstOfMarch2024IsValid)
//{
//	CDate d(1u, Month::MARCH, 2024u);
//
//	ASSERT_TRUE(d.IsValid());
//	EXPECT_EQ(d.GetDay(), 1u);
//	EXPECT_EQ(d.GetMonth(), Month::MARCH);
//	EXPECT_EQ(d.GetYear(), 2024u);
//}
//
//TEST(CDateYmdCtor, LastDayOfYear9999IsValid)
//{
//	CDate d(31u, Month::DECEMBER, 9999u);
//
//	ASSERT_TRUE(d.IsValid());
//	EXPECT_EQ(d.GetDay(), 31u);
//	EXPECT_EQ(d.GetMonth(), Month::DECEMBER);
//	EXPECT_EQ(d.GetYear(), 9999u);
//}
//
//TEST(CDateYmdCtor, SeveralValidDatesRoundTrip)
//{
//	struct DateCase
//	{
//		unsigned day;
//		Month month;
//		unsigned year;
//	};
//
//	const DateCase cases[] = {
//		{15u, Month::MARCH, 1970u},
//		{29u, Month::FEBRUARY, 2024u},
//		{1u, Month::JANUARY, 2000u},
//		{28u, Month::FEBRUARY, 2023u},
//		{31u, Month::DECEMBER, 9999u},
//	};
//
//	for (const auto& c : cases)
//	{
//		CDate d(c.day, c.month, c.year);
//		ASSERT_TRUE(d.IsValid());
//		EXPECT_EQ(d.GetDay(), c.day);
//		EXPECT_EQ(d.GetMonth(), c.month);
//		EXPECT_EQ(d.GetYear(), c.year);
//	}
//}
//
//TEST(CDateCtorEquivalence, YmdAndTimestampAreEquivalentForEarlyEpochDates)
//{
//	CDate ymdEpoch(1u, Month::JANUARY, 1970u);
//	CDate tsEpoch(0u);
//
//	ASSERT_TRUE(ymdEpoch.IsValid());
//	ASSERT_TRUE(tsEpoch.IsValid());
//	EXPECT_EQ(ymdEpoch.GetDay(), tsEpoch.GetDay());
//	EXPECT_EQ(ymdEpoch.GetMonth(), tsEpoch.GetMonth());
//	EXPECT_EQ(ymdEpoch.GetYear(), tsEpoch.GetYear());
//
//	CDate ymdNext(2u, Month::JANUARY, 1970u);
//	CDate tsNext(1u);
//
//	ASSERT_TRUE(ymdNext.IsValid());
//	ASSERT_TRUE(tsNext.IsValid());
//	EXPECT_EQ(ymdNext.GetDay(), tsNext.GetDay());
//	EXPECT_EQ(ymdNext.GetMonth(), tsNext.GetMonth());
//	EXPECT_EQ(ymdNext.GetYear(), tsNext.GetYear());
//}
//
//TEST(CDateYmdCtorValidation, April31IsInvalid)
//{
//	CDate d(31u, Month::APRIL, 2024u);
//	EXPECT_FALSE(d.IsValid());
//}
//
//TEST(CDateYmdCtorValidation, February29InNonLeapYearIsInvalid)
//{
//	CDate d(29u, Month::FEBRUARY, 2023u);
//	EXPECT_FALSE(d.IsValid());
//}
//
//TEST(CDateYmdCtorValidation, February29InLeapYearIsValid)
//{
//	CDate d(29u, Month::FEBRUARY, 2024u);
//	EXPECT_TRUE(d.IsValid());
//}
//
//TEST(CDateYmdCtorValidation, YearBefore1970IsInvalid)
//{
//	CDate d(1u, Month::JANUARY, 1969u);
//	EXPECT_FALSE(d.IsValid());
//}
//
//TEST(CDateYmdCtorValidation, Month13IsInvalid)
//{
//	CDate d(1u, static_cast<Month>(13), 2024u);
//	EXPECT_FALSE(d.IsValid());
//}
//
//TEST(CDateYmdCtorValidation, DayZeroIsInvalid)
//{
//	CDate d(0u, Month::JANUARY, 2024u);
//	EXPECT_FALSE(d.IsValid());
//}
//
//TEST(CDateYmdCtorValidation, MonthZeroIsInvalid)
//{
//	CDate d(1u, static_cast<Month>(0), 2024u);
//	EXPECT_FALSE(d.IsValid());
//}
//
//TEST(CDateWeekDay, EpochIsThursday)
//{
//	CDate d(0u);
//
//	ASSERT_TRUE(d.IsValid());
//	EXPECT_EQ(d.GetWeekDay(), WeekDay::THURSDAY);
//}
//
//TEST(CDateWeekDay, FourthOfJanuary1970IsSunday)
//{
//	CDate d(3u); // 04.01.1970
//
//	ASSERT_TRUE(d.IsValid());
//	EXPECT_EQ(d.GetWeekDay(), WeekDay::SUNDAY);
//}
//
//TEST(CDateWeekDay, LeapDay2024IsThursday)
//{
//	CDate d(19782u); // 29.02.2024
//	
//	ASSERT_TRUE(d.IsValid());
//	EXPECT_EQ(d.GetWeekDay(), WeekDay::THURSDAY);
//}
//
//TEST(CDateWeekDay, FirstOfJanuary2000IsSaturday)
//{
//	CDate d(10957u); // 01.01.2000
//
//	ASSERT_TRUE(d.IsValid());
//	EXPECT_EQ(d.GetWeekDay(), WeekDay::SATURDAY);
//}
//
//TEST(CDateWeekDay, InvalidDateReturnsThursdayByContract)
//{
//	CDate d(2932897u); // invalid timestamp (max is 2932896)
//
//	ASSERT_FALSE(d.IsValid());
//	EXPECT_EQ(d.GetWeekDay(), WeekDay::THURSDAY);
//}
//
//TEST(CDatePrefixTests, PrefixIncrementNormalDay)	
//{
//	CDate date(14, Month::APRIL, 2026);
//
//	CDate& ref = ++date;
//
//	EXPECT_EQ(&ref, &date);
//	EXPECT_TRUE(date.IsValid());
//	EXPECT_EQ(date.GetDay(), 15u);
//	EXPECT_EQ(date.GetMonth(), Month::APRIL);
//	EXPECT_EQ(date.GetYear(), 2026u);
//}
//
//TEST(CDatePrefixTests, PrefixDecrementNormalDay)
//{
//	CDate date(15, Month::APRIL, 2026);
//
//	CDate& ref = --date;
//
//	EXPECT_EQ(&ref, &date);
//	EXPECT_TRUE(date.IsValid());
//	EXPECT_EQ(date.GetDay(), 14u);
//	EXPECT_EQ(date.GetMonth(), Month::APRIL);
//	EXPECT_EQ(date.GetYear(), 2026u);
//}
//
//TEST(CDatePrefixTests, PrefixIncrementEndOfMonth)
//{
//	CDate date(31, Month::JANUARY, 2026);
//
//	++date;
//
//	EXPECT_TRUE(date.IsValid());
//	EXPECT_EQ(date.GetDay(), 1u);
//	EXPECT_EQ(date.GetMonth(), Month::FEBRUARY);
//	EXPECT_EQ(date.GetYear(), 2026u);
//}
//
//TEST(CDatePrefixTests, PrefixIncrementEndOfYear)
//{
//	CDate date(31, Month::DECEMBER, 2026);
//
//	++date;
//
//	EXPECT_TRUE(date.IsValid());
//	EXPECT_EQ(date.GetDay(), 1u);
//	EXPECT_EQ(date.GetMonth(), Month::JANUARY);
//	EXPECT_EQ(date.GetYear(), 2027u);
//}
//
//TEST(CDatePrefixTests, PrefixDecrementStartOfMonth)
//{
//	CDate date(1, Month::MARCH, 2026);
//
//	--date;
//
//	EXPECT_TRUE(date.IsValid());
//	EXPECT_EQ(date.GetDay(), 28u);
//	EXPECT_EQ(date.GetMonth(), Month::FEBRUARY);
//	EXPECT_EQ(date.GetYear(), 2026u);
//}
//
//TEST(CDatePrefixTests, PrefixDecrementStartOfYear)
//{
//	CDate date(1, Month::JANUARY, 1971);
//
//	--date;
//
//	EXPECT_TRUE(date.IsValid());
//	EXPECT_EQ(date.GetDay(), 31u);
//	EXPECT_EQ(date.GetMonth(), Month::DECEMBER);
//	EXPECT_EQ(date.GetYear(), 1970u);
//}
//
//TEST(CDatePrefixTests, PrefixIncrementUpperBoundaryBecomesInvalid)
//{
//	CDate date(31, Month::DECEMBER, 9999);
//
//	++date;
//
//	EXPECT_FALSE(date.IsValid());
//}
//
//TEST(CDatePrefixTests, PrefixDecrementLowerBoundaryBecomesInvalid)
//{
//	CDate date(1, Month::JANUARY, 1970);
//
//	--date;
//
//	EXPECT_FALSE(date.IsValid());
//}
//
//TEST(CDatePrefixTests, PrefixOnInvalidDateIsNoOpIncrement)
//{
//	CDate date(32, Month::JANUARY, 2026); // invalid
//
//	EXPECT_FALSE(date.IsValid());
//
//	++date;
//
//	EXPECT_FALSE(date.IsValid());
//	EXPECT_EQ(date.GetDay(), 0u);
//	EXPECT_EQ(date.GetMonth(), Month::JANUARY);
//	EXPECT_EQ(date.GetYear(), 0u);
//}
//
//TEST(CDatePrefixTests, PrefixOnInvalidDateIsNoOpDecrement)
//{
//	CDate date(32, Month::JANUARY, 2026); // invalid
//
//	EXPECT_FALSE(date.IsValid());
//
//	--date;
//
//	EXPECT_FALSE(date.IsValid());
//	EXPECT_EQ(date.GetDay(), 0u);
//	EXPECT_EQ(date.GetMonth(), Month::JANUARY);
//	EXPECT_EQ(date.GetYear(), 0u);
//}
//
//TEST(CDatePrefixTests, PrefixReturnsReference)
//{
//	static_assert(std::is_same_v<decltype(++std::declval<CDate&>()), CDate&>);
//	static_assert(std::is_same_v<decltype(--std::declval<CDate&>()), CDate&>);
//}
//
//TEST(CDatePostfixTests, PostfixIncrementBasic)
//{
//	CDate date(14, Month::APRIL, 2026);
//
//	CDate old = date++;
//
//	EXPECT_EQ(old.GetDay(), 14u);
//	EXPECT_EQ(date.GetDay(), 15u);
//}
//
//TEST(CDatePostfixTests, PostfixDecrementBasic)
//{
//	CDate date(15, Month::APRIL, 2026);
//
//	CDate old = date--;
//
//	EXPECT_EQ(old.GetDay(), 15u);
//	EXPECT_EQ(date.GetDay(), 14u);
//}
//
//TEST(CDatePostfixTests, PostfixIncrementFullCheck)
//{
//	CDate date(31, Month::DECEMBER, 2026);
//
//	CDate old = date++;
//
//	EXPECT_EQ(old.GetDay(), 31u);
//	EXPECT_EQ(old.GetMonth(), Month::DECEMBER);
//	EXPECT_EQ(old.GetYear(), 2026u);
//
//	EXPECT_EQ(date.GetDay(), 1u);
//	EXPECT_EQ(date.GetMonth(), Month::JANUARY);
//	EXPECT_EQ(date.GetYear(), 2027u);
//}
//
//TEST(CDatePostfixTests, PostfixIncrementUpperBoundary)
//{
//	CDate date(31, Month::DECEMBER, 9999);
//
//	CDate old = date++;
//
//	EXPECT_TRUE(old.IsValid());
//	EXPECT_EQ(old.GetYear(), 9999u);
//
//	EXPECT_FALSE(date.IsValid());
//}
//
//TEST(CDatePostfixTests, PostfixDecrementLowerBoundary)
//{
//	CDate date(1, Month::JANUARY, 1970);
//
//	CDate old = date--;
//
//	EXPECT_TRUE(old.IsValid());
//	EXPECT_EQ(old.GetYear(), 1970u);
//
//	EXPECT_FALSE(date.IsValid());
//}
//
//TEST(CDatePostfixTests, PostfixIncrementInvalidNoOp)
//{
//	CDate date(32, Month::JANUARY, 2026); 
//
//	CDate old = date++;
//
//	EXPECT_FALSE(old.IsValid());
//	EXPECT_FALSE(date.IsValid());
//}
//
//TEST(CDatePostfixTests, PostfixDecrementInvalidNoOp)
//{
//	CDate date(32, Month::JANUARY, 2026); 
//
//	CDate old = date--;
//
//	EXPECT_FALSE(old.IsValid());
//	EXPECT_FALSE(date.IsValid());
//}
//
//TEST(CDatePostfixTests, PostfixReturnsByValue)
//{
//	static_assert(std::is_same_v<decltype(std::declval<CDate>()++), CDate>);
//}
//
//TEST(CDateAdditionTests, AddPositiveDaysAcrossMonth)
//{
//	CDate date(28, Month::FEBRUARY, 2010);
//
//	CDate result = date + 3;
//
//	EXPECT_TRUE(result.IsValid());
//	EXPECT_EQ(result.GetDay(), 3u);
//	EXPECT_EQ(result.GetMonth(), Month::MARCH);
//	EXPECT_EQ(result.GetYear(), 2010u);
//}
//
//TEST(CDateAdditionTests, AddNegativeDaysInLeapYear)
//{
//	CDate date(1, Month::MARCH, 2024);
//
//	CDate result = date + (-1);
//
//	EXPECT_TRUE(result.IsValid());
//	EXPECT_EQ(result.GetDay(), 29u);
//	EXPECT_EQ(result.GetMonth(), Month::FEBRUARY);
//	EXPECT_EQ(result.GetYear(), 2024u);
//}
//
//TEST(CDateAdditionTests, AddPastUpperBoundaryBecomesInvalid)
//{
//	CDate date(31, Month::DECEMBER, 9999);
//
//	CDate result = date + 1;
//
//	EXPECT_FALSE(result.IsValid());
//}
//
//TEST(CDateAdditionTests, AddPastLowerBoundaryBecomesInvalid)
//{
//	CDate date(1, Month::JANUARY, 1970);
//
//	CDate result = date + (-1);
//
//	EXPECT_FALSE(result.IsValid());
//}
//
//TEST(CDateAdditionTests, AddToInvalidDateStaysInvalid)
//{
//	CDate date(32, Month::JANUARY, 2024); 
//
//	CDate result = date + 10;
//
//	EXPECT_FALSE(result.IsValid());
//}
//
//TEST(CDateAdditionTests, AdditionDoesNotModifyOriginal)
//{
//	CDate date(28, Month::FEBRUARY, 2010);
//
//	CDate result = date + 3;
//
//	EXPECT_TRUE(date.IsValid());
//	EXPECT_EQ(date.GetDay(), 28u);
//	EXPECT_EQ(date.GetMonth(), Month::FEBRUARY);
//	EXPECT_EQ(date.GetYear(), 2010u);
//
//	EXPECT_TRUE(result.IsValid());
//	EXPECT_EQ(result.GetDay(), 3u);
//	EXPECT_EQ(result.GetMonth(), Month::MARCH);
//	EXPECT_EQ(result.GetYear(), 2010u);
//}
//
//namespace
//{
//void ExpectSameDate(const CDate& lhs, const CDate& rhs)
//{
//	ASSERT_EQ(lhs.IsValid(), rhs.IsValid());
//
//	if (!lhs.IsValid())
//	{
//		return;
//	}
//
//	EXPECT_EQ(lhs.GetDay(), rhs.GetDay());
//	EXPECT_EQ(lhs.GetMonth(), rhs.GetMonth());
//	EXPECT_EQ(lhs.GetYear(), rhs.GetYear());
//}
//} // namespace
//
//TEST(CDateFreeAdditionTests, DaysPlusDatePositive)
//{
//	CDate date(28, Month::FEBRUARY, 2010);
//
//	CDate result = 3 + date;
//
//	EXPECT_TRUE(result.IsValid());
//	EXPECT_EQ(result.GetDay(), 3u);
//	EXPECT_EQ(result.GetMonth(), Month::MARCH);
//	EXPECT_EQ(result.GetYear(), 2010u);
//}
//
//TEST(CDateFreeAdditionTests, DaysPlusDateNegative)
//{
//	CDate date(1, Month::MARCH, 2024);
//
//	CDate result = -1 + date;
//
//	EXPECT_TRUE(result.IsValid());
//	EXPECT_EQ(result.GetDay(), 29u);
//	EXPECT_EQ(result.GetMonth(), Month::FEBRUARY);
//	EXPECT_EQ(result.GetYear(), 2024u);
//}
//
//TEST(CDateFreeAdditionTests, DaysPlusInvalidDateIsInvalid)
//{
//	CDate invalid(32, Month::JANUARY, 2024);
//
//	CDate result = 10 + invalid;
//
//	EXPECT_FALSE(result.IsValid());
//}
//
//TEST(CDateFreeAdditionTests, FreeAdditionMatchesMemberAddition)
//{
//	const int shifts[] = { -400, -1, 0, 1, 3, 30, 365, 1000 };
//
//	const CDate dates[] = {
//		CDate(1, Month::JANUARY, 1970),
//		CDate(28, Month::FEBRUARY, 2010),
//		CDate(1, Month::MARCH, 2024),
//		CDate(31, Month::DECEMBER, 9999),
//	};
//
//	for (const CDate& date : dates)
//	{
//		for (int shift : shifts)
//		{
//			ExpectSameDate(date + shift, shift + date);
//		}
//	}
//}
//
//TEST(CDateFreeAdditionTests, BoundaryMatchesMemberAddition)
//{
//	CDate date1(31, Month::DECEMBER, 9999);
//	ExpectSameDate(date1 + 1, 1 + date1);
//
//	CDate date2(1, Month::JANUARY, 1970);
//	ExpectSameDate(date2 + (-1), -1 + date2);
//}
//
//#include "CDate.h"
//#include <gtest/gtest.h>
//
//TEST(CDateSubtractionTests, SubtractAcrossMonthAndYear)
//{
//	CDate date(1, Month::JANUARY, 2010);
//
//	CDate result = date - 2;
//
//	EXPECT_TRUE(result.IsValid());
//	EXPECT_EQ(result.GetDay(), 30u);
//	EXPECT_EQ(result.GetMonth(), Month::DECEMBER);
//	EXPECT_EQ(result.GetYear(), 2009u);
//}
//
//TEST(CDateSubtractionTests, SubtractIntoLeapDay)
//{
//	CDate date(1, Month::MARCH, 2024);
//
//	CDate result = date - 1;
//
//	EXPECT_TRUE(result.IsValid());
//	EXPECT_EQ(result.GetDay(), 29u);
//	EXPECT_EQ(result.GetMonth(), Month::FEBRUARY);
//	EXPECT_EQ(result.GetYear(), 2024u);
//}
//
//TEST(CDateSubtractionTests, SubtractPastLowerBoundaryBecomesInvalid)
//{
//	CDate date(1, Month::JANUARY, 1970);
//
//	CDate result = date - 1;
//
//	EXPECT_FALSE(result.IsValid());
//}
//
//TEST(CDateSubtractionTests, SubtractFromInvalidStaysInvalid)
//{
//	CDate date(32, Month::JANUARY, 2024); // invalid
//
//	CDate result = date - 10;
//
//	EXPECT_FALSE(result.IsValid());
//}
//
//TEST(CDateSubtractionTests, SubtractionDoesNotModifyOriginal)
//{
//	CDate date(1, Month::JANUARY, 2010);
//
//	CDate result = date - 2;
//
//	EXPECT_TRUE(date.IsValid());
//	EXPECT_EQ(date.GetDay(), 1u);
//	EXPECT_EQ(date.GetMonth(), Month::JANUARY);
//	EXPECT_EQ(date.GetYear(), 2010u);
//
//	EXPECT_TRUE(result.IsValid());
//	EXPECT_EQ(result.GetDay(), 30u);
//	EXPECT_EQ(result.GetMonth(), Month::DECEMBER);
//	EXPECT_EQ(result.GetYear(), 2009u);
//}
//
//#include "CDate.h"
//#include <gtest/gtest.h>
//
//TEST(CDateDifferenceTests, PositiveDifference)
//{
//	CDate d1(1, Month::JANUARY, 2010);
//	CDate d2(30, Month::DECEMBER, 2009);
//
//	EXPECT_EQ(d1 - d2, 2); // timestamp difference
//}
//
//TEST(CDateDifferenceTests, NegativeDifference)
//{
//	CDate d1(1, Month::JANUARY, 2010);
//	CDate d2(3, Month::JANUARY, 2010);
//
//	EXPECT_EQ(d1 - d2, -2);
//}
//
//TEST(CDateDifferenceTests, ZeroDifference)
//{
//	CDate d1(1, Month::JANUARY, 2010);
//
//	EXPECT_EQ(d1 - d1, 0);
//}
//
//TEST(CDateDifferenceTests, ValidMinusInvalidReturnsZero)
//{
//	CDate valid(1, Month::JANUARY, 2010);
//	CDate invalid(32, Month::JANUARY, 2020);
//
//	EXPECT_EQ(valid - invalid, 0);
//}
//
//TEST(CDateDifferenceTests, InvalidMinusValidReturnsZero)
//{
//	CDate valid(1, Month::JANUARY, 2010);
//	CDate invalid(32, Month::JANUARY, 2020);
//
//	EXPECT_EQ(invalid - valid, 0);
//}
//
//TEST(CDateDifferenceTests, InvalidMinusInvalidReturnsZero)
//{
//	CDate invalid1(32, Month::JANUARY, 2020);
//	CDate invalid2(0, Month::FEBRUARY, 2020);
//
//	EXPECT_EQ(invalid1 - invalid2, 0);
//}
//
//TEST(CDateCompoundAssignmentTests, PlusEqualsAcrossMonth)
//{
//	CDate date(28, Month::FEBRUARY, 2010);
//
//	CDate& ref = (date += 3);
//
//	EXPECT_EQ(&ref, &date);
//	EXPECT_TRUE(date.IsValid());
//	EXPECT_EQ(date.GetDay(), 3u);
//	EXPECT_EQ(date.GetMonth(), Month::MARCH);
//	EXPECT_EQ(date.GetYear(), 2010u);
//}
//
//TEST(CDateCompoundAssignmentTests, MinusEqualsAcrossYear)
//{
//	CDate date(1, Month::JANUARY, 2010);
//
//	CDate& ref = (date -= 2);
//
//	EXPECT_EQ(&ref, &date);
//	EXPECT_TRUE(date.IsValid());
//	EXPECT_EQ(date.GetDay(), 30u);
//	EXPECT_EQ(date.GetMonth(), Month::DECEMBER);
//	EXPECT_EQ(date.GetYear(), 2009u);
//}
//
//TEST(CDateCompoundAssignmentTests, PlusEqualsUpperBoundaryBecomesInvalid)
//{
//	CDate date(31, Month::DECEMBER, 9999);
//
//	date += 1;
//
//	EXPECT_FALSE(date.IsValid());
//}
//
//TEST(CDateCompoundAssignmentTests, InvalidPlusEqualsNoOp)
//{
//	CDate date(32, Month::JANUARY, 2024); // invalid
//
//	date += 10;
//
//	EXPECT_FALSE(date.IsValid());
//	EXPECT_EQ(date.GetDay(), 0u);
//	EXPECT_EQ(date.GetMonth(), Month::JANUARY);
//	EXPECT_EQ(date.GetYear(), 0u);
//}
//
//TEST(CDateCompoundAssignmentTests, InvalidMinusEqualsNoOp)
//{
//	CDate date(32, Month::JANUARY, 2024); // invalid
//
//	date -= 10;
//
//	EXPECT_FALSE(date.IsValid());
//	EXPECT_EQ(date.GetDay(), 0u);
//	EXPECT_EQ(date.GetMonth(), Month::JANUARY);
//	EXPECT_EQ(date.GetYear(), 0u);
//}
//
//TEST(CDateCompoundAssignmentTests, PlusEqualsReturnsReference)
//{
//	static_assert(std::is_same_v<decltype(std::declval<CDate&>() += 1), CDate&>);
//}
//
//TEST(CDateCompoundAssignmentTests, MinusEqualsReturnsReference)
//{
//	static_assert(std::is_same_v<decltype(std::declval<CDate&>() -= 1), CDate&>);
//}
//
//TEST(CDateComparisonTests, EqualValidDates)
//{
//	CDate a(1, Month::JANUARY, 2010);
//	CDate b(1, Month::JANUARY, 2010);
//
//	EXPECT_TRUE(a == b);
//	EXPECT_FALSE(a != b);
//}
//
//TEST(CDateComparisonTests, DifferentValidDates)
//{
//	CDate a(1, Month::JANUARY, 2010);
//	CDate b(2, Month::JANUARY, 2010);
//
//	EXPECT_FALSE(a == b);
//	EXPECT_TRUE(a != b);
//}
//
//TEST(CDateComparisonTests, ValidAndInvalidAreNotEqual)
//{
//	CDate valid(1, Month::JANUARY, 2010);
//	CDate invalid(32, Month::JANUARY, 2010);
//
//	EXPECT_FALSE(valid == invalid);
//	EXPECT_TRUE(valid != invalid);
//
//	EXPECT_FALSE(invalid == valid);
//	EXPECT_TRUE(invalid != valid);
//}
//
//TEST(CDateComparisonTests, InvalidAndInvalidAreEqual)
//{
//	CDate a(32, Month::JANUARY, 2010);
//	CDate b(0, Month::FEBRUARY, 2020);
//
//	EXPECT_TRUE(a == b);
//	EXPECT_FALSE(a != b);
//}
//
//TEST(CDateComparisonTests, SameObjectIsEqualToItself)
//{
//	CDate date(28, Month::FEBRUARY, 2024);
//
//	EXPECT_TRUE(date == date);
//	EXPECT_FALSE(date != date);
//}
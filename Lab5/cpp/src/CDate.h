#pragma once

enum class Month
{
    JANUARY = 1, FEBRUARY, MARCH, APRIL,
    MAY, JUNE, JULY, AUGUST, SEPTEMBER,
    OCTOBER, NOVEMBER, DECEMBER
};

enum class WeekDay
{
    SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
    THURSDAY, FRIDAY, SATURDAY
};

class CDate
{
public:
    CDate(unsigned day, Month month, unsigned year);

    explicit CDate(unsigned timestamp);

    CDate();

    unsigned GetDay() const;

    Month GetMonth() const;

    unsigned GetYear() const;

    WeekDay GetWeekDay() const;

    bool IsValid() const;
};
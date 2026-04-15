#pragma once

#include <iosfwd>

enum class Month
{
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

enum class WeekDay
{
	SUNDAY = 0,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
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

	CDate& operator++();
	CDate& operator--();

	CDate operator++(int);
	CDate operator--(int);

	CDate operator+(int days) const;
	CDate operator-(int days) const;

	int operator-(const CDate& other) const;

	CDate& operator+=(int days);
	CDate& operator-=(int days);

	bool operator==(const CDate& other) const;
	bool operator!=(const CDate& other) const;

	bool operator<(const CDate& other) const;
	bool operator>(const CDate& other) const;
	bool operator<=(const CDate& other) const;
	bool operator>=(const CDate& other) const;

private:
	int m_timestamp = 0;
	bool m_isValid = true;
};

CDate operator+(int days, const CDate& date);

std::ostream& operator<<(std::ostream& os, const CDate& date);
std::istream& operator>>(std::istream& is, CDate& date);
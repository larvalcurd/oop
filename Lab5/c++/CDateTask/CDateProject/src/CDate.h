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

	//spaceship
	bool operator==(const CDate& other) const;
	bool operator!=(const CDate& other) const;

	bool operator<(const CDate& other) const;
	bool operator>(const CDate& other) const;
	bool operator<=(const CDate& other) const;
	bool operator>=(const CDate& other) const;

private:
	// здесь int, потому что operator-(const CDate&) возращает m_timestamp - other.m_timestamp
	// при отрицаительной разнице могло бы быть беззнаково переполнение
	// удобно при проверке на декремент if (m_timestamp <= 0), потому то читается лучше
	// максимальное значение 2 932 896 влезает в int, сужение при преобразовании из unsigned безопасно
	int m_timestamp = 0; 
	bool m_isValid = true;
};

CDate operator+(int days, const CDate& date);

std::ostream& operator<<(std::ostream& os, const CDate& date);
std::istream& operator>>(std::istream& is, CDate& date);
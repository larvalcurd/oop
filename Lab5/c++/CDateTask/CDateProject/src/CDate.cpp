#include "CDate.h"
#include <cctype>
#include <iomanip>
#include <istream>
#include <ostream>
#include <string>

namespace
{
constexpr unsigned MAX_TIMESTAMP = 2932896u; // 31.12.9999

struct DayMonthYear
{
	unsigned day;
	unsigned month;
	unsigned year;
};

DayMonthYear TimestampToDayMonthYear(int timestamp)
{
	// Сдвиг к "civil calendar" (алгоритм работает от 0000-03-01)
	long long days = static_cast<long long>(timestamp) + 719468;

	// 1. Считаем, сколько прошло 400-летних эпох
	const long long era = days / 146097;

	// 2. День внутри текущей эпохи [0, 146096]
	const unsigned dayOfEra = static_cast<unsigned>(days - era * 146097);

	// 3. Год внутри эпохи [0, 399]
	const unsigned yearOfEra = (dayOfEra
								   - dayOfEra / 1460
								   + dayOfEra / 36524
								   - dayOfEra / 146096)
		/ 365;

	// 4. Абсолютный год
	long long year = static_cast<long long>(yearOfEra) + era * 400;

	// 5. День года [0, 365]
	const unsigned dayOfYear = dayOfEra
		- (365 * yearOfEra + yearOfEra / 4 - yearOfEra / 100);

	// 6. Месяц (смещённый, март = 0)
	const unsigned monthPrime = (5 * dayOfYear + 2) / 153;

	// 7. День месяца
	const unsigned day = dayOfYear
		- (153 * monthPrime + 2) / 5 + 1;

	// 8. Нормальный месяц (1–12)
	const unsigned month = monthPrime + (monthPrime < 10 ? 3 : -9);

	// 9. Коррекция года (январь/февраль считаются концом прошлого года)
	year += (month <= 2);

	return DayMonthYear{
		day,
		month,
		static_cast<unsigned>(year)
	};
}

bool IsLeapYear(unsigned year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

unsigned DaysInMonth(unsigned year, Month month)
{
	switch (month)
	{
	case Month::JANUARY:
		return 31;
	case Month::FEBRUARY:
		return IsLeapYear(year) ? 29 : 28;
	case Month::MARCH:
		return 31;
	case Month::APRIL:
		return 30;
	case Month::MAY:
		return 31;
	case Month::JUNE:
		return 30;
	case Month::JULY:
		return 31;
	case Month::AUGUST:
		return 31;
	case Month::SEPTEMBER:
		return 30;
	case Month::OCTOBER:
		return 31;
	case Month::NOVEMBER:
		return 30;
	case Month::DECEMBER:
		return 31;
	}
	return 0;
}

unsigned LeapsBefore(unsigned year)
{
	return year / 4 - year / 100 + year / 400;
}

unsigned DaysBeforeYear(unsigned year)
{
	return 365u * (year - 1970u) + (LeapsBefore(year - 1u) - LeapsBefore(1969u));
}

unsigned DaysBeforeMonth(unsigned year, Month month)
{
	unsigned sum = 0;
	for (unsigned m = 1; m < static_cast<unsigned>(month); ++m)
	{
		sum += DaysInMonth(year, static_cast<Month>(m));
	}
	return sum;
}

bool IsAllDigits(const std::string& s, std::size_t begin, std::size_t count)
{
	for (std::size_t i = 0; i < count; ++i)
	{
		if (!std::isdigit(static_cast<unsigned char>(s[begin + i])))
		{
			return false;
		}
	}
	return true;
}

CDate MakeInvalidDate()
{
	return CDate(32, Month::JANUARY, 1970);
}

bool IsInRange(long long timestamp)
{
	return timestamp >= 0 && timestamp <= static_cast<long long>(MAX_TIMESTAMP);
}

} // namespace

CDate::CDate(unsigned day, Month month, unsigned year)
{
	if (year < 1970u || year > 9999u)
	{
		m_timestamp = 0;
		m_isValid = false;
		return;
	}

	const unsigned m = static_cast<unsigned>(month);
	if (m < 1u || m > 12u)
	{
		m_timestamp = 0;
		m_isValid = false;
		return;
	}

	const unsigned dim = DaysInMonth(year, month);
	if (day < 1u || day > dim)
	{
		m_timestamp = 0;
		m_isValid = false;
		return;
	}

	const unsigned ts = DaysBeforeYear(year) + DaysBeforeMonth(year, month) + (day - 1u);

	if (ts > MAX_TIMESTAMP)
	{
		m_timestamp = 0;
		m_isValid = false;
		return;
	}

	m_timestamp = static_cast<int>(ts);
	m_isValid = true;
}

CDate::CDate(unsigned timestamp)
{
	if (timestamp <= MAX_TIMESTAMP)
	{
		m_timestamp = static_cast<int>(timestamp);
		m_isValid = true;
	}
	else
	{
		m_timestamp = 0;
		m_isValid = false;
	}
}

CDate::CDate()
{
	m_timestamp = 0;
	m_isValid = true;
}

unsigned CDate::GetDay() const
{
	if (!m_isValid)
	{
		return 0;
	}
	return TimestampToDayMonthYear(m_timestamp).day;
}

Month CDate::GetMonth() const
{
	if (!m_isValid)
	{
		return Month::JANUARY;
	}
	return static_cast<Month>(TimestampToDayMonthYear(m_timestamp).month);
}

unsigned CDate::GetYear() const
{
	if (!m_isValid)
	{
		return 0;
	}
	return TimestampToDayMonthYear(m_timestamp).year;
}

WeekDay CDate::GetWeekDay() const
{
	if (!m_isValid)
	{
		return WeekDay::THURSDAY;
	}

	int index = (4 + m_timestamp) % 7;

	return static_cast<WeekDay>(index);
}

bool CDate::IsValid() const
{
	return m_isValid;
}

CDate& CDate::operator++()
{
	if (!m_isValid)
	{
		return *this;
	}

	if (m_timestamp >= static_cast<int>(MAX_TIMESTAMP))
	{
		m_timestamp = 0;
		m_isValid = false;
		return *this;
	}

	++m_timestamp;
	return *this;
}

CDate& CDate::operator--()
{
	if (!m_isValid)
	{
		return *this;
	}

	if (m_timestamp <= 0)
	{
		m_timestamp = 0;
		m_isValid = false;
		return *this;
	}

	--m_timestamp;
	return *this;
}

CDate CDate::operator++(int)
{
	CDate old = *this;
	++(*this);
	return old;
}

CDate CDate::operator--(int)
{
	CDate old = *this;
	--(*this);
	return old;
}

CDate CDate::operator+(int days) const
{
	if (!m_isValid)
	{
		return MakeInvalidDate();
	}

	const long long newTimestamp = static_cast<long long>(m_timestamp) + days;

	if (!IsInRange(newTimestamp))
	{
		return MakeInvalidDate();
	}

	return CDate(static_cast<unsigned>(newTimestamp));
}

int CDate::operator-(const CDate& other) const
{
	if (!m_isValid || !other.m_isValid)
	{
		return 0;
	}

	return m_timestamp - other.m_timestamp;
}

CDate& CDate::operator+=(int days)
{
	if (!m_isValid)
	{
		return *this;
	}

	*this = *this + days;
	return *this;
}

CDate& CDate::operator-=(int days)
{
	if (!m_isValid)
	{
		return *this;
	}

	*this = *this - days;
	return *this;
}

bool CDate::operator==(const CDate& other) const
{
	if (m_isValid != other.m_isValid)
	{
		return false;
	}

	if (!m_isValid)
	{
		return true;
	}

	return m_timestamp == other.m_timestamp;
}

bool CDate::operator!=(const CDate& other) const
{
	return !(*this == other);
}

bool CDate::operator<(const CDate& other) const
{
	if (!m_isValid || !other.m_isValid)
	{
		return false;
	}

	return m_timestamp < other.m_timestamp;
}

bool CDate::operator>(const CDate& other) const
{
	return other < *this;
}

bool CDate::operator<=(const CDate& other) const
{
	return (*this < other) || (*this == other);
}

bool CDate::operator>=(const CDate& other) const
{
	return (*this > other) || (*this == other);
}

CDate operator+(int days, const CDate& date)
{
	return date + days;
}

CDate CDate::operator-(int days) const
{
	return *this + (-days);
}

std::ostream& operator<<(std::ostream& os, const CDate& date)
{
	if (!date.IsValid())
	{
		os << "INVALID";
		return os;
	}

	const unsigned day = date.GetDay();
	const unsigned month = static_cast<unsigned>(date.GetMonth());
	const unsigned year = date.GetYear();

	os << std::setfill('0')
	   << std::setw(2) << day << '.'
	   << std::setw(2) << month << '.'
	   << std::setw(4) << year;

	return os;
}

std::istream& operator>>(std::istream& is, CDate& date)
{
	std::string token;
	if (!(is >> token))
	{
		return is;
	}

	if (token == "INVALID")
	{
		date = MakeInvalidDate();
		return is;
	}

	if (token.size() != 10 || token[2] != '.' || token[5] != '.' || !IsAllDigits(token, 0, 2) || !IsAllDigits(token, 3, 2) || !IsAllDigits(token, 6, 4))
	{
		is.setstate(std::ios::failbit);
		return is;
	}

	const unsigned day = static_cast<unsigned>(std::stoi(token.substr(0, 2)));
	const unsigned monthNumber = static_cast<unsigned>(std::stoi(token.substr(3, 2)));
	const unsigned year = static_cast<unsigned>(std::stoi(token.substr(6, 4)));

	const CDate parsed(day, static_cast<Month>(monthNumber), year);

	if (!parsed.IsValid())
	{
		date = parsed;
		//is.setstate(std::ios::failbit);
		return is;
	}

	date = parsed;
	return is;
}
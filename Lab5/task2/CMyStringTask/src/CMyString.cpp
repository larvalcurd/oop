#include "CMyString.h"

#include <cctype>
#include <istream>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <utility>

char CMyString::s_emptyString[1] = { '\0' };

CMyString::CMyString() = default;

// Копируем ровно length символов; pString должен указывать на буфер длиной не меньше length.
CMyString::CMyString(const char* pString, size_t length)
{
	if (pString != nullptr && length == std::numeric_limits<size_t>::max())
	{
		throw std::length_error("String length is too large");
	}

	if (pString == nullptr || length == 0)
	{
		return;
	}

	m_length = length;
	m_capacity = length;
	m_data = new char[length + 1];

	std::memcpy(m_data, pString, length);
	m_data[length] = '\0';
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, [](const char* str) {
		if (str == nullptr)
		{
			return size_t(0);
		}
		size_t len = 0;
		while (str[len] != '\0')
		{
			++len;
		}
		return len;
	}(pString))
{
}

CMyString::CMyString(const std::string& stlString)
	: CMyString(stlString.data(), stlString.size())
{
}
// почему передаю по конастантной ссылке
CMyString::CMyString(const CMyString& other)
{
	if (other.m_length == 0)
	{
		return;
	}
	else
	{
		m_capacity = other.m_capacity;
		m_length = other.m_length;
		m_data = new char[m_capacity + 1];
		std::memcpy(m_data, other.m_data, m_length);
		m_data[m_length] = '\0';
	}
}

CMyString::CMyString(CMyString&& other) noexcept
	: m_data(other.m_data)
	, m_length(other.m_length)
	, m_capacity(other.m_capacity)
{
	other.ResetToEmpty();
}

CMyString::~CMyString()
{
	if (m_data != s_emptyString)
	{
		delete[] m_data;
	}
}

CMyString& CMyString::operator=(const CMyString& other)
{
	if (this != &other)
	{
		CMyString temp(other);
		Swap(temp);
	}
	return *this;
}
CMyString& CMyString::operator=(CMyString&& other) noexcept
{
	if (this != &other)
	{
		CMyString temp(std::move(other));
		Swap(temp);
	}
	return *this;
}

size_t CMyString::GetLength() const
{
	return m_length;
}

size_t CMyString::GetCapacity() const
{
	return m_capacity;
}

const char* CMyString::GetStringData() const
{
	return m_data;
}

char& CMyString::operator[](size_t index)
{
	if (index >= m_length)
	{
		throw std::out_of_range("Index out of range");
	}
	return m_data[index];
}

const char& CMyString::operator[](size_t index) const
{
	if (index >= m_length)
	{
		throw std::out_of_range("Index out of range");
	}
	return m_data[index];
}

void CMyString::Clear()
{
	if (m_data != s_emptyString)
	{
		delete[] m_data;
	}

	ResetToEmpty();
}

void CMyString::ResetToEmpty() noexcept
{
	m_data = s_emptyString;
	m_length = 0;
	m_capacity = 0;
}

CMyString& CMyString::operator+=(const CMyString& other)
{
	if (other.m_length == 0)
	{
		return *this;
	}

	if (this == &other)
	{
		size_t oldLength = m_length;
		size_t newLength = m_length + oldLength;

		EnsureCapacity(newLength);

		for (size_t i = 0; i < oldLength; ++i)
		{
			m_data[oldLength + i] = m_data[i];
		}

		m_length = newLength;
		m_data[m_length] = '\0';

		return *this;
	}

	size_t oldLength = m_length;
	size_t newLength = m_length + other.m_length;

	EnsureCapacity(newLength);

	std::memcpy(m_data + oldLength, other.m_data, other.m_length);

	m_length = newLength;
	m_data[m_length] = '\0';

	return *this;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start >= m_length)
	{
		return CMyString();
	}

	size_t maxLength = m_length - start;
	size_t substringLength = (length < maxLength) ? length : maxLength;

	return CMyString(m_data + start, substringLength);
}

int CMyString::Compare(const CMyString& other) const
{
	size_t minLength = (m_length < other.m_length) ? m_length : other.m_length;

	for (size_t i = 0; i < minLength; ++i)
	{
		unsigned char c1 = static_cast<unsigned char>(m_data[i]);
		unsigned char c2 = static_cast<unsigned char>(other.m_data[i]);

		if (c1 != c2)
		{
			return c1 - c2;
		}
	}

	return static_cast<int>(m_length) - static_cast<int>(other.m_length);
}

bool operator==(const CMyString& lhs, const CMyString& rhs)
{
	return lhs.Compare(rhs) == 0;
}

bool operator!=(const CMyString& lhs, const CMyString& rhs)
{
	return lhs.Compare(rhs) != 0;
}

bool operator<(const CMyString& lhs, const CMyString& rhs)
{
	return lhs.Compare(rhs) < 0;
}

bool operator<=(const CMyString& lhs, const CMyString& rhs)
{
	return lhs.Compare(rhs) <= 0;
}

bool operator>(const CMyString& lhs, const CMyString& rhs)
{
	return lhs.Compare(rhs) > 0;
}

bool operator>=(const CMyString& lhs, const CMyString& rhs)
{
	return lhs.Compare(rhs) >= 0;
}

CMyString operator+(const CMyString& lhs, const CMyString& rhs)
{
	CMyString result(lhs);
	result += rhs;
	return result;
}

CMyString operator+(const std::string& lhs, const CMyString& rhs)
{
	CMyString temp(lhs);
	return temp + rhs;
}

CMyString operator+(const char* lhs, const CMyString& rhs)
{
	CMyString temp(lhs);
	return temp + rhs;
}

std::ostream& operator<<(std::ostream& os, const CMyString& str)
{
	os.write(str.GetStringData(), static_cast<std::streamsize>(str.GetLength()));
	return os;
}

std::istream& operator>>(std::istream& is, CMyString& str)
{
	std::istream::sentry sentry(is);
	if (!sentry)
	{
		return is;
	}

	CMyString temp;
	bool extracted = false;

	while (true)
	{
		int ch = is.peek();

		if (ch == std::char_traits<char>::eof())
		{
			break;
		}

		if (std::isspace(static_cast<unsigned char>(ch)))
		{
			break;
		}

		temp.PushBack(static_cast<char>(is.get()));
		extracted = true;
	}

	if (!extracted)
	{
		is.setstate(std::ios::failbit);
	}
	else
	{
		str = std::move(temp);
	}

	return is;
}

void CMyString::Swap(CMyString& other) noexcept
{
	std::swap(m_data, other.m_data);
	std::swap(m_length, other.m_length);
	std::swap(m_capacity, other.m_capacity);
}

void CMyString::EnsureCapacity(size_t requiredLength)
{
	if (requiredLength <= m_capacity)
	{
		return;
	}

	size_t newCapacity = m_capacity == 0 ? 1 : m_capacity;

	while (newCapacity < requiredLength)
	{
		newCapacity *= 2;
	}

	char* newData = new char[newCapacity + 1];

	std::memcpy(newData, m_data, m_length);
	newData[m_length] = '\0';

	if (m_data != s_emptyString)
	{
		delete[] m_data;
	}

	m_data = newData;
	m_capacity = newCapacity;
}

void CMyString::PushBack(char ch)
{
	EnsureCapacity(m_length + 1);
	m_data[m_length] = ch;
	++m_length;
	m_data[m_length] = '\0';
}

CMyString::Iterator CMyString::begin()
{
	return Iterator(m_data, m_data, m_data + m_length);
}

CMyString::Iterator CMyString::end()
{
	return Iterator(m_data + m_length, m_data, m_data + m_length);
}

CMyString::ConstIterator CMyString::begin() const
{
	return ConstIterator(m_data, m_data, m_data + m_length);
}

CMyString::ConstIterator CMyString::end() const
{
	return ConstIterator(m_data + m_length, m_data, m_data + m_length);
}

CMyString::ConstIterator CMyString::cbegin() const
{
	return begin();
}

CMyString::ConstIterator CMyString::cend() const
{
	return end();
}

CMyString::ReverseIterator CMyString::rbegin()
{
	return ReverseIterator(end());
}

CMyString::ReverseIterator CMyString::rend()
{
	return ReverseIterator(begin());
}

CMyString::ConstReverseIterator CMyString::rbegin() const
{
	return ConstReverseIterator(end());
}

CMyString::ConstReverseIterator CMyString::rend() const
{
	return ConstReverseIterator(begin());
}

CMyString::ConstReverseIterator CMyString::crbegin() const
{
	return rbegin();
}

CMyString::ConstReverseIterator CMyString::crend() const
{
	return rend();
}

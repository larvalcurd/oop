#include "CMyString.h"

#include <ostream>
#include <istream>
#include <cctype>
#include <utility>
#include <stdexcept>

CMyString::CMyString()
	: m_data(s_emptyString)
	, m_length(0)
	, m_capacity(0)
{
}

CMyString::~CMyString()
{
	if (m_data != s_emptyString)
	{
		delete[] m_data;
	}
}

CMyString::CMyString(const char* pString)
{
	size_t len = 0;
	if (pString != nullptr)
	{
		while (pString[len] != '\0')
		{
			++len;
		}
	}

	if (len == 0)
	{
		m_data = s_emptyString;
		m_length = 0;
		m_capacity = 0;
	}
	else
	{
		m_data = new char[len + 1];

		for (size_t i = 0; i < len; ++i)
		{
			m_data[i] = pString[i];
		}
		m_data[len] = '\0';
		m_length = len;
		m_capacity = len;
	}
}

CMyString::CMyString(const char* pString, size_t length)
{
	if (pString == nullptr || length == 0)
    {
        m_data = s_emptyString;
        m_length = 0;
        m_capacity = 0;
    }
	else
	{
		m_data = new char[length + 1];
		for (size_t i = 0; i < length; ++i)
		{
			m_data[i] = pString[i];
		}
		m_data[length] = '\0';
		m_length = length;
		m_capacity = length;
	}
}

CMyString::CMyString(const std::string& stlString)
    : CMyString(stlString.data(), stlString.size())
{
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	return m_data;
}

size_t CMyString::GetCapacity() const
{
	return m_capacity;
}

void CMyString::Clear()
{
	if (m_data != s_emptyString)
	{
		delete[] m_data; 
	}
	m_data = s_emptyString;
	m_length = 0;
	m_capacity = 0;
}
    
void CMyString::Swap(CMyString& other) noexcept
{
	std::swap(m_data, other.m_data);
	std::swap(m_length, other.m_length);
	std::swap(m_capacity, other.m_capacity);
}


CMyString::CMyString(const CMyString& other)
{
    if (other.m_length == 0)
    {
        m_data = s_emptyString;
        m_length = 0;
        m_capacity = 0;
    }
    else
    {
        m_capacity = other.m_capacity; 
        m_length = other.m_length;
        m_data = new char[m_capacity + 1]; 
        for (size_t i = 0; i < m_length; ++i)
        {
            m_data[i] = other.m_data[i];
        }
        m_data[m_length] = '\0';
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

CMyString& CMyString::operator+=(const CMyString& other)
{
    if (other.m_length == 0)
    {
        return *this; 
    }

    size_t newLength = m_length + other.m_length;
    EnsureCapacity(newLength); 

    for (size_t i = 0; i < other.m_length; ++i)
    {
        m_data[m_length + i] = other.m_data[i];
    }
    m_length = newLength;
    m_data[m_length] = '\0'; 

    return *this;
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

void CMyString::EnsureCapacity(size_t requredLength)
{
    if (requredLength <= m_capacity)
    {
        return;
    }  
    
    size_t newCapacity = m_capacity == 0 ? 1 : m_capacity;

    while (newCapacity < requredLength)
    {
        newCapacity *= 2;
    }

    char* newData = new char [newCapacity + 1];

    for (size_t i = 0; i < m_length; ++i)
    {
        newData[i] = m_data[i];
    }
    newData[m_length] = '\0';

    if (m_data != s_emptyString)
    {
        delete[] m_data;
    }

    m_data = newData;
    m_capacity = newCapacity;
}

CMyString::CMyString(CMyString&& other) noexcept
    : m_data(other.m_data)
    , m_length(other.m_length)
    , m_capacity(other.m_capacity)
{
    other.m_data = s_emptyString;
    other.m_length = 0;
    other.m_capacity = 0;
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
    if (this != &other)
    {
        if (m_data != s_emptyString)
        {
            delete[] m_data;
        }
        m_data = other.m_data;
        m_length = other.m_length;
        m_capacity = other.m_capacity;

        other.m_data = s_emptyString;
        other.m_length = 0;
        other.m_capacity = 0;
    }
    return *this;
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
    return !(lhs == rhs);
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

CMyString CMyString::Substring(size_t start, size_t length) const
{
    if (start >= m_length)
    {
        return CMyString(); 
    }

    size_t maxLength = m_length - start;
    size_t substringLength = (length < maxLength) ? length : maxLength;

    return CMyString(m_data + start, substringLength);
}

void CMyString::PushBack(char ch)
{
    EnsureCapacity(m_length + 1);
    m_data[m_length] = ch;
    ++m_length;
    m_data[m_length] = '\0';
}

std::ostream& operator<<(std::ostream& os, const CMyString& str)
{
    os.write(str.m_data, static_cast<std::streamsize>(str.m_length));
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

char CMyString::s_emptyString[1] = { '\0' };
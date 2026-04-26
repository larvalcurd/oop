#pragma once

#include <string>
#include <cstddef>
#include <iosfwd>

class CMyString
{
public:
    CMyString();
    CMyString(const char* pString);
    CMyString(const char* pString, size_t length);
    CMyString(const std::string& stlString);

    CMyString(const CMyString& other);
    CMyString(CMyString&& other) noexcept;
    ~CMyString();

    CMyString& operator=(const CMyString& other);
    CMyString& operator=(CMyString&& other) noexcept;

    size_t GetLength() const;
    size_t GetCapacity() const;
    const char* GetStringData() const;
    void Clear();

    char& operator[](size_t index);
    const char& operator[](size_t index) const;
    CMyString& operator+=(const CMyString& other);

    int Compare(const CMyString& other) const;
    CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

private:
    void Swap(CMyString& other) noexcept;
    void EnsureCapacity(size_t requiredLength);
    void PushBack(char ch);

    char* m_data;
    size_t m_length;
    size_t m_capacity;

    static char s_emptyString[1];

    friend std::ostream& operator<<(std::ostream& os, const CMyString& str);
    friend std::istream& operator>>(std::istream& is, CMyString& str);
};

bool operator==(const CMyString& lhs, const CMyString& rhs);
bool operator!=(const CMyString& lhs, const CMyString& rhs);
bool operator<(const CMyString& lhs, const CMyString& rhs);
bool operator<=(const CMyString& lhs, const CMyString& rhs);
bool operator>(const CMyString& lhs, const CMyString& rhs);
bool operator>=(const CMyString& lhs, const CMyString& rhs);

CMyString operator+(const CMyString& lhs, const CMyString& rhs);
CMyString operator+(const std::string& lhs, const CMyString& rhs);
CMyString operator+(const char* lhs, const CMyString& rhs);

std::ostream& operator<<(std::ostream& os, const CMyString& str);
std::istream& operator>>(std::istream& is, CMyString& str);

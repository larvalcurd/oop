#pragma once

#include <cstddef>
#include <iosfwd>
#include <string>

#include <cassert>
#include <cstddef>
#include <iterator>

template <bool IsConst>
class StringIterator
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = char;
	using difference_type = std::ptrdiff_t;
	using pointer = std::conditional_t<IsConst, const char*, char*>;
	using reference = std::conditional_t<IsConst, const char&, char&>;

	StringIterator(pointer ptr, pointer begin, pointer end)
		: m_ptr(ptr)
		, m_begin(begin)
		, m_end(end)
	{
	}

	template <bool OtherConst, typename = std::enable_if_t<IsConst && !OtherConst>>
	StringIterator(const StringIterator<OtherConst>& other)
		: m_ptr(other.m_ptr)
		, m_begin(other.m_begin)
		, m_end(other.m_end)
	{
	}

	reference operator*() const
	{
		assert(m_ptr >= m_begin && m_ptr < m_end && "Dereferencing out of range");
		return *m_ptr;
	}

	pointer operator->() const
	{
		assert(m_ptr >= m_begin && m_ptr < m_end && "Dereferencing out of range");
		return m_ptr;
	}

	reference operator[](difference_type n) const
	{
		pointer target = m_ptr + n;
		assert(target >= m_begin && target < m_end && "Indexing out of range");
		return m_ptr[n];
	}

	StringIterator& operator++()
	{
		assert(m_ptr < m_end && "Incrementing past end");
		++m_ptr;
		return *this;
	}

	StringIterator operator++(int)
	{
		assert(m_ptr < m_end && "Incrementing past end");
		StringIterator temp = *this;
		++m_ptr;
		return temp;
	}

	StringIterator& operator--()
	{
		assert(m_ptr > m_begin && "Decrementing before begin");
		--m_ptr;
		return *this;
	}

	StringIterator operator--(int)
	{
		assert(m_ptr > m_begin && "Decrementing before begin");
		StringIterator temp = *this;
		--m_ptr;
		return temp;
	}

	StringIterator operator+(difference_type n) const
	{
		pointer target = m_ptr + n;
		assert(target >= m_begin && target <= m_end && "Iterator + n out of range");
		return StringIterator(target, m_begin, m_end);
	}

	StringIterator operator-(difference_type n) const
	{
		pointer target = m_ptr - n;
		assert(target >= m_begin && target <= m_end && "Iterator - n out of range");
		return StringIterator(target, m_begin, m_end);
	}

	StringIterator& operator+=(difference_type n)
	{
		pointer target = m_ptr + n;
		assert(target >= m_begin && target <= m_end && "Iterator += n out of range");
		m_ptr = target;
		return *this;
	}

	StringIterator& operator-=(difference_type n)
	{
		pointer target = m_ptr - n;
		assert(target >= m_begin && target <= m_end
			&& "Iterator -= n out of range");
		m_ptr = target;
		return *this;
	}

	template <bool OtherConst>
	difference_type operator-(const StringIterator<OtherConst>& other) const
	{
		return m_ptr - other.m_ptr;
	}

	template <bool OtherConst>
	bool operator==(const StringIterator<OtherConst>& other) const
	{
		assert(m_begin == other.m_begin && "Comparing iterators from different containers");
		return m_ptr == other.m_ptr;
	}

	template <bool OtherConst>
	auto operator<=>(const StringIterator<OtherConst>& other) const
	{
		assert(m_begin == other.m_begin && "Comparing iterators from different containers");
		return m_ptr <=> other.m_ptr;
	}

private:
	template <bool>
	friend class StringIterator;

	pointer m_ptr;
	pointer m_begin;
	pointer m_end;
};

template <bool IsConst>
StringIterator<IsConst> operator+(
	typename StringIterator<IsConst>::difference_type n,
	const StringIterator<IsConst>& it)
{
	return it + n;
}
class CMyString
{
public:
	using Iterator = StringIterator<false>;
	using ConstIterator = StringIterator<true>;
	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

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
	void PushBack(char ch);

	char& operator[](size_t index);
	const char& operator[](size_t index) const;
	CMyString& operator+=(const CMyString& other);

	int Compare(const CMyString& other) const;
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;
	ConstIterator cbegin() const;
	ConstIterator cend() const;

	ReverseIterator rbegin();
	ReverseIterator rend();
	ConstReverseIterator rbegin() const;
	ConstReverseIterator rend() const;
	ConstReverseIterator crbegin() const;
	ConstReverseIterator crend() const;

private:
	void Swap(CMyString& other) noexcept;
	void EnsureCapacity(size_t requiredLength);

	void ResetToEmpty() noexcept;

	static char s_emptyString[1];

	char* m_data = s_emptyString;
	size_t m_length = 0;
	size_t m_capacity = 0;
};
// способы перегрузки
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

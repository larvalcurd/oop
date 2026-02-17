#include "radix.h"

#include <algorithm>
#include <cctype>
#include <limits>

namespace
{
const int INVALID_DIGIT = -1;
const char INVALID_CHAR = '?';
constexpr long long INT_MAX_LL = std::numeric_limits<int>::max();
constexpr long long INT_MIN_LL = std::numeric_limits<int>::min();

bool IsPositiveSign(char c)
{
	return c == '+';
}

bool IsNegativeSign(char c)
{
	return c == '-';
}

bool IsSign(char c)
{
	return IsPositiveSign(c) || IsNegativeSign(c);
}

bool WouldOverFlowPositive(long long currentAcc, int digit, int radix)
{
	return currentAcc > (INT_MAX_LL - digit) / radix;
}

bool WouldOverFlowNegative(long long currentAcc, int digit, int radix)
{
	constexpr long long NEGATIVE_LIMIT = -INT_MIN_LL;
	return currentAcc > (NEGATIVE_LIMIT - digit) / radix;
}
} // namespace

bool IsValidRadix(int radix)
{
	return radix >= MIN_RADIX && radix <= MAX_RADIX;
}

int CharToDigit(char c)
{
	const char upper = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));

	if (upper >= '0' && upper <= '9')
	{
		return upper - '0';
	}

	if (upper >= 'A' && upper <= 'Z')
	{
		return upper - 'A' + 10;
	}

	return INVALID_DIGIT;
}

char DigitToChar(int digit)
{
	if (digit >= 0 && digit <= 9)
	{
		return static_cast<char>('0' + digit);
	}

	if (digit >= 10 && digit < MAX_RADIX)
	{
		return static_cast<char>('A' + digit - 10);
	}

	return INVALID_CHAR;
}

int StringToInt(const std::string& str, int radix, bool& wasError)
{
	wasError = false;

	if (!IsValidRadix(radix) || str.empty())
	{
		wasError = true;
		return 0;
	}

	size_t pos = 0;
	const bool isNegative = IsNegativeSign(str[0]);

	if (IsSign(str[0]))
	{
		pos++;
		if (pos >= str.size())
		{
			wasError = true;
			return 0;
		}
	}

	long long accumulator = 0;

	for (; pos < str.size(); pos++)
	{
		const int digit = CharToDigit(str[pos]);

		if (digit == INVALID_DIGIT || digit >= radix)
		{
			wasError = true;
			return 0;
		}

		const bool wouldOverflow = isNegative
			? WouldOverFlowNegative(accumulator, digit, radix)
			: WouldOverFlowPositive(accumulator, digit, radix);

		if (wouldOverflow)
		{
			wasError = true;
			return 0;
		}

		accumulator = accumulator * radix + digit;
	}

	const long long result = isNegative ? -accumulator : accumulator;

	return static_cast<int>(result);
}

std::string IntToString(int n, int radix, bool& wasError)
{
	wasError = false;

	if (!IsValidRadix(radix))
	{
		//wasError = true;
		return "";
	}

	if (n == 0)
	{
		return "0";
	}

	const bool isNegative = n < 0;
	long long absoluteValue = isNegative ? -static_cast<long long>(n) : static_cast<long long>(n);

	std::string result;

	while (absoluteValue > 0)
	{
		const int digit = static_cast<int>(absoluteValue % radix);
		result.push_back(DigitToChar(digit));
		absoluteValue /= radix;
	}

	if (isNegative)
	{
		result.push_back('-');
	}

	std::reverse(result.begin(), result.end());

	return result;
}

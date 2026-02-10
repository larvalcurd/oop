#include "radix.h"

int StringToInt(const std::string& str, int radix, bool& wasError)
{
	wasError = false;

	if (!ValidateRadix(radix))
	{
		wasError = true;
		return 0;
	}

	if (str.empty())
	{
		wasError = true;
		return 0;
	}

	int sign = 1;
	size_t i = 0;

	if (str[0] == '+' || str[0] == '-')
	{
		if (str[0] == '-') sign = -1;
		i++;

		if (i == str.size())
		{
			wasError = true;
			return 0;
		}
	}

	long long acc = 0;
	const long long INT_MAX_LL = std::numeric_limits<int>::max();
	const long long INT_MIN_LL = std::numeric_limits<int>::min();

	for (; i < str.size(); i++)
	{
		int digit = CharToDigit(str[i]);
		if (digit < 0 || digit >= radix)
		{
			wasError = true;
			return 0;
		}

		if (sign > 0)
		{
			if (acc > (INT_MAX_LL - digit) / radix)
			{
				wasError = true;
				return 0;
			}
		}
		else
		{
			long long limit = -(long long)INT_MIN_LL;
			if (acc > (limit - digit) / radix)
			{
				wasError = true;
				return 0;
			}
		}

		acc = acc * radix + digit;
	}

	long long result = sign * acc;

	if (result < INT_MIN_LL || result > INT_MAX_LL)
	{
		wasError = true;
		return 0;
	}

	return (int)result;
}

std::string IntToString(int n, int radix, bool& wasError)
{
	wasError = false;

	if (!ValidateRadix(radix))
	{
		wasError = true;
		return "";
	}

	if (n == 0)
		return "0";

	bool isNegative = n < 0;
	long long nn = isNegative ? -(long long)n : (long long)n;

	std::string result;

	while (nn > 0)
	{
		int digit = static_cast<int>(nn % radix);
		result += DigitToChar(digit);
		nn /= radix;
	}

	if (isNegative)
		result += '-';

	std::reverse(result.begin(), result.end());
	return result;
}

int CharToDigit(char c)
{
	c = toupper(static_cast<unsigned char>(c));

	if (c >= '0' && c <= '9')
		return c - '0';

	if (c >= 'A' && c <= 'Z')
		return c - 'A' + 10;

	return -1;
}

char DigitToChar(int digit)
{
	if (digit >= 0 && digit <= 9)
		return '0' + digit;

	if (digit >= 10 && digit < 36)
		return 'A' + (digit - 10);

	return '?';
}

bool ValidateRadix(int radix)
{
	return radix >= 2 && radix <= 36;
}
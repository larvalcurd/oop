#include "StringUtils.h"
#include <cctype>


//А-П: D0 90–D0 9F
//Р-Я: D0 A0–D0 AF
//Ё:   D0 81
//а-п: D0 B0–D0 BF
//р-я: D1 80–D1 8F
//ё:   D1 91
std::string toLower(std::string_view str)
{
	std::string result;
	result.reserve(str.size());

	for (size_t i = 0; i < str.size(); ++i)
	{
		const auto c = static_cast<unsigned char>(str[i]);

		// UTF-8 кириллица — двухбайтовые последовательности 0xD0/0xD1
		if (i + 1 < str.size() && (c == 0xD0 || c == 0xD1))
		{
			const auto next = static_cast<unsigned char>(str[i + 1]);

			if (c == 0xD0)
			{
				// А-П (0xD0 0x90-0x9F) → а-п (0xD0 0xB0-0xBF)
				if (next >= 0x90 && next <= 0x9F)
				{
					result += static_cast<char>(0xD0);
					result += static_cast<char>(next + 0x20);
					++i;
					continue;
				}
				// Р-Я (0xD0 0xA0-0xAF) → р-я (0xD1 0x80-0x8F)
				if (next >= 0xA0 && next <= 0xAF)
				{
					result += static_cast<char>(0xD1);
					result += static_cast<char>(next - 0x20);
					++i;
					continue;
				}
				// Ё (0xD0 0x81) → ё (0xD1 0x91)
				if (next == 0x81)
				{
					result += static_cast<char>(0xD1);
					result += static_cast<char>(0x91);
					++i;
					continue;
				}
			}

			// Уже строчная кириллица или другой символ — копируем как есть
			result += static_cast<char>(c);
			result += static_cast<char>(next);
			++i;
			continue;
		}

		// ASCII — стандартный toLower
		result += static_cast<char>(std::tolower(c));
	}

	return result;
}

std::string trim(std::string_view str)
{
	const size_t start = str.find_first_not_of(" \t\r\n");
	if (start == std::string_view::npos)
		return {};
	const size_t end = str.find_last_not_of(" \t\r\n");
	return std::string(str.substr(start, end - start + 1));
}

bool hasCyrillic(std::string_view str)
{
	for (size_t i = 0; i + 1 < str.size(); ++i)
	{
		const auto c = static_cast<unsigned char>(str[i]);
		const auto next = static_cast<unsigned char>(str[i + 1]);

		if ((c == 0xD0 || c == 0xD1) && next >= 0x80 && next <= 0xBF)
			return true;
	}
	return false;
}
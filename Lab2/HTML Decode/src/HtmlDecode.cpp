#include "HtmlDecode.h"
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>

namespace
{

struct HtmlEntity
{
	std::string_view encoded;
	char decoded;
};

constexpr std::array<HtmlEntity, 5> HTML_ENTITIES = { { 
	{ "&lt;", '<' },
	{ "&gt;", '>' },
	{ "&amp;", '&' },
	{ "&quot;", '"' },
	{ "&apos;", '\'' } 
} };

constexpr size_t CalculateMaxEntityLength()
{
	size_t maxLen = 0;
	for (const auto& entity : HTML_ENTITIES)
	{
		if (entity.encoded.size() > maxLen)
		{
			maxLen = entity.encoded.size();
		}
	}
	return maxLen;
}

constexpr size_t MAX_ENTITY_LENGTH = CalculateMaxEntityLength();

std::optional<char> TryDecodeEntity(std::string_view entity)
{
	for (const auto& [encoded, decoded] : HTML_ENTITIES)
	{
		if (entity == encoded)
		{
			return decoded;
		}
	}
	return std::nullopt;
}

} // namespace

std::string HtmlDecode(const std::string& html)
{
	std::string result;
	result.reserve(html.size());

	size_t i = 0;
	while (i < html.size())
	{
		if (html[i] != '&')
		{
			result += html[i];
			++i;
			continue;
		}

		size_t maxEnd = std::min(i + MAX_ENTITY_LENGTH, html.size());
		size_t semicolonPos = std::string::npos;

		for (size_t j = i + 1; j < maxEnd; ++j)
		{
			if (html[j] == '&')
			{
				break;
			}

			if (html[j] == ';')
			{
				semicolonPos = j;
				break;
			}
		}

		if (semicolonPos == std::string::npos)
		{
			result += html[i];
			++i;
			continue;
		}

		std::string_view entity(&html[i], semicolonPos - i + 1);
		auto decoded = TryDecodeEntity(entity);

		if (decoded.has_value())
		{
			result += decoded.value();
		}
		else
		{
			result += entity;
		}

		i = semicolonPos + 1;
	}

	return result;
}
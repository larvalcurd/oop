#include "HtmlDecode.h"
#include <algorithm>

std::optional<char> TryDecodeEntity(const std::string& entity)
{
	if (entity == "&lt;")
		return '<';
	if (entity == "&gt;")
		return '>';
	if (entity == "&amp;")
		return '&';
	if (entity == "&quot;")
		return '"';
	if (entity == "&apos;")
		return '\'';
	return std::nullopt;
}

std::string HtmlDecode(const std::string& html)
{
	constexpr size_t MAX_ENTITY_LENGTH = 6;

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

		std::string entity = html.substr(i, semicolonPos - i + 1);
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
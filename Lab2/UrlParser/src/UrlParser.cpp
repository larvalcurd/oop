#include "UrlParser.h"
#include <algorithm>
#include <cassert>
#include <cctype>
#include <regex>
#include <string>

namespace
{
int GetDefaultPort(Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return 80;
	case Protocol::HTTPS:
		return 443;
	case Protocol::FTP:
		return 21;
	}

	assert(false && "Bug: unhandled Protocol value");
	return 0;
}

std::string ToLower(const std::string& str)
{
	std::string result = str;
	std::transform(result.begin(), result.end(), result.begin(),
		[](unsigned char c) { return std::tolower(c); });
	return result;
}

bool ParseProtocol(const std::string& str, Protocol& protocol)
{
	const std::string lower = ToLower(str);
	if (lower == "http")
	{
		protocol = Protocol::HTTP;
		return true;
	}
	if (lower == "https")
	{
		protocol = Protocol::HTTPS;
		return true;
	}
	if (lower == "ftp")
	{
		protocol = Protocol::FTP;
		return true;
	}
	return false;
}

bool ParsePort(const std::string& str, int& port)
{
	if (str.empty())
	{
		return false;
	}

	for (char c : str)
	{
		if (!std::isdigit(static_cast<unsigned char>(c)))
		{
			return false;
		}
	}

	if (str.length() > 1 && str[0] == '0')
	{
		return false;
	}

	if (str.length() > 5)
	{
		return false;
	}

	const unsigned long value = std::stoul(str);

	if (value < 1 || value > 65535)
	{
		return false;
	}

	port = static_cast<int>(value);
	return true;
}
} // namespace

//^        — начало строки
//$        — конец строки
//()       — группа захвата (результат можно извлечь)
//(?:)     — группа БЕЗ захвата (только для группировки)
//[]       — класс символов (любой из перечисленных)
//[^]      — отрицание класса (любой КРОМЕ перечисленных)
//?        — 0 или 1 раз (необязательно)
//+        — 1 или более раз
//*        — 0 или более раз
//\d       — цифра (0-9)
//.        — любой символ
//|        — ИЛИ

bool ParseURL(
	const std::string& url,
	Protocol& protocol,
	int& port,
	std::string& host,
	std::string& document)
{
	static const std::regex urlRegex(
		[]() {
			const std::string start = R"(^)";
			const std::string protocol = R"((http|https|ftp))";
			const std::string separator = R"(://)";
			const std::string host = R"(([^/:]+))";
			const std::string port = R"((?::(\d+))?)";
			const std::string document = R"((?:/(.*))?)";
			const std::string end = R"($)";

			return start + protocol + separator + host + port + document + end;
		}(),
		std::regex_constants::icase);

	std::smatch match;
	if (!std::regex_match(url, match, urlRegex))
		return false;

	if (!ParseProtocol(match[1].str(), protocol))
		return false;

	host = match[2].str();
	if (host.empty())
		return false;

	if (match[3].matched)
	{
		if (!ParsePort(match[3].str(), port))
			return false;
	}
	else
	{
		port = GetDefaultPort(protocol);
	}

	document = match[4].matched ? match[4].str() : "";

	return true;
}
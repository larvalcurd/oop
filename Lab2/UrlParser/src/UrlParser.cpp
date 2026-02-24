#include "UrlParser.h"
#include <algorithm>
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
	try
	{
		const unsigned long value = std::stoul(str);
		if (value < 1 || value > 65535)
			return false;
		port = static_cast<int>(value);
		return true;
	}
	catch (...)
	{
		return false;
	}
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
		std::string(R"(^)")
			+ R"((https?|ftp))" // группа 1: протокол
			+ R"(://)"
			+ R"(([^/:]+))" // группа 2: хост
			+ R"((?::(\d+))?)" // группа 3: порт (опционально)
			+ R"((?:/(.*))?)" // группа 4: путь (опционально, может быть пустым)
			+ R"($)",
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
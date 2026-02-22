#include <algorithm>
#include <iostream>
#include <optional>
#include <string>
#include <cassert>

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

std::string HtmlDecode(std::string const& html)
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

void TestHtmlDecode()
{
	// Тест 1: Базовые сущности
	assert(HtmlDecode("&lt;") == "<");
	assert(HtmlDecode("&gt;") == ">");
	assert(HtmlDecode("&quot;") == "\"");
	assert(HtmlDecode("&apos;") == "'");
	assert(HtmlDecode("&amp;") == "&");
	std::cout << "Test 1: PASSED\n";

	// Тест 2: Пример из задания
	assert(HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s")
		== "Cat <says> \"Meow\". M&M's");
	std::cout << "Test 2: PASSED\n";

	// Тест 3: Строка без сущностей
	assert(HtmlDecode("Hello World") == "Hello World");
	assert(HtmlDecode("") == "");
	std::cout << "Test 3: PASSED\n";

	// Тест 4: Несколько сущностей подряд
	assert(HtmlDecode("&lt;&gt;&amp;") == "<>&");
	std::cout << "Test 4: PASSED\n";

	// Тест 5: Незавершённые/неизвестные сущности (должны остаться как есть)
	assert(HtmlDecode("&unknown;") == "&unknown;");
	assert(HtmlDecode("&") == "&");
	assert(HtmlDecode("&lt") == "&lt"); // Без точки с запятой
	assert(HtmlDecode("& lt;") == "& lt;"); // Пробел внутри
	std::cout << "Test 5: PASSED\n";

	// Тест 6: Амперсанд в разных позициях
	assert(HtmlDecode("a & b") == "a & b");
	assert(HtmlDecode("&amp; & &amp;") == "& & &");
	std::cout << "Test 6: PASSED\n";

	// Тест 7: Сущность в конце строки
	assert(HtmlDecode("test&lt;") == "test<");
	assert(HtmlDecode("test&") == "test&");
	std::cout << "Test 7: PASSED\n";

	// Тест 8: Смешанный текст
	assert(HtmlDecode("1 &lt; 2 &amp;&amp; 3 &gt; 2") == "1 < 2 && 3 > 2");
	std::cout << "Test 8: PASSED\n";

	// Тест 9: Только специальные символы
	assert(HtmlDecode("&quot;&apos;") == "\"'");
	std::cout << "Test 9: PASSED\n";

	// Тест 10: Регистр имеет значение
	assert(HtmlDecode("&LT;") == "&LT;"); // Должно остаться как есть
	assert(HtmlDecode("&AMP;") == "&AMP;");
	std::cout << "Test 10: PASSED\n";

	std::cout << "\n=== All tests done ===\n\n";
}


int main()
{
	TestHtmlDecode();

	//std::string line;
	//while (std::getline(std::cin, line))
	//{
	//	std::cout << HtmlDecode(line) << '\n';
	//}
	return 0;
}
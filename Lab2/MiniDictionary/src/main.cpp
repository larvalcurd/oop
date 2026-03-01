#include "Dictionary.h"
#include "StringUtils.h"
#include <iostream>
#include <set>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

constexpr std::string_view EXIT_COMMAND = "...";
constexpr std::string_view PROMPT = ">";

void setupConsole()
{
#ifdef _WIN32
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
#endif
}

void printPrompt()
{
	std::cout << PROMPT;
}

void printTranslations(const std::set<std::string>& translations)
{
	if (translations.empty())
	{
		std::cout << "(нет переводов)\n";
		return;
	}
	auto it = translations.begin();
	std::cout << *it;
	for (++it; it != translations.end(); ++it)
	{
		std::cout << ", " << *it;
	}
	std::cout << "\n";
}

std::string promptTranslation(const std::string& word)
{
	std::cout << "Неизвестное слово \"" << word
			  << "\". Введите перевод или пустую строку для отказа.\n";
	printPrompt();

	std::string translation;
	if (!std::getline(std::cin, translation))
	{
		return {};
	}
	return trim(translation);
}

void handleUnknownWord(DictionaryData& dict, const std::string& input, bool isRussian)
{
	const std::string translation = promptTranslation(input);

	if (translation.empty())
	{
		std::cout << "Слово \"" << input << "\" проигнорировано.\n";
		return;
	}

	AddStatus status = isRussian
		? addEntry(dict, translation, input)
		: addEntry(dict, input, translation);

	if (status == AddStatus::Added)
	{
		std::cout << "Слово \"" << input << "\" сохранено в словаре как \""
				  << translation << "\".\n";
	}
	else
	{
		std::cout << "Запись \"" << input
				  << " — " << translation
				  << "\" уже существует.\n";
	}
}

void processInput(DictionaryData& dict, const std::string& input)
{
	const bool isRussian = hasCyrillic(input);
	const std::string lowerInput = toLower(input);

	std::set<std::string> translations = isRussian
		? translateRusToEng(dict, lowerInput)
		: translateEngToRus(dict, lowerInput);

	if (!translations.empty())
		printTranslations(translations);
	else
		handleUnknownWord(dict, input, isRussian);
}

void runDictionary(DictionaryData& dict)
{
	std::cout << "Мини-словарь. Введите слово для перевода или '...' для выхода.\n\n";

	std::string input;
	while (printPrompt(), std::getline(std::cin, input))
	{
		input = trim(input);

		if (input == EXIT_COMMAND)
			break;

		if (!input.empty())
			processInput(dict, input);
	}
}

void promptSave(const DictionaryData& dict, const std::string& filename)
{
	if (!dict.modified)
	{
		std::cout << "До свидания.\n";
		return;
	}

	std::cout << "В словарь были внесены изменения. "
				 "Введите Y или y для сохранения перед выходом.\n";

	printPrompt();
	std::string answer;

	if (std::getline(std::cin, answer) && toLower(trim(answer)) == "y")
	{
		DictError err = saveDictionary(dict, filename);

		if (err == DictError::Ok)
			std::cout << "Изменения сохранены. До свидания.\n";
		else
			std::cout << "Ошибка сохранения файла. До свидания.\n";
	}
	else
	{
		std::cout << "Изменения не сохранены. До свидания.\n";
	}
}

int main(int argc, char* argv[])
{
	setupConsole();

	if (argc < 2)
	{
		std::cerr << "Использование: " << argv[0]
				  << " <файл_словаря>\n";
		return 1;
	}

	const std::string filename = argv[1];
	DictionaryData dict;

	DictResult loadRes = loadDictionary(dict, filename);

	if (loadRes.fileMissing)
		std::cout << "Файл словаря отсутствует. Создаём новый словарь.\n";

	if (loadRes.malformedLines > 0)
		std::cout << "Предупреждение: пропущено битых строк: "
				  << loadRes.malformedLines << "\n";

	if (loadRes.error != DictError::Ok)
	{
		std::cerr << "Ошибка чтения файла словаря.\n";
		return 1;
	}

	runDictionary(dict);
	promptSave(dict, filename);

	return 0;
}
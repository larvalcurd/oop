#include "Dictionary.h"
#include "StringUtils.h"
#include <fstream>
#include <iostream>

void loadDictionary(DictionaryData& dict, const std::string& filename)
{
	std::ifstream fin(filename);
	if (!fin.is_open())
	{
		std::cout << "Файл словаря не найден. Создан пустой словарь.\n";
		return;
	}

	std::string line;
	while (std::getline(fin, line))
	{
		const auto pos = line.find('|');
		if (pos == std::string::npos)
			continue;

		std::string eng = trim(line.substr(0, pos));
		std::string rus = trim(line.substr(pos + 1));

		if (eng.empty() || rus.empty())
			continue;

		dict.engToRus[toLower(eng)].insert(rus);
		dict.rusToEng[toLower(rus)].insert(eng);
		dict.entries.emplace_back(std::move(eng), std::move(rus));
	}
}

void saveDictionary(const DictionaryData& dict, const std::string& filename)
{
	std::ofstream fout(filename);
	if (!fout.is_open())
	{
		std::cerr << "Ошибка сохранения файла!\n";
		return;
	}

	for (const auto& [eng, rus] : dict.entries)
	{
		fout << eng << "|" << rus << "\n";
	}
}

void addEntry(DictionaryData& dict, const std::string& eng, const std::string& rus)
{
	dict.engToRus[toLower(eng)].insert(rus);
	dict.rusToEng[toLower(rus)].insert(eng);
	dict.entries.emplace_back(eng, rus);
	dict.modified = true;
}

std::set<std::string> translateEngToRus(const DictionaryData& dict, const std::string& word)
{
	const auto it = dict.engToRus.find(toLower(word));
	if (it != dict.engToRus.end())
		return it->second;
	return {};
}

std::set<std::string> translateRusToEng(const DictionaryData& dict, const std::string& word)
{
	const auto it = dict.rusToEng.find(toLower(word));
	if (it != dict.rusToEng.end())
		return it->second;
	return {};
}
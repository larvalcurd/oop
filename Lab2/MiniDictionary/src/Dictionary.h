#pragma once
#include <map>
#include <set>
#include <string>
#include <vector>

struct DictionaryData
{
	std::map<std::string, std::set<std::string>> engToRus;
	std::map<std::string, std::set<std::string>> rusToEng;
	std::vector<std::pair<std::string, std::string>> entries;
	bool modified = false;
};

void loadDictionary(DictionaryData& dict, const std::string& filename);
void saveDictionary(const DictionaryData& dict, const std::string& filename);

void addEntry(DictionaryData& dict, const std::string& eng, const std::string& rus);

std::set<std::string> translateEngToRus(const DictionaryData& dict, const std::string& word);
std::set<std::string> translateRusToEng(const DictionaryData& dict, const std::string& word);
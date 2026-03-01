#pragma once
#include <map>
#include <set>
#include <string>
#include <vector>

enum class DictError
{
	Ok,
	OpenFailed,
	ReadFailed,
	WriteFailed
};

enum class AddStatus
{
	Added,
	AlreadyExists
};

struct DictResult
{
	DictError error;
	bool fileMissing = false;
	size_t malformedLines = 0;
};

struct DictionaryData
{
	std::map<std::string, std::set<std::string>> engToRus;
	std::map<std::string, std::set<std::string>> rusToEng;
	std::vector<std::pair<std::string, std::string>> entries;
	bool modified = false;
};

DictResult loadDictionary(DictionaryData& dict, const std::string& filename);
DictError saveDictionary(const DictionaryData& dict, const std::string& filename);

AddStatus addEntry(DictionaryData& dict, const std::string& eng, const std::string& rus);

std::set<std::string> translateEngToRus(const DictionaryData& dict, const std::string& normalizedWord);
std::set<std::string> translateRusToEng(const DictionaryData& dict, const std::string& normalizedWord);
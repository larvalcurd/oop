#include "Dictionary.h"
#include "StringUtils.h"
#include <fstream>

namespace
{
AddStatus addEntryInternal(DictionaryData& dict, const std::string& eng, const std::string& rus)
{
	std::string engNorm = toLower(eng);
	std::string rusNorm = toLower(rus);

	auto& rusSet = dict.engToRus[engNorm];

	for (const auto& existingRus : rusSet)
	{
		if (toLower(existingRus) == rusNorm)
		{
			return AddStatus::AlreadyExists;
		}
	}

	rusSet.insert(rus);
	dict.rusToEng[rusNorm].insert(eng);

	dict.entries.emplace_back(eng, rus);

	return AddStatus::Added;
}
} // namespace

DictResult loadDictionary(DictionaryData& dict, const std::string& filename)
{
	std::ifstream fin(filename);
	if (!fin.is_open())
	{
		return { DictError::Ok, true, 0 };
	}

	DictResult result{};
	result.error = DictError::Ok;

	std::string line;

	while (true)
	{
		if (!std::getline(fin, line))
		{
			if (fin.eof())
			{
				break;
			}
			return { DictError::ReadFailed, false, result.malformedLines };
		}

		const auto pos = line.find('|');
		if (pos == std::string::npos)
		{
			result.malformedLines++;
			continue;
		}

		std::string eng = trim(line.substr(0, pos));
		std::string rus = trim(line.substr(pos + 1));

		if (eng.empty() || rus.empty())
		{
			result.malformedLines++;
			continue;
		}

		addEntryInternal(dict, eng, rus);
	}

	return result;
}

DictError saveDictionary(const DictionaryData& dict, const std::string& filename)
{
	std::ofstream fout(filename);
	if (!fout.is_open())
	{
		return DictError::OpenFailed;
	}

	for (const auto& [eng, rus] : dict.entries)
	{
		fout << eng << "|" << rus << "\n";

		if (!fout)
		{
			return DictError::WriteFailed;
		}
	}

	return DictError::Ok;
}

AddStatus addEntry(DictionaryData& dict, const std::string& eng, const std::string& rus)
{
	AddStatus status = addEntryInternal(dict, eng, rus);
	if (status == AddStatus::Added)
	{
		dict.modified = true;
	}
	return status;
}

std::set<std::string> translateEngToRus(const DictionaryData& dict, const std::string& normalizedWord)
{
	const auto it = dict.engToRus.find(normalizedWord);
	if (it != dict.engToRus.end())
		return it->second;
	return {};
}

std::set<std::string> translateRusToEng(const DictionaryData& dict, const std::string& normalizedWord)
{
	const auto it = dict.rusToEng.find(normalizedWord);
	if (it != dict.rusToEng.end())
		return it->second;
	return {};
}
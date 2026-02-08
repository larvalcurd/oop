#include "replace.h"
#include "stream_processor.h"

#include <string>
#include <iostream>
#include <fstream>

void printHelp()
{
	std::cout << "Usage:\n";
	std::cout << "replace.exe <input file> <output file> <search string> <replace string>\n";
	std::cout << "Or run without arguments to use stdin mode.\n";
}

std::string replaceInLine(const std::string& line,
	const std::string& search,
	const std::string& replace)
{
	if (search.empty())
	{
		return line;
	}

	std::string result = line;
	size_t pos = 0;
	while ((pos = result.find(search, pos)) != std::string::npos)
	{
		result.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return result;
}
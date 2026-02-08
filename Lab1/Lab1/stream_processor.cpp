#include "stream_processor.h"
#include "replace.h"

#include <string>
#include <iostream>
#include <fstream>

int processCLI(const std::string& inputFile,
	const std::string& outputFile,
	const std::string& search,
	const std::string& replace)
{
	std::ifstream in(inputFile);
	if (!in.is_open())
	{
		std::cout << "ERROR";
		return 1;
	}

	std::ofstream out(outputFile);
	if (!out.is_open())
	{
		std::cout << "ERROR";
		return 1;
	}

	processStream(in, out, search, replace);
	return 0;
}

void processStream(std::istream& in,
	std::ostream& out,
	const std::string& search,
	const std::string& replace)
{
	std::string line;

	while (std::getline(in, line))
	{
		std::string replaced = replaceInLine(line, search, replace);
		out << replaced << '\n';
	}
}

int processStdin()
{
	std::string search, replace;
	if (!std::getline(std::cin, search) || !std::getline(std::cin, replace))
	{
		std::cout << "ERROR" << std::endl;
		return 0;
	}
	processStream(std::cin, std::cout, search, replace);
	return 0;
}
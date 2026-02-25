#pragma once
#include <string>

enum class Mode
{
	Help,
	Stdin,
	FileReplace,
	Error,
};

struct Args
{
	Mode mode = Mode::Error;
	std::string inputFileName;
	std::string outputFileName;
	std::string searchString;
	std::string replacementString;
};

Args ParseArgs(int argc, char* argv[]);

void PrintHelp();
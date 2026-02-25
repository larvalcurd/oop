#include "ArgsParser.h"
#include "StreamProcessor.h"
#include <iostream>

int ProcessStdin()
{
	std::string search, replace;

	if (!std::getline(std::cin, search) || !std::getline(std::cin, replace))
	{
		std::cout << "ERROR" << std::endl;
		return 0;
	}

	CopyStreamWithReplacement(std::cin, std::cout, search, replace);
	return 0;
}

int main(int argc, char* argv[])
{
	Args args = ParseArgs(argc, argv);

	switch (args.mode)
	{
	case Mode::Help:
		PrintHelp();
		return 0;

	case Mode::Stdin:
		return ProcessStdin();

	case Mode::FileReplace:
		if (!CopyFileWithReplacement(args.inputFileName, args.outputFileName,
				args.searchString, args.replacementString))
		{
			std::cout << "ERROR" << std::endl;
			return 1;
		}
		return 0;

	case Mode::Error:
	default:
		std::cout << "ERROR" << std::endl;
		return 1;
	}
}
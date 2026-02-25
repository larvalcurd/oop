#include "ArgsParser.h"
#include <iostream>

Args ParseArgs(int argc, char* argv[])
{
	Args args;

	if (argc == 2 && std::string(argv[1]) == "-h")
	{
		args.mode = Mode::Help;
	}
	else if (argc == 1)
	{
		args.mode = Mode::Stdin;
	}
	else if (argc == 5)
	{
		args.mode = Mode::FileReplace;
		args.inputFileName = argv[1];
		args.outputFileName = argv[2];
		args.searchString = argv[3];
		args.replacementString = argv[4];
	}
	else
	{
		args.mode = Mode::Error;
	}

	return args;
}

void PrintHelp()
{
	std::cout << "Usage:\n"
			  << "replace.exe <input file> <output file> <search string> <replace string>\n"
			  << "Or run without arguments to use stdin mode.\n";
}
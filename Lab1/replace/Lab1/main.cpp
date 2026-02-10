#include "replace.h"
#include "stream_processor.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	if (argc == 2 && std::string(argv[1]) == "-h")
	{
		printHelp();
		return 0;
	}

	if (argc == 1)
	{
		return processStdin();
	}

	if (argc == 5)
	{
		std::string inputFile = argv[1];
		std::string outputFile = argv[2];
		std::string search = argv[3];
		std::string replace = argv[4];

		return processCLI(inputFile, outputFile, search, replace);
	}
	else
	{
		std::cout << "Invalid arguments. Use --help for usage information." << std::endl;
		return 1;
	}
}
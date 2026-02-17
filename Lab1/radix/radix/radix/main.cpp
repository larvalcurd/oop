#include "radix.h"

#include <iostream>
#include <string>

namespace
{
const int REQUIRED_ARGC = 4;
const int SUCCESS = 0;
const int FAILURE = 1;

void PrintUsage()
{
	std::cerr << "Usage: radix.exe <source radix> <destination radix> <value>\n";
}

bool TryParseRadix(const char* str, int& outRadix)
{
	try
	{
		outRadix = std::stoi(str);
		return true;
	}
	catch (...)
	{
		return false;
	}
}
} // namespace

int main(int argc, char* argv[])
{
	if (argc != REQUIRED_ARGC)
	{
		PrintUsage();
		return FAILURE;
	}

	int sourceRadix = 0;
	int destinationRadix = 0;

	if (!TryParseRadix(argv[1], sourceRadix) || !TryParseRadix(argv[2], destinationRadix))
	{
		std::cerr << "Error: cannot parse radix. Expected an integer.\n";
		return FAILURE;
	}

	if (!IsValidRadix(sourceRadix) || !IsValidRadix(destinationRadix))
	{
		std::cerr << "Error: radix must be between "
				  << MIN_RADIX << " and " << MAX_RADIX << ".\n";
		return FAILURE;
	}

	const std::string valueStr = argv[3];
	bool wasError = false;

	const int value = StringToInt(valueStr, sourceRadix, wasError);
	if (wasError)
	{
		std::cerr << "Error: invalid input value or overflow in source radix.\n";
		return FAILURE;
	}

	const std::string result = IntToString(value, destinationRadix, wasError);
	if (wasError)
	{
		std::cerr << "Error: cannot convert to destination radix.\n";
		return FAILURE;
	}

	std::cout << result << "\n";

	return SUCCESS;
}
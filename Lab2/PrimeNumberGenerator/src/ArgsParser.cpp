#include "ArgsParser.h"

#include <iostream>

namespace
{

void PrintUsage(const std::string& programName)
{
	std::cerr << "Usage: " << programName << " <upper_bound>\n"
			  << "  upper_bound: integer from 1 to " << MAX_UPPER_BOUND << '\n';
}

std::optional<int> ParseUpperBound(const std::string& input)
{
	try
	{
		size_t processedChars = 0;
		int value = std::stoi(input, &processedChars);

		bool hasTrailingChars = (processedChars != input.length());
		bool isOutOfRange = (value <= 0 || value > MAX_UPPER_BOUND);

		if (hasTrailingChars || isOutOfRange)
		{
			return std::nullopt;
		}

		return value;
	}
	catch (const std::exception&)
	{
		return std::nullopt;
	}
}

} // namespace

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		PrintUsage(argv[0]);
		return std::nullopt;
	}

	std::optional<int> upperBound = ParseUpperBound(argv[1]);

	if (!upperBound.has_value())
	{
		std::cerr << "Error: upper_bound must be an integer from 1 to "
				  << MAX_UPPER_BOUND << '\n';
		return std::nullopt;
	}

	return Args{ upperBound.value() };
}
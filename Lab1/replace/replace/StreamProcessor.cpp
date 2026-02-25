#include "StreamProcessor.h"
#include "StringUtils.h"
#include <fstream>

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;
	bool firstLine = true;

	while (std::getline(input, line))
	{
		if (!firstLine)
		{
			output << "\n";
		}
		output << ReplaceString(line, searchString, replacementString);
		firstLine = false;
	}
}

bool CopyFileWithReplacement(const std::string& inputFileName,
	const std::string& outputFileName,
	const std::string& searchString, const std::string& replacementString)
{
	std::ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
	{
		return false;
	}

	std::ofstream outputFile(outputFileName);
	if (!outputFile.is_open())
	{
		return false;
	}

	CopyStreamWithReplacement(inputFile, outputFile, searchString, replacementString);

	outputFile.flush();

	return !outputFile.fail();
}
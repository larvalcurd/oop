#include <iostream>
#include <fstream>
#include <string>

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	if (searchString.empty())
	{
		return subject;
	}

	size_t pos = 0;
	std::string result;
	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);
		result.append(subject, pos, foundPos - pos);

		if (foundPos == std::string::npos)
		{
			break;
		}

		result.append(replacementString);
		pos = foundPos + searchString.length();
	}
	return result;
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;
	bool firstLine = true;

	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << "\n";
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

	if (outputFile.fail())
	{
		return false;
	}

	return true;
}

void PrintHelp()
{
	std::cout << "Usage:\n";
	std::cout << "replace.exe <input file> <output file> <search string> <replace string>\n";
	std::cout << "Or run without arguments to use stdin mode.\n";
}

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
	if (argc == 2 && std::string(argv[1]) == "-h")
	{
		PrintHelp();
		return 0;
	}

	if (argc == 1)
	{
		return ProcessStdin();
	}

	if (argc == 5)
	{
		std::string inputFileName = argv[1];
		std::string outputFileName = argv[2];
		std::string search = argv[3];
		std::string replace = argv[4];

		if (!CopyFileWithReplacement(inputFileName, outputFileName, search, replace))
		{
			std::cout << "ERROR" << std::endl;
			return 1;
		}
		return 0;
	}

	std::cout << "ERROR" << std::endl;
	return 1;
}
#include "Life.h"
#include <fstream>

namespace
{
void printUsage(const char* programName)
{
	std::cerr << "Usage: " << programName << " <input> [output]\n";
}

std::ifstream openInput(const char* filename)
{
	std::ifstream file(filename);
	if (!file)
		std::cerr << "Cannot open: " << filename << "\n";
	return file;
}

std::ofstream openOutput(const char* filename)
{
	std::ofstream file(filename);
	if (!file)
		std::cerr << "Cannot write: " << filename << "\n";
	return file;
}

void writeResult(const Grid& result, int argc, char* argv[])
{
	if (argc >= 3)
	{
		if (auto out = openOutput(argv[2]))
			Life::writeField(result, out);
	}
	else
	{
		Life::writeField(result, std::cout);
	}
}
} // namespace

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printUsage(argv[0]);
		return 1;
	}

	auto inputFile = openInput(argv[1]);
	if (!inputFile)
		return 1;

	Grid result = Life::calculateNextGeneration(Life::readField(inputFile));

	writeResult(result, argc, argv);
	return 0;
}
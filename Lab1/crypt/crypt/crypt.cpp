#include "Cipher.h"
#include <iostream>
#include <string>

struct Args
{
	std::string mode;
	std::string inputPath;
	std::string outputPath;
	uint8_t key;
};

static bool ParseKey(const std::string& str, int& outKey)
{
	try
	{
		size_t pos = 0;
		outKey = std::stoi(str, &pos);
		return pos == str.size() && outKey >= 0 && outKey <= 255;
	}
	catch (...)
	{
		return false;
	}
}

static bool ParseArgs(int argc, char* argv[], Args& args)
{
	if (argc != 5)
	{
		std::cerr << "Usage: crypt.exe <crypt|decrypt> <input file> <output file> <key>\n";
		return false;
	}

	args.mode = argv[1];
	if (args.mode != "crypt" && args.mode != "decrypt")
	{
		std::cerr << "Error: first argument must be 'crypt' or 'decrypt'\n";
		return false;
	}

	args.inputPath = argv[2];
	args.outputPath = argv[3];

	if (args.inputPath == args.outputPath)
	{
		std::cerr << "Error: input and output files must differ\n";
		return false;
	}

	int key;
	if (!ParseKey(argv[4], key))
	{
		std::cerr << "Error: key must be a number between 0 and 255\n";
		return false;
	}
	args.key = static_cast<uint8_t>(key);

	return true;
}

static bool OpenFiles(const Args& args,
	std::ifstream& input,
	std::ofstream& output)
{
	input.open(args.inputPath, std::ios::binary);
	if (!input)
	{
		std::cerr << "Error: cannot open input file '" << args.inputPath << "'\n";
		return false;
	}

	output.open(args.outputPath, std::ios::binary);
	if (!output)
	{
		std::cerr << "Error: cannot open output file '" << args.outputPath << "'\n";
		return false;
	}

	return true;
}

static bool ProcessCipher(const Args& args)
{
	std::ifstream input;
	std::ofstream output;
	if (!OpenFiles(args, input, output))
	{
		return false;
	}

	LookupTable encTable;
	LookupTable decTable;
	BuildLookupTables(encTable, decTable, args.key);

	const LookupTable& table = (args.mode == "crypt") ? encTable : decTable;

	if (!TransformFile(input, output, table))
	{
		std::cerr << "Error: file processing failed\n";
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	Args args;
	if (!ParseArgs(argc, argv, args))
	{
		return 1;
	}

	if (!ProcessCipher(args))
	{
		return 1;
	}

	return 0;
}
#include "Cipher.h"
#include <iostream>
#include <string>

namespace
{

struct Args
{
	std::string mode;
	std::string inputPath;
	std::string outputPath;
	uint8_t key;
};

bool ParseKey(const std::string& str, uint8_t& outKey)
{
	try
	{
		std::size_t pos = 0;
		int value = std::stoi(str, &pos);

		if (pos != str.size() || value < 0 || value > 255)
		{
			return false;
		}

		outKey = static_cast<uint8_t>(value);
		return true;
	}
	catch (...)
	{
		return false;
	}
}

bool ParseArgs(int argc, char* argv[], Args& args)
{
	if (argc != 5)
	{
		std::cerr << "Usage: crypt.exe <crypt|decrypt> <input file> <output file> <key>\n";
		return false;
	}

	args.mode = argv[1];

	if (args.mode != MODE_CRYPT && args.mode != MODE_DECRYPT)
	{
		std::cerr << "Error: first argument must be '"
				  << MODE_CRYPT << "' or '" << MODE_DECRYPT << "'\n";
		return false;
	}

	args.inputPath = argv[2];
	args.outputPath = argv[3];

	if (args.inputPath == args.outputPath)
	{
		std::cerr << "Error: input and output files must differ\n";
		return false;
	}

	if (!ParseKey(argv[4], args.key))
	{
		std::cerr << "Error: key must be a number between 0 and 255\n";
		return false;
	}

	return true;
}

bool OpenFiles(const Args& args,
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

bool EncryptOrDecrypt(const Args& args)
{
	std::ifstream input;
	std::ofstream output;

	if (!OpenFiles(args, input, output))
	{
		return false;
	}

	bool encrypt = (args.mode == MODE_CRYPT);
	LookupTable table = BuildLookupTable(args.key, encrypt);

	if (!ApplyTableToStream(input, output, table))
	{
		std::cerr << "Error: file processing failed\n";
		return false;
	}

	return true;
}

} // namespace

int main(int argc, char* argv[])
{
	Args args;

	if (!ParseArgs(argc, argv, args))
	{
		return 1;
	}

	if (!EncryptOrDecrypt(args))
	{
		return 1;
	}

	return 0;
}
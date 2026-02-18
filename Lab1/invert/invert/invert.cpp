#include "matrix.h"
#include <fstream>
#include <string>

static bool OpenInputFile(const std::string& path, std::ifstream& file)
{
	file.open(path);
	if (!file)
	{
		std::cerr << "Failed to open file: " << path << "\n";
		return false;
	}
	return true;
}

static bool ProcessMatrix(std::istream& input)
{
	Matrix3x3 matrix;
	ReadResult rc = ReadMatrix(input, matrix);

	if (rc == ReadResult::InvalidFormat)
	{
		std::cerr << "Invalid matrix format\n";
		return false;
	}
	if (rc == ReadResult::InvalidValue)
	{
		std::cerr << "Invalid matrix\n";
		return false;
	}

	Matrix3x3 inverse;
	if (!Invert(matrix, inverse))
	{
		std::cout << "Non-invertible\n";
		return false;
	}

	PrintMatrix(std::cout, inverse);
	return true;
}

int main(int argc, char* argv[])
{
	if (argc > 2)
	{
		std::cerr << "Too many arguments. Use -h for help.\n";
		return 1;
	}

	if (argc == 2 && std::string(argv[1]) == "-h")
	{
		PrintHelp();
		return 0;
	}

	std::ifstream file;
	std::istream* input = &std::cin;

	if (argc == 2)
	{
		if (!OpenInputFile(argv[1], file))
		{
			return 1;
		}
		input = &file;
	}

	if (!ProcessMatrix(*input))
	{
		return 1;
	}

	return 0;
}
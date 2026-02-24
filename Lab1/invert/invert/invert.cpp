#include "matrix.h"
#include <fstream>
#include <string>

namespace
{

bool ProcessStream(std::istream& input)
{
	auto [matrix, error] = ReadMatrix(input);

	if (error != ReadError::None)
	{
		std::cerr << GetReadErrorMessage(error) << '\n';
		return false;
	}

	auto inverse = Invert(matrix);

	if (!inverse.has_value())
	{
		std::cerr << "Non-invertible\n";
		return false;
	}

	PrintMatrix(std::cout, inverse.value());
	return true;
}

bool ProcessFile(const std::string& path)
{
	std::ifstream file(path);

	if (!file)
	{
		std::cerr << "Failed to open file: " << path << '\n';
		return false;
	}

	return ProcessStream(file);
}

int Run(int argc, char* argv[])
{
	if (argc > 2)
	{
		std::cerr << "Too many arguments. Use -h for help.\n";
		return 1;
	}

	if (argc == 2)
	{
		std::string arg = argv[1];

		if (arg == "-h")
		{
			PrintHelp();
			return 0;
		}

		return ProcessFile(arg) ? 0 : 1;
	}

	return ProcessStream(std::cin) ? 0 : 1;
}

} // namespace

int main(int argc, char* argv[])
{
	return Run(argc, argv);
}
#include "matrix.h"
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
	if (argc > 2) {
		std::cout << "Too many arguments. Use -h for help.\n";
		return 1;
	}

	if (argc == 2 && std::string(argv[1]) == "-h") {
		PrintHelp();
		return 0;
	}

	std::ifstream file;
	std::istream* input = &std::cin;

	if (argc == 2) {
		file.open(argv[1]);
		if (!file.is_open()) {
			std::cout << "Failed to open file: " << argv[1] << "\n";
			return 1;
		}
		input = &file;
	}

	Matrix3x3 matrix;
	int rc = ReadMatrix(*input, matrix);	

	if (rc == 1) {
		std::cout << "Invalid matrix format" << "\n";
		return 1;
	}
	else if (rc == 2) {
		std::cout << "Invalid matrix" << "\n";
		return 1;
	}

	Matrix3x3 inverse;
	if (!Invert(matrix, inverse)) {
		std::cout << "Non-invertible" << '\n';
		return 1;
	}

	PrintMatrix(std::cout, inverse);
	return 0;
}
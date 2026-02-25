#include "life.h"
#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cerr << "Usage: live.exe <input file> [<output file>]\n";
		return 1;
	}

	std::ifstream fin(argv[1]);
	if (!fin.is_open())
	{
		std::cerr << "Error: cannot open " << argv[1] << "\n";
		return 1;
	}
	Grid grid = readField(fin);
	fin.close();

	Grid next = calculateNextGeneration(grid);

	if (argc >= 3)
	{
		std::ofstream fout(argv[2]);
		if (!fout.is_open())
		{
			std::cerr << "Error: cannot open " << argv[2] << " for writing\n";
			return 1;
		}
		writeField(next, fout);
	}
	else
	{
		writeField(next, std::cout);
	}

	return 0;
}
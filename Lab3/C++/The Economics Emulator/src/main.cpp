#include "Simulation.h"
#include <cstdlib>
#include <iostream>

namespace
{
	constexpr Money INITIAL_CASH = 10000;

	int ParseIterations(int argc, char* argv[])
	{
		if (argc >= 2)
		{
			return std::stoi(argv[1]);
		}

		std::cout << "Enter number of iterations: ";
		int iterations = 0;
		std::cin >> iterations;
		return iterations;
	}
}

int main(int argc, char* argv[])
{
	const int numIterations = ParseIterations(argc, argv);

	if (numIterations <= 0)
	{
		std::cerr << "Invalid number of iterations\n";
		return 1;
	}

	Simulation simulation(INITIAL_CASH);
	simulation.Run(numIterations);
	simulation.PrintFinalState();

	if (!simulation.VerifyInvariants())
	{
		std::cerr << "Simulation ended with errors!\n";
		return 1;
	}

	return 0;
}
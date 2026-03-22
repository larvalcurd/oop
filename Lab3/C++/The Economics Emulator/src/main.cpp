#include "Simulation.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[])
{
	int numIterations = 0;

	if (argc >= 2)
	{
		numIterations = std::atoi(argv[1]);
	}

	if (numIterations <= 0)
	{
		std::cout << "Enter number of iterations: ";
		std::cin >> numIterations;
	}

	if (numIterations <= 0)
	{
		std::cerr << "Invalid number of iterations\n";
		return 1;
	}

	constexpr Money INITIAL_CASH = 10000;

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
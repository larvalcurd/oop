#include "ArgsParser.h"
#include "PrimeGenerator.h"

#include <cstdlib>
#include <iostream>
#include <set>

void PrintPrimes(const std::set<int>& primes)
{
	for (int prime : primes)
	{
		std::cout << prime << '\n';
	}
}

int main(int argc, char* argv[])
{
	std::optional<Args> args = ParseArgs(argc, argv);

	if (!args.has_value())
	{
		return EXIT_FAILURE;
	}

	std::set<int> primes = GeneratePrimeNumbersSet(args->upperBound);
	PrintPrimes(primes);

	return EXIT_SUCCESS;
}
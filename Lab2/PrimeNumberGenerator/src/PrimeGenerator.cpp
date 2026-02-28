#include "PrimeGenerator.h"

#include <vector>

namespace
{

int NumberToIndex(int number)
{
	return (number - 3) / 2;
}

int IndexToNumber(int index)
{
	return 2 * index + 3;
}

int SieveSize(int upperBound)
{
	return (upperBound - 1) / 2;
}

std::vector<bool> BuildPrimeSieve(int upperBound)
{
	int size = SieveSize(upperBound);
	std::vector<bool> isPrime(size, true);

	for (int number = 3; number * number <= upperBound; number += 2)
	{
		int index = NumberToIndex(number);

		if (!isPrime[index])
		{
			continue;
		}

		for (int multiple = number * number; multiple <= upperBound; multiple += 2 * number)
		{
			isPrime[NumberToIndex(multiple)] = false;
		}
	}

	return isPrime;
}

std::set<int> CollectPrimesFromSieve(const std::vector<bool>& sieve, int upperBound)
{
	std::set<int> primes;

	if (upperBound >= 2)
	{
		primes.insert(2);
	}

	int size = SieveSize(upperBound);
	for (int index = 0; index < size; ++index)
	{
		if (sieve[index])
		{
			primes.insert(primes.end(), IndexToNumber(index));
		}
	}

	return primes;
}

} // namespace

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound < MIN_PRIME)
	{
		return {};
	}

	std::vector<bool> sieve = BuildPrimeSieve(upperBound);

	return CollectPrimesFromSieve(sieve, upperBound);
}
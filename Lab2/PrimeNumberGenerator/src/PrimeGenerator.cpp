#include "PrimeGenerator.h"

#include <cmath>
#include <vector>

namespace
{

std::vector<bool> BuildPrimeSieve(int upperBound)
{
	std::vector<bool> isPrime(upperBound + 1, true);

	isPrime[0] = false;
	isPrime[1] = false;

	int sieveLimit = static_cast<int>(std::sqrt(static_cast<double>(upperBound)));

	for (int number = MIN_PRIME; number <= sieveLimit; ++number)
	{
		if (!isPrime[number])
		{
			continue;
		}

		long long firstMultiple = static_cast<long long>(number) * number;
		for (long long multiple = firstMultiple; multiple <= upperBound; multiple += number)
		{
			isPrime[multiple] = false;
		}
	}

	return isPrime;
}

std::set<int> CollectPrimesFromSieve(const std::vector<bool>& sieve)
{
	std::set<int> primes;

	for (size_t number = MIN_PRIME; number < sieve.size(); ++number)
	{
		if (sieve[number])
		{
			primes.insert(primes.end(), static_cast<int>(number));
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

	return CollectPrimesFromSieve(sieve);
}
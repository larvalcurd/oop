#include "../src/PrimeGenerator.h"
#include <gtest/gtest.h>

TEST(GeneratePrimeNumbersSet, ReturnsEmptySetForNegativeUpperBound)
{
	std::set<int> primes = GeneratePrimeNumbersSet(-10);

	EXPECT_TRUE(primes.empty());
}

TEST(GeneratePrimeNumbersSet, ReturnsEmptySetForZero)
{
	std::set<int> primes = GeneratePrimeNumbersSet(0);

	EXPECT_TRUE(primes.empty());
}

TEST(GeneratePrimeNumbersSet, ReturnsEmptySetForOne)
{
	std::set<int> primes = GeneratePrimeNumbersSet(1);

	EXPECT_TRUE(primes.empty());
}

TEST(GeneratePrimeNumbersSet, ReturnsSinglePrimeForTwo)
{
	std::set<int> primes = GeneratePrimeNumbersSet(2);

	std::set<int> expected = { 2 };
	EXPECT_EQ(primes, expected);
}

TEST(GeneratePrimeNumbersSet, ReturnsCorrectPrimesUpToTen)
{
	std::set<int> primes = GeneratePrimeNumbersSet(10);

	std::set<int> expected = { 2, 3, 5, 7 };
	EXPECT_EQ(primes, expected);
}

TEST(GeneratePrimeNumbersSet, ReturnsCorrectPrimesUpToThirty)
{
	std::set<int> primes = GeneratePrimeNumbersSet(30);

	std::set<int> expected = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
	EXPECT_EQ(primes, expected);
}

TEST(GeneratePrimeNumbersSet, ReturnsCorrectPrimesUpToHundred)
{
	std::set<int> primes = GeneratePrimeNumbersSet(100);

	std::set<int> expected = {
		2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
		31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
		73, 79, 83, 89, 97
	};
	EXPECT_EQ(primes, expected);
}

TEST(GeneratePrimeNumbersSet, IncludesUpperBoundIfPrime)
{
	std::set<int> primes = GeneratePrimeNumbersSet(13);

	EXPECT_TRUE(primes.count(13) == 1);
}

TEST(GeneratePrimeNumbersSet, ExcludesUpperBoundIfNotPrime)
{
	std::set<int> primes = GeneratePrimeNumbersSet(14);

	EXPECT_TRUE(primes.count(14) == 0);
	EXPECT_TRUE(primes.count(13) == 1);
}

TEST(GeneratePrimeNumbersSet, ReturnsCorrectCountUpToThousand)
{
	std::set<int> primes = GeneratePrimeNumbersSet(1000);

	EXPECT_EQ(primes.size(), 168u);
}

TEST(GeneratePrimeNumbersSet, ReturnsCorrectCountUpToTenThousand)
{
	std::set<int> primes = GeneratePrimeNumbersSet(10000);

	EXPECT_EQ(primes.size(), 1229u);
}

TEST(GeneratePrimeNumbersSet, ReturnsCorrectCountUpToHundredThousand)
{
	std::set<int> primes = GeneratePrimeNumbersSet(100000);

	EXPECT_EQ(primes.size(), 9592u);
}

TEST(GeneratePrimeNumbersSet, ReturnsCorrectCountUpToMillion)
{
	std::set<int> primes = GeneratePrimeNumbersSet(1000000);

	EXPECT_EQ(primes.size(), 78498u);
}

TEST(GeneratePrimeNumbersSet, AllElementsArePrime)
{
	std::set<int> primes = GeneratePrimeNumbersSet(100);

	auto isPrime = [](int n) {
		if (n < 2)
			return false;
		if (n == 2)
			return true;
		if (n % 2 == 0)
			return false;
		for (int i = 3; i * i <= n; i += 2)
		{
			if (n % i == 0)
				return false;
		}
		return true;
	};

	for (int prime : primes)
	{
		EXPECT_TRUE(isPrime(prime)) << prime << " is not prime";
	}
}

TEST(GeneratePrimeNumbersSet, ContainsAllPrimesInRange)
{
	int upperBound = 100;
	std::set<int> primes = GeneratePrimeNumbersSet(upperBound);

	auto isPrime = [](int n) {
		if (n < 2)
			return false;
		if (n == 2)
			return true;
		if (n % 2 == 0)
			return false;
		for (int i = 3; i * i <= n; i += 2)
		{
			if (n % i == 0)
				return false;
		}
		return true;
	};

	for (int n = 2; n <= upperBound; ++n)
	{
		if (isPrime(n))
		{
			EXPECT_TRUE(primes.count(n) == 1) << "Missing prime: " << n;
		}
	}
}

TEST(GeneratePrimeNumbersSet, ReturnsCorrectCountUpToHundredMillion)
{
	std::set<int> primes = GeneratePrimeNumbersSet(100000000);

	EXPECT_EQ(primes.size(), 5761455u);
}
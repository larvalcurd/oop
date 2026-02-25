#include <gtest/gtest.h>
#include <sstream>
#include "numbers.h"

// ============================================================
// ReadNumbers tests
// ============================================================

TEST(ReadNumbers, EmptyInput)
{
    std::istringstream input("");
    std::vector<double> numbers;
    EXPECT_TRUE(ReadNumbers(input, numbers));
    EXPECT_TRUE(numbers.empty());
}

TEST(ReadNumbers, SingleNumber)
{
    std::istringstream input("3.14");
    std::vector<double> numbers;
    EXPECT_TRUE(ReadNumbers(input, numbers));
    ASSERT_EQ(numbers.size(), 1u);
    EXPECT_DOUBLE_EQ(numbers[0], 3.14);
}

TEST(ReadNumbers, MultipleNumbers)
{
    std::istringstream input("1.0 2 3.659512");
    std::vector<double> numbers;
    EXPECT_TRUE(ReadNumbers(input, numbers));
    ASSERT_EQ(numbers.size(), 3u);
    EXPECT_DOUBLE_EQ(numbers[0], 1.0);
    EXPECT_DOUBLE_EQ(numbers[1], 2.0);
    EXPECT_DOUBLE_EQ(numbers[2], 3.659512);
}

TEST(ReadNumbers, NegativeNumbers)
{
    std::istringstream input("-1.0 -2.5 -3.0");
    std::vector<double> numbers;
    EXPECT_TRUE(ReadNumbers(input, numbers));
    ASSERT_EQ(numbers.size(), 3u);
    EXPECT_DOUBLE_EQ(numbers[0], -1.0);
}

TEST(ReadNumbers, TabsAndNewlines)
{
    std::istringstream input("1.0\t2.0\n3.0");
    std::vector<double> numbers;
    EXPECT_TRUE(ReadNumbers(input, numbers));
    ASSERT_EQ(numbers.size(), 3u);
}

TEST(ReadNumbers, InvalidInputDash)
{
    std::istringstream input("- 2 3");
    std::vector<double> numbers;
    EXPECT_FALSE(ReadNumbers(input, numbers));
}

TEST(ReadNumbers, InvalidInputLetters)
{
    std::istringstream input("1.0 abc 3.0");
    std::vector<double> numbers;
    EXPECT_FALSE(ReadNumbers(input, numbers));
}

TEST(ReadNumbers, InvalidInputMixed)
{
    std::istringstream input("1.0 2.5x 3.0");
    std::vector<double> numbers;
    EXPECT_FALSE(ReadNumbers(input, numbers));
}

TEST(ReadNumbers, ClearsVectorBeforeReading)
{
    std::istringstream input("5.0");
    std::vector<double> numbers = { 1.0, 2.0, 3.0 };
    EXPECT_TRUE(ReadNumbers(input, numbers));
    ASSERT_EQ(numbers.size(), 1u);
    EXPECT_DOUBLE_EQ(numbers[0], 5.0);
}

// ============================================================
// addArithmeticMeanOfPositiveElements tests
// ============================================================

TEST(addArithmeticMeanOfPositiveElements, EmptyVector)
{
    std::vector<double> numbers;
    addArithmeticMeanOfPositiveElements(numbers);
    EXPECT_TRUE(numbers.empty());
}

TEST(addArithmeticMeanOfPositiveElements, AllNegative)
{
    std::vector<double> numbers = { -1.0, -2.0, -3.0 };
    std::vector<double> original = numbers;
    addArithmeticMeanOfPositiveElements(numbers);
    for (size_t i = 0; i < numbers.size(); ++i)
    {
        EXPECT_DOUBLE_EQ(numbers[i], original[i]);
    }
}

TEST(addArithmeticMeanOfPositiveElements, AllPositive)
{
    // {1, 2, 3} -> avg = 2.0 -> {3, 4, 5}
    std::vector<double> numbers = { 1.0, 2.0, 3.0 };
    addArithmeticMeanOfPositiveElements(numbers);
    EXPECT_DOUBLE_EQ(numbers[0], 3.0);
    EXPECT_DOUBLE_EQ(numbers[1], 4.0);
    EXPECT_DOUBLE_EQ(numbers[2], 5.0);
}

TEST(addArithmeticMeanOfPositiveElements, MixedNumbers)
{
    // {4, 16, -30, 10} -> positive avg = 10 -> {14, 26, -20, 20}
    std::vector<double> numbers = { 4.0, 16.0, -30.0, 10.0 };
    addArithmeticMeanOfPositiveElements(numbers);
    EXPECT_DOUBLE_EQ(numbers[0], 14.0);
    EXPECT_DOUBLE_EQ(numbers[1], 26.0);
    EXPECT_DOUBLE_EQ(numbers[2], -20.0);
    EXPECT_DOUBLE_EQ(numbers[3], 20.0);
}

TEST(addArithmeticMeanOfPositiveElements, Example1)
{
    std::vector<double> numbers = { 1.0, 2.0, 3.659512 };
    addArithmeticMeanOfPositiveElements(numbers);
    double avg = 6.659512 / 3.0;
    EXPECT_NEAR(numbers[0], 1.0 + avg, 1e-9);
    EXPECT_NEAR(numbers[1], 2.0 + avg, 1e-9);
    EXPECT_NEAR(numbers[2], 3.659512 + avg, 1e-9);
}

TEST(addArithmeticMeanOfPositiveElements, ZerosAreNotPositive)
{
    std::vector<double> numbers = { 0.0, 0.0, -1.0 };
    std::vector<double> original = numbers;
    addArithmeticMeanOfPositiveElements(numbers);
    for (size_t i = 0; i < numbers.size(); ++i)
    {
        EXPECT_DOUBLE_EQ(numbers[i], original[i]);
    }
}

TEST(addArithmeticMeanOfPositiveElements, SinglePositive)
{
    std::vector<double> numbers = { 5.0 };
    addArithmeticMeanOfPositiveElements(numbers);
    EXPECT_DOUBLE_EQ(numbers[0], 10.0);
}

// ============================================================
// PrintSortedNumbers tests
// ============================================================

TEST(PrintSortedNumbers, EmptyVector)
{
    std::vector<double> numbers;
    std::ostringstream output;
    PrintSortedNumbers(numbers, output);
    EXPECT_EQ(output.str(), "");
}

TEST(PrintSortedNumbers, SingleNumber)
{
    std::vector<double> numbers = { 3.14159 };
    std::ostringstream output;
    PrintSortedNumbers(numbers, output);
    EXPECT_EQ(output.str(), "3.142");
}

TEST(PrintSortedNumbers, SortsCorrectly)
{
    std::vector<double> numbers = { 3.0, 1.0, 2.0 };
    std::ostringstream output;
    PrintSortedNumbers(numbers, output);
    EXPECT_EQ(output.str(), "1.000 2.000 3.000");
}

TEST(PrintSortedNumbers, DoesNotModifyOriginal)
{
    std::vector<double> numbers = { 3.0, 1.0, 2.0 };
    std::vector<double> original = numbers;
    std::ostringstream output;
    PrintSortedNumbers(numbers, output);
    EXPECT_EQ(numbers, original);
}

TEST(PrintSortedNumbers, NegativeNumbers)
{
    std::vector<double> numbers = { -1.0004, -703.0, -3.659512, -11.0 };
    std::ostringstream output;
    PrintSortedNumbers(numbers, output);
    EXPECT_EQ(output.str(), "-703.000 -11.000 -3.660 -1.000");
}

TEST(PrintSortedNumbers, PrecisionRounding)
{
    std::vector<double> numbers = { 2.3 };
    std::ostringstream output;
    PrintSortedNumbers(numbers, output);
    EXPECT_EQ(output.str(), "2.300");
}

// ============================================================
// Integration tests
// ============================================================

TEST(Integration, Example1)
{
    std::istringstream input("1.0 2 3.659512");
    std::vector<double> numbers;
    ASSERT_TRUE(ReadNumbers(input, numbers));
    addArithmeticMeanOfPositiveElements(numbers);
    std::ostringstream output;
    PrintSortedNumbers(numbers, output);
    EXPECT_EQ(output.str(), "3.220 4.220 5.879");
}

TEST(Integration, Example2)
{
    std::istringstream input("4 16 -30 10");
    std::vector<double> numbers;
    ASSERT_TRUE(ReadNumbers(input, numbers));
    addArithmeticMeanOfPositiveElements(numbers);
    std::ostringstream output;
    PrintSortedNumbers(numbers, output);
    EXPECT_EQ(output.str(), "-20.000 14.000 20.000 26.000");
}

TEST(Integration, Example3)
{
    std::istringstream input("-1.0004000 -703 -3.659512 -11");
    std::vector<double> numbers;
    ASSERT_TRUE(ReadNumbers(input, numbers));
    addArithmeticMeanOfPositiveElements(numbers);
    std::ostringstream output;
    PrintSortedNumbers(numbers, output);
    EXPECT_EQ(output.str(), "-703.000 -11.000 -3.660 -1.000");
}

TEST(Integration, Example4Error)
{
    std::istringstream input("- 2 3");
    std::vector<double> numbers;
    EXPECT_FALSE(ReadNumbers(input, numbers));
}

TEST(Integration, EmptyInput)
{
    std::istringstream input("");
    std::vector<double> numbers;
    ASSERT_TRUE(ReadNumbers(input, numbers));
    addArithmeticMeanOfPositiveElements(numbers);
    std::ostringstream output;
    PrintSortedNumbers(numbers, output);
    EXPECT_EQ(output.str(), "");
}
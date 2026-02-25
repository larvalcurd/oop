#include "numbers.h"

#include <algorithm>
#include <iomanip>
#include <numeric>
#include <sstream>
#include <string>

bool ReadNumbers(std::istream& input, std::vector<double>& numbers)
{
    numbers.clear();
    std::string token;

    while (input >> token)
    {
        std::istringstream tokenStream(token);
        double value;

        if (!(tokenStream >> value))
        {
            return false;
        }

        char remaining;
        if (tokenStream >> remaining)
        {
            return false;
        }

        numbers.push_back(value);
    }

    return true;
}

void addArithmeticMeanOfPositiveElements(std::vector<double>& numbers)
{
    if (numbers.empty())
    {
        return;
    }

    int countPositive = static_cast<int>(std::count_if(
        numbers.begin(), numbers.end(),
        [](double x) { return x > 0; }));

    if (countPositive == 0)
    {
        return;
    }

    double sumPositive = std::accumulate(
        numbers.begin(), numbers.end(), 0.0,
        [](double sum, double x) { return x > 0 ? sum + x : sum; });

    double average = sumPositive / countPositive;

    for (double& num : numbers)
    {
        num += average;
    }
}

void PrintSortedNumbers(const std::vector<double>& numbers, std::ostream& output)
{
    if (numbers.empty())
    {
        return;
    }

    std::vector<double> sorted = numbers;
    std::sort(sorted.begin(), sorted.end());

    output << std::fixed << std::setprecision(3);

    for (size_t i = 0; i < sorted.size(); ++i)
    {
        if (i > 0)
        {
            output << " ";
        }
        output << sorted[i];
    }
}
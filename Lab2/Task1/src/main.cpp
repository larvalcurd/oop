#include "numbers.h"
#include <iostream>

int main()
{
    std::vector<double> numbers;

    if (!ReadNumbers(std::cin, numbers))
    {
        std::cout << "ERROR" << std::endl;
        return 0;
    }

    addArithmeticMeanOfPositiveElements(numbers);
    PrintSortedNumbers(numbers, std::cout);

    if (!numbers.empty())
    {
        std::cout << std::endl;
    }

    return 0;
}
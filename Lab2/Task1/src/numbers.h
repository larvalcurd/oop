#pragma once

#include <iostream>
#include <vector>

bool ReadNumbers(std::istream& input, std::vector<double>& numbers);
void addArithmeticMeanOfPositiveElements(std::vector<double>& numbers);
void PrintSortedNumbers(const std::vector<double>& numbers, std::ostream& output);

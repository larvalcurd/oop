#pragma once

#include <string>

constexpr int MIN_RADIX = 2;
constexpr int MAX_RADIX = 36;

int StringToInt(const std::string& str, int radix, bool& wasError);
std::string IntToString(int value, int radix, bool& wasError);

int CharToDigit(char c);
char DigitToChar(int digit);
bool IsValidRadix(int radix);

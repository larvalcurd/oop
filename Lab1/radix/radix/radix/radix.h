#pragma once
#include <string>

int StringToInt(const std::string& str, int radix, bool & wasError);
std::string IntToString(int value, int radix, bool & wasError);

int CharToDigit(char c);
char DigitToChar(int digit);
bool ValidateRadix(int radix);

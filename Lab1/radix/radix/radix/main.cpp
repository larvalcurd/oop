#include <iostream>
#include <string>
#include "radix.h"

int main(int argc, char* argv[])
{
    if (argc != 4) {
        std::cerr << "Usage: radix.exe <source radix> <destination radix> <value>\n";
        return 1;
    }

    int srcRadix = 0;
    int dstRadix = 0;

    try {
        srcRadix = std::stoi(argv[1]);
        dstRadix = std::stoi(argv[2]);
    }
    catch (...) {
        std::cerr << "Error: cannot parse radix. Expected an integer.\n";
        return 1;
    }

    if (!ValidateRadix(srcRadix) || !ValidateRadix(dstRadix)) {
        std::cerr << "Error: radix must be between 2 and 36.\n";
        return 1;
    }

    const std::string valueStr = argv[3];
    bool wasError = false;

    int value = StringToInt(valueStr, srcRadix, wasError);
    if (wasError) {
        std::cerr << "Error: invalid input value or overflow in source radix.\n";
        return 1;
    }

    std::string output = IntToString(value, dstRadix, wasError);
    if (wasError) {
        std::cerr << "Error: cannot convert integer to destination radix.\n";
        return 1;
    }

    std::cout << output << "\n";
    return 0;
}
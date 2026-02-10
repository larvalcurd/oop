#pragma once

#include <string>
#include <iostream>

void printHelp();

int processCLI(const std::string& inputFile,
               const std::string& outputFile,
               const std::string& search,
               const std::string& replace);

int processStdin();

std::string replaceInLine(const std::string& line,
                         const std::string& search,
                         const std::string& replace);
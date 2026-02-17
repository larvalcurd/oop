#pragma once
#include <cstdint>
#include <fstream>

void BuildLookupTables(uint8_t encTable[256], uint8_t decTable[256], uint8_t key);
bool TransformFile(std::ifstream& input, std::ofstream& output, const uint8_t table[256]);
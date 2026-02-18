#pragma once

#include <array>
#include <cstdint>
#include <fstream>

using LookupTable = std::array<uint8_t, 256>;

void BuildLookupTables(LookupTable& encTable,
	LookupTable& decTable,
	uint8_t key);

bool TransformFile(std::ifstream& input,
	std::ofstream& output,
	const LookupTable& table);
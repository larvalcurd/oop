#pragma once

#include <array>
#include <cstdint>
#include <fstream>

inline constexpr char MODE_CRYPT[] = "crypt";
inline constexpr char MODE_DECRYPT[] = "decrypt";

using LookupTable = std::array<uint8_t, 256>;

LookupTable BuildLookupTable(uint8_t key, bool encrypt);

bool ApplyTableToStream(std::ifstream& input,
	std::ofstream& output,
	const LookupTable& table);
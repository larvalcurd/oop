#include "Cipher.h"
#include <utility>

namespace
{

const std::pair<int, int> BIT_MAP[] = {
	{ 7, 5 }, { 6, 1 }, { 5, 0 }, { 4, 7 },
	{ 3, 6 }, { 2, 4 }, { 1, 3 }, { 0, 2 }
};

const size_t BUFFER_SIZE = 8192;

} // namespace

void BuildLookupTables(uint8_t encTable[256], uint8_t decTable[256], uint8_t key)
{
	for (int i = 0; i < 256; ++i)
	{
		uint8_t xored = static_cast<uint8_t>(i) ^ key;
		uint8_t shuffled = 0;
		for (const auto& mapping : BIT_MAP)
		{
			shuffled |= ((xored >> mapping.first) & 1) << mapping.second;
		}
		encTable[i] = shuffled;
		decTable[shuffled] = static_cast<uint8_t>(i);
	}
}

bool TransformFile(std::ifstream& input, std::ofstream& output, const uint8_t table[256])
{
	char buffer[BUFFER_SIZE];

	while (input.read(buffer, BUFFER_SIZE) || input.gcount() > 0)
	{
		std::streamsize bytesRead = input.gcount();

		for (std::streamsize i = 0; i < bytesRead; ++i)
		{
			buffer[i] = static_cast<char>(table[static_cast<uint8_t>(buffer[i])]);
		}

		output.write(buffer, bytesRead);
		if (!output)
		{
			return false;
		}
	}

	return input.eof();
}
#include "Cipher.h"
#include <utility>

namespace
{

constexpr std::array<std::pair<int, int>, 8> BIT_MAP = { { { 7, 5 }, { 6, 1 }, { 5, 0 }, { 4, 7 },
	{ 3, 6 }, { 2, 4 }, { 1, 3 }, { 0, 2 } } };

constexpr size_t BUFFER_SIZE = 8192;

} // namespace

void BuildLookupTables(LookupTable& encTable,
	LookupTable& decTable,
	uint8_t key)
{
	for (size_t i = 0; i < encTable.size(); ++i)
	{
		uint8_t value = static_cast<uint8_t>(i);
		uint8_t xored = static_cast<uint8_t>(value ^ key);
		uint8_t shuffled = 0;

		for (const auto& [from, to] : BIT_MAP)
		{
			const uint8_t bit = (xored >> from) & 1u;
			shuffled |= static_cast<uint8_t>(bit << to);
		}

		encTable[i] = shuffled;
		decTable[shuffled] = value;
	}
}

bool TransformFile(std::ifstream& input,
	std::ofstream& output,
	const LookupTable& table)
{
	std::array<char, BUFFER_SIZE> buffer;

	while (true)
	{
		input.read(buffer.data(), buffer.size());
		std::streamsize bytesRead = input.gcount();

		if (bytesRead > 0)
		{
			for (std::streamsize i = 0; i < bytesRead; ++i)
			{
				unsigned char byte = static_cast<unsigned char>(buffer[i]);

				buffer[i] = static_cast<char>(table[byte]);
			}

			output.write(buffer.data(), bytesRead);
			if (!output)
				return false;
		}

		if (input.eof())
			break;

		if (input.fail())
			return false;
	}

	return true;
}
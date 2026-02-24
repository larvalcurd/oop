#include "Cipher.h"

namespace
{

constexpr std::size_t BUFFER_SIZE = 8192;

struct BitMapping
{
	int from;
	int to;
};

constexpr std::array<BitMapping, 8> BIT_MAP = { { { 7, 5 }, { 6, 1 }, { 5, 0 }, { 4, 7 },
	{ 3, 6 }, { 2, 4 }, { 1, 3 }, { 0, 2 } } };

uint8_t ShuffleBits(uint8_t value)
{
	uint8_t result = 0;

	for (const auto& mapping : BIT_MAP)
	{
		uint8_t bit = (value >> mapping.from) & 1u;
		result |= static_cast<uint8_t>(bit << mapping.to);
	}

	return result;
}

LookupTable BuildEncryptTable(uint8_t key)
{
	LookupTable table{};

	for (std::size_t i = 0; i < table.size(); ++i)
	{
		uint8_t byte = static_cast<uint8_t>(i);
		uint8_t xored = byte ^ key;
		table[i] = ShuffleBits(xored);
	}

	return table;
}

LookupTable BuildDecryptTable(uint8_t key)
{
	LookupTable encTable = BuildEncryptTable(key);
	LookupTable decTable{};

	for (std::size_t i = 0; i < encTable.size(); ++i)
	{
		uint8_t byte = static_cast<uint8_t>(i);
		decTable[encTable[i]] = byte;
	}

	return decTable;
}

} // namespace

LookupTable BuildLookupTable(uint8_t key, bool encrypt)
{
	return encrypt ? BuildEncryptTable(key) : BuildDecryptTable(key);
}

bool ApplyTableToStream(std::ifstream& input,
	std::ofstream& output,
	const LookupTable& table)
{
	std::array<char, BUFFER_SIZE> buffer{};

	while (input.read(buffer.data(), buffer.size()) || input.gcount() > 0)
	{
		std::streamsize bytesRead = input.gcount();

		for (std::streamsize i = 0; i < bytesRead; ++i)
		{
			auto byte = static_cast<uint8_t>(buffer[i]);
			buffer[i] = static_cast<char>(table[byte]);
		}

		output.write(buffer.data(), bytesRead);

		if (!output)
		{
			return false;
		}
	}

	output.flush();

	return !input.bad() && output.good();
}
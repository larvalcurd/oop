#include <optional>
#include <string>

constexpr int MAX_UPPER_BOUND = 100'000'000;

struct Args
{
	int upperBound;
};

std::optional<Args> ParseArgs(int argc, char* argv[]);

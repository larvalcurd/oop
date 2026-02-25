#pragma once

#include <iostream>
#include <string>
#include <vector>

using Grid = std::vector<std::string>;

namespace Life
{
Grid readField(std::istream& in);
void writeField(const Grid& grid, std::ostream& out);
Grid calculateNextGeneration(const Grid& grid);
} // namespace Life
#pragma once

#include <iostream>
#include <string>
#include <vector>

using Grid = std::vector<std::string>;

Grid readField(std::istream& in);
void writeField(const Grid& grid, std::ostream& out);
int countNeighbors(const Grid& grid, int r, int c);
Grid calculateNextGeneration(const Grid& grid);
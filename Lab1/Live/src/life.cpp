#include "Life.h"

namespace
{
constexpr char ALIVE = '#';
constexpr char DEAD = ' ';
constexpr char WALL = '*';

void trimCarriageReturn(std::string& line)
{
	if (!line.empty() && line.back() == '\r')
		line.pop_back();
}

bool isInsideBounds(const Grid& grid, int row, int col)
{
	return row >= 0
		&& row < static_cast<int>(grid.size())
		&& col >= 0
		&& col < static_cast<int>(grid[row].size());
}

bool isAlive(char cell)
{
	return cell == ALIVE;
}

bool isWall(char cell)
{
	return cell == WALL;
}

bool isInnerCell(int row, int col, int rows, int cols)
{
	return row > 0 && row < rows - 1 && col > 0 && col < cols - 1;
}

int countNeighbors(const Grid& grid, int row, int col)
{
	int count = 0;

	for (int dr = -1; dr <= 1; ++dr)
	{
		for (int dc = -1; dc <= 1; ++dc)
		{
			if (dr == 0 && dc == 0)
				continue;

			int neighborRow = row + dr;
			int neighborCol = col + dc;

			if (isInsideBounds(grid, neighborRow, neighborCol)
				&& isAlive(grid[neighborRow][neighborCol]))
			{
				++count;
			}
		}
	}

	return count;
}

char getNextState(char currentCell, int neighbors)
{
	if (isWall(currentCell))
		return currentCell;

	bool alive = isAlive(currentCell);

	if (alive)
		return (neighbors == 2 || neighbors == 3) ? ALIVE : DEAD;

	return (neighbors == 3) ? ALIVE : currentCell;
}
} // namespace

namespace Life
{
Grid readField(std::istream& in)
{
	Grid grid;
	std::string line;

	while (std::getline(in, line))
	{
		trimCarriageReturn(line);
		grid.push_back(line);
	}

	return grid;
}

void writeField(const Grid& grid, std::ostream& out)
{
	for (const auto& line : grid)
		out << line << "\n";
}

Grid calculateNextGeneration(const Grid& grid)
{
	Grid next = grid;
	int rows = static_cast<int>(grid.size());

	if (rows < 3)
		return next;

	for (int row = 1; row < rows - 1; ++row)
	{
		int cols = static_cast<int>(grid[row].size());

		for (int col = 1; col < cols - 1; ++col)
		{
			int neighbors = countNeighbors(grid, row, col);
			next[row][col] = getNextState(grid[row][col], neighbors);
		}
	}

	return next;
}
} // namespace Life
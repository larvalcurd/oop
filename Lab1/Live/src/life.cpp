#include "Life.h"

Grid readField(std::istream& in)
{
	Grid grid;
	std::string line;
	while (std::getline(in, line))
	{
		if (!line.empty() && line.back() == '\r')
			line.pop_back();
		grid.push_back(line);
	}
	return grid;
}

void writeField(const Grid& grid, std::ostream& out)
{
	for (const auto& line : grid)
		out << line << "\n";
}

int countNeighbors(const Grid& grid, int r, int c)
{
	int count = 0;
	const int rows = static_cast<int>(grid.size());
	for (int dr = -1; dr <= 1; ++dr)
	{
		for (int dc = -1; dc <= 1; ++dc)
		{
			if (dr == 0 && dc == 0)
				continue;
			int nr = r + dr;
			int nc = c + dc;
			if (nr >= 0 && nr < rows && nc >= 0 && nc < static_cast<int>(grid[nr].size()))
			{
				if (grid[nr][nc] == '#')
					++count;
			}
		}
	}
	return count;
}

Grid calculateNextGeneration(const Grid& grid)
{
	Grid next = grid;
	const int rows = static_cast<int>(grid.size());
	if (rows < 3)
		return next;

	for (int r = 1; r < rows - 1; ++r)
	{
		const int cols = static_cast<int>(grid[r].size());
		for (int c = 1; c < cols - 1; ++c)
		{
			if (grid[r][c] == '*')
				continue;

			int n = countNeighbors(grid, r, c);
			bool alive = (grid[r][c] == '#');

			if (alive)
			{
				if (n < 2 || n > 3)
					next[r][c] = ' ';
			}
			else
			{
				if (n == 3)
					next[r][c] = '#';
			}
		}
	}
	return next;
}

#include "Life.h"
#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <sstream>

namespace
{
Grid gridFromString(const std::string& s)
{
	std::istringstream ss(s);
	return Life::readField(ss);
}

std::string gridToString(const Grid& g)
{
	std::ostringstream ss;
	Life::writeField(g, ss);
	return ss.str();
}

void expectGridsEqual(const Grid& actual, const Grid& expected)
{
	ASSERT_EQ(actual.size(), expected.size()) << "Row count mismatch";
	for (size_t i = 0; i < actual.size(); ++i)
		EXPECT_EQ(actual[i], expected[i]) << "Mismatch at row " << i;
}
} // namespace

// ═══════════════════════════════════════════
// Still lifes — фигуры, которые не меняются.
// Проверяют, что клетки с 2-3 соседями выживают
// и что мёртвые клетки с ≠3 соседями не рождаются.
// ═══════════════════════════════════════════

TEST(StillLife, Block)
{
	Grid g = gridFromString(
		"******\n"
		"*    *\n"
		"* ## *\n"
		"* ## *\n"
		"*    *\n"
		"******");
	expectGridsEqual(Life::calculateNextGeneration(g), g);
}

TEST(StillLife, Beehive)
{
	Grid g = gridFromString(
		"********\n"
		"*      *\n"
		"*  ##  *\n"
		"* #  # *\n"
		"*  ##  *\n"
		"*      *\n"
		"********");
	expectGridsEqual(Life::calculateNextGeneration(g), g);
}

// ═══════════════════════════════════════════
// Oscillators — фигуры, которые циклически переключаются.
// ═══════════════════════════════════════════

TEST(Oscillator, BlinkerHtoV)
{
	Grid g = gridFromString(
		"*******\n"
		"*     *\n"
		"* ### *\n"
		"*     *\n"
		"*******");
	Grid exp = gridFromString(
		"*******\n"
		"*  #  *\n"
		"*  #  *\n"
		"*  #  *\n"
		"*******");
	expectGridsEqual(Life::calculateNextGeneration(g), exp);
}

TEST(Oscillator, BlinkerVtoH)
{
	Grid g = gridFromString(
		"*******\n"
		"*  #  *\n"
		"*  #  *\n"
		"*  #  *\n"
		"*******");
	Grid exp = gridFromString(
		"*******\n"
		"*     *\n"
		"* ### *\n"
		"*     *\n"
		"*******");
	expectGridsEqual(Life::calculateNextGeneration(g), exp);
}

TEST(Oscillator, BlinkerPeriod2)
{
	Grid g = gridFromString(
		"*******\n"
		"*     *\n"
		"* ### *\n"
		"*     *\n"
		"*******");
	Grid g2 = Life::calculateNextGeneration(Life::calculateNextGeneration(g));
	expectGridsEqual(g2, g);
}

TEST(Oscillator, Toad)
{
	Grid g = gridFromString(
		"********\n"
		"*      *\n"
		"*      *\n"
		"*  ### *\n"
		"* ###  *\n"
		"*      *\n"
		"*      *\n"
		"********");
	Grid exp = gridFromString(
		"********\n"
		"*      *\n"
		"*   #  *\n"
		"* #  # *\n"
		"* #  # *\n"
		"*  #   *\n"
		"*      *\n"
		"********");
	expectGridsEqual(Life::calculateNextGeneration(g), exp);
}

// ═══════════════════════════════════════════
// Spaceship — движущаяся фигура.
// ═══════════════════════════════════════════

TEST(Spaceship, GliderOneStep)
{
	Grid g = gridFromString(
		"********\n"
		"*      *\n"
		"*  #   *\n"
		"*   #  *\n"
		"* ###  *\n"
		"*      *\n"
		"*      *\n"
		"********");
	Grid exp = gridFromString(
		"********\n"
		"*      *\n"
		"*      *\n"
		"* # #  *\n"
		"*  ##  *\n"
		"*  #   *\n"
		"*      *\n"
		"********");
	expectGridsEqual(Life::calculateNextGeneration(g), exp);
}

// ═══════════════════════════════════════════
// Death — проверка правил смерти клеток.
// ═══════════════════════════════════════════

TEST(Death, SingleCellDies)
{
	Grid g = gridFromString(
		"*****\n"
		"*   *\n"
		"* # *\n"
		"*   *\n"
		"*****");
	Grid exp = gridFromString(
		"*****\n"
		"*   *\n"
		"*   *\n"
		"*   *\n"
		"*****");
	expectGridsEqual(Life::calculateNextGeneration(g), exp);
}

TEST(Death, TwoCellsDie)
{
	Grid g = gridFromString(
		"*****\n"
		"*   *\n"
		"*## *\n"
		"*   *\n"
		"*****");
	Grid exp = gridFromString(
		"*****\n"
		"*   *\n"
		"*   *\n"
		"*   *\n"
		"*****");
	expectGridsEqual(Life::calculateNextGeneration(g), exp);
}

TEST(Death, Overcrowding)
{
	Grid g = gridFromString(
		"*******\n"
		"*     *\n"
		"*  #  *\n"
		"* ### *\n"
		"*  #  *\n"
		"*     *\n"
		"*******");
	Grid exp = gridFromString(
		"*******\n"
		"*     *\n"
		"* ### *\n"
		"* # # *\n"
		"* ### *\n"
		"*     *\n"
		"*******");
	expectGridsEqual(Life::calculateNextGeneration(g), exp);
}

TEST(Death, FiveNeighbors)
{
	Grid g = gridFromString(
		"*******\n"
		"*     *\n"
		"* ### *\n"
		"* ### *\n"
		"*     *\n"
		"*******");
	Grid exp = gridFromString(
		"*******\n"
		"*  #  *\n"
		"* # # *\n"
		"* # # *\n"
		"*  #  *\n"
		"*******");
	expectGridsEqual(Life::calculateNextGeneration(g), exp);
}

// ═══════════════════════════════════════════
// Birth — рождение мёртвой клетки при ровно 3 соседях.
// ═══════════════════════════════════════════

TEST(Birth, ExactlyThreeNeighbors)
{
	Grid g = gridFromString(
		"******\n"
		"*    *\n"
		"* #  *\n"
		"* ## *\n"
		"*    *\n"
		"******");
	Grid exp = gridFromString(
		"******\n"
		"*    *\n"
		"* ## *\n"
		"* ## *\n"
		"*    *\n"
		"******");
	expectGridsEqual(Life::calculateNextGeneration(g), exp);
}

// ═══════════════════════════════════════════
// Survival — выживание клетки при ровно 2 соседях.
// ═══════════════════════════════════════════

TEST(Survival, ExactlyTwoNeighbors)
{
	Grid g = gridFromString(
		"*****\n"
		"* # *\n"
		"* # *\n"
		"* # *\n"
		"*****");
	Grid exp = gridFromString(
		"*****\n"
		"*   *\n"
		"*###*\n"
		"*   *\n"
		"*****");
	expectGridsEqual(Life::calculateNextGeneration(g), exp);
}

// ═══════════════════════════════════════════
// Simultaneous — проверка одновременности обновления.
// ═══════════════════════════════════════════

TEST(Simultaneous, UpdateOrder)
{
	Grid g = gridFromString(
		"*******\n"
		"*     *\n"
		"* # # *\n"
		"*  #  *\n"
		"*     *\n"
		"*******");
	Grid correct_exp = gridFromString(
		"*******\n"
		"*     *\n"
		"*  #  *\n"
		"*  #  *\n"
		"*     *\n"
		"*******");
	expectGridsEqual(Life::calculateNextGeneration(g), correct_exp);
}

// ═══════════════════════════════════════════
// Edge — граничные случаи.
// ═══════════════════════════════════════════

TEST(Edge, EmptyFieldStaysEmpty)
{
	Grid g = gridFromString(
		"*****\n"
		"*   *\n"
		"*   *\n"
		"*   *\n"
		"*****");
	expectGridsEqual(Life::calculateNextGeneration(g), g);
}

TEST(Edge, MinField1x1_Alive)
{
	Grid g = gridFromString(
		"***\n"
		"*#*\n"
		"***");
	Grid exp = gridFromString(
		"***\n"
		"* *\n"
		"***");
	expectGridsEqual(Life::calculateNextGeneration(g), exp);
}

TEST(Edge, MinField1x1_Dead)
{
	Grid g = gridFromString(
		"***\n"
		"* *\n"
		"***");
	expectGridsEqual(Life::calculateNextGeneration(g), g);
}

TEST(Edge, RectangularField)
{
	Grid g = gridFromString(
		"**********\n"
		"*        *\n"
		"* ###    *\n"
		"*        *\n"
		"**********");
	Grid exp = gridFromString(
		"**********\n"
		"*  #     *\n"
		"*  #     *\n"
		"*  #     *\n"
		"**********");
	expectGridsEqual(Life::calculateNextGeneration(g), exp);
}

TEST(Edge, AliveNextToBorder)
{
	Grid g = gridFromString(
		"*****\n"
		"*#  *\n"
		"*#  *\n"
		"*#  *\n"
		"*****");
	Grid exp = gridFromString(
		"*****\n"
		"*   *\n"
		"*## *\n"
		"*   *\n"
		"*****");
	expectGridsEqual(Life::calculateNextGeneration(g), exp);
}

TEST(Edge, EmptyInput)
{
	Grid g = gridFromString("");
	Grid next = Life::calculateNextGeneration(g);
	EXPECT_TRUE(next.empty());
}

// ═══════════════════════════════════════════
// I/O — ввод-вывод.
// ═══════════════════════════════════════════

TEST(IO, StreamRoundTrip)
{
	Grid g = gridFromString(
		"*****\n"
		"* # *\n"
		"*## *\n"
		"*   *\n"
		"*****");
	Grid back = gridFromString(gridToString(g));
	expectGridsEqual(back, g);
}

TEST(IO, FileRoundTrip)
{
	const char* tmpIn = "_test_in.txt";
	const char* tmpOut = "_test_out.txt";

	Grid g = gridFromString(
		"*******\n"
		"*     *\n"
		"* ### *\n"
		"*     *\n"
		"*******");

	{
		std::ofstream f(tmpIn);
		Life::writeField(g, f);
	}

	Grid read;
	{
		std::ifstream f(tmpIn);
		read = Life::readField(f);
	}
	expectGridsEqual(read, g);

	Grid next = Life::calculateNextGeneration(read);
	{
		std::ofstream f(tmpOut);
		Life::writeField(next, f);
	}

	Grid readNext;
	{
		std::ifstream f(tmpOut);
		readNext = Life::readField(f);
	}

	Grid exp = gridFromString(
		"*******\n"
		"*  #  *\n"
		"*  #  *\n"
		"*  #  *\n"
		"*******");
	expectGridsEqual(readNext, exp);

	std::remove(tmpIn);
	std::remove(tmpOut);
}
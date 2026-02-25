#include "life.h"
#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <sstream>

static Grid gridFromString(const std::string& s)
{
	std::istringstream ss(s);
	return readField(ss);
}

static std::string gridToString(const Grid& g)
{
	std::ostringstream ss;
	writeField(g, ss);
	return ss.str();
}

static void expectGridsEqual(const Grid& actual, const Grid& expected)
{
	ASSERT_EQ(actual.size(), expected.size()) << "Row count mismatch";
	for (size_t i = 0; i < actual.size(); ++i)
		EXPECT_EQ(actual[i], expected[i]) << "Mismatch at row " << i;
}

// ═══════════════════════════════════════════
// Still lifes — фигуры, которые не меняются.
// Проверяют, что клетки с 2-3 соседями выживают
// и что мёртвые клетки с ≠3 соседями не рождаются.
// ═══════════════════════════════════════════

// Блок: каждая живая клетка имеет ровно 3 соседа → выживает.
// Мёртвые вокруг имеют ≤2 соседа → не рождаются.
TEST(StillLife, Block)
{
	Grid g = gridFromString(
		"******\n"
		"*    *\n"
		"* ## *\n"
		"* ## *\n"
		"*    *\n"
		"******");
	expectGridsEqual(calculateNextGeneration(g), g);
}

// Улей: другая геометрия неподвижной фигуры.
// Живые имеют по 2 соседа, мёртвые вокруг — нигде не ровно 3.
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
	expectGridsEqual(calculateNextGeneration(g), g);
}

// ═══════════════════════════════════════════
// Oscillators — фигуры, которые циклически переключаются.
// Проверяют одновременное рождение, смерть и выживание.
// ═══════════════════════════════════════════

// Горизонтальный блинкер → вертикальный.
// Крайние (1 сосед) умирают, сверху/снизу центра (3 соседа) рождаются,
// центр (2 соседа) выживает.
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
	expectGridsEqual(calculateNextGeneration(g), exp);
}

// Вертикальный блинкер → горизонтальный. Обратное направление.
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
	expectGridsEqual(calculateNextGeneration(g), exp);
}

// Два шага возвращают блинкер к исходному состоянию.
// Косвенно проверяет двухбуферность: при обновлении «по месту»
// период бы нарушился.
TEST(Oscillator, BlinkerPeriod2)
{
	Grid g = gridFromString(
		"*******\n"
		"*     *\n"
		"* ### *\n"
		"*     *\n"
		"*******");
	Grid g2 = calculateNextGeneration(calculateNextGeneration(g));
	expectGridsEqual(g2, g);
}

// Жаба — осциллятор периода 2 из 6 клеток.
// Комплексный тест: одновременно рождаются, умирают и выживают клетки.
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
	expectGridsEqual(calculateNextGeneration(g), exp);
}

// ═══════════════════════════════════════════
// Spaceship — движущаяся фигура.
// Интеграционный тест: все три правила работают согласованно,
// порождая «движение» фигуры по полю.
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
	expectGridsEqual(calculateNextGeneration(g), exp);
}

// ═══════════════════════════════════════════
// Death — проверка правил смерти клеток.
// ═══════════════════════════════════════════

// Одиночная клетка: 0 соседей → смерть от одиночества.
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
	expectGridsEqual(calculateNextGeneration(g), exp);
}

// Две соседние клетки: каждая имеет 1 соседа → обе умирают.
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
	expectGridsEqual(calculateNextGeneration(g), exp);
}

// Крест: центральная клетка имеет 4 соседа → перенаселение → смерть.
// Угловые мёртвые клетки имеют по 3 соседа → рождаются.
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
	expectGridsEqual(calculateNextGeneration(g), exp);
}

// Блок 2×3: центральные клетки имеют по 5 соседей → смерть.
// Угловые имеют по 3 → выживают. Проверяет смерть при >3 соседях.
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
	expectGridsEqual(calculateNextGeneration(g), exp);
}

// ═══════════════════════════════════════════
// Birth — рождение мёртвой клетки при ровно 3 соседях.
// ═══════════════════════════════════════════

// L-образная фигура из 3 клеток: пустая клетка рядом
// имеет ровно 3 живых соседа → рождается.
// Все 3 исходных клетки имеют по 2 соседа → выживают → блок.
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
	expectGridsEqual(calculateNextGeneration(g), exp);
}

// ═══════════════════════════════════════════
// Survival — выживание клетки при ровно 2 соседях.
// ═══════════════════════════════════════════

// Вертикальная линия из 3: средняя клетка имеет ровно 2 соседа → выживает.
// Крайние имеют по 1 → умирают. Это тот же блинкер, но фокус на выживании.
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
	expectGridsEqual(calculateNextGeneration(g), exp);
}

// ═══════════════════════════════════════════
// Simultaneous — проверка одновременности обновления.
// При последовательном обновлении «по месту» (сверху вниз)
// результат был бы ДРУГИМ, что позволяет отловить баг.
// ═══════════════════════════════════════════

// Две клетки сверху и одна снизу между ними:
//   * # # *
//   *  #  *
// «По месту»: сначала (2,2) и (2,4) умирают (1 сосед),
// потом (3,3) видит 0 соседей → тоже умирает → пустое поле.
// Правильно (двухбуферно): (3,3) читает ИСХОДНОЕ → 2 соседа → выживает.
TEST(Simultaneous, UpdateOrder)
{
	Grid g = gridFromString(
		"*******\n"
		"*     *\n"
		"* # # *\n"
		"*  #  *\n"
		"*     *\n"
		"*******");
	Grid exp = gridFromString(
		"*******\n"
		"*     *\n"
		"*     *\n"
		"*     *\n"
		"*     *\n"
		"*******");
	// ↑ При неправильной реализации (по месту) — всё умрёт.
	// Но при правильной (3,3) выживает:
	Grid correct_exp = gridFromString(
		"*******\n"
		"*     *\n"
		"*  #  *\n"
		"*  #  *\n"
		"*     *\n"
		"*******");
	expectGridsEqual(calculateNextGeneration(g), correct_exp);
}

// ═══════════════════════════════════════════
// Edge — граничные случаи.
// ═══════════════════════════════════════════

// Пустое поле: ничего не рождается, ничего не умирает.
TEST(Edge, EmptyFieldStaysEmpty)
{
	Grid g = gridFromString(
		"*****\n"
		"*   *\n"
		"*   *\n"
		"*   *\n"
		"*****");
	expectGridsEqual(calculateNextGeneration(g), g);
}

// Минимальное поле 1×1, живая клетка: 0 соседей → умирает.
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
	expectGridsEqual(calculateNextGeneration(g), exp);
}

// Минимальное поле 1×1, мёртвая клетка: нет соседей → не рождается.
TEST(Edge, MinField1x1_Dead)
{
	Grid g = gridFromString(
		"***\n"
		"* *\n"
		"***");
	expectGridsEqual(calculateNextGeneration(g), g);
}

// Прямоугольное (не квадратное) поле: проверяет корректность индексации.
// Блинкер в широком поле — должен работать так же.
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
	expectGridsEqual(calculateNextGeneration(g), exp);
}

// Живые клетки вплотную к границе *:
// Проверяет, что * не считается живым соседом.
// Вертикальная линия у левой стенки — блинкер, но упирается в *.
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
	expectGridsEqual(calculateNextGeneration(g), exp);
}

// Пустой ввод: пустой вектор → пустой вектор.
TEST(Edge, EmptyInput)
{
	Grid g = gridFromString("");
	Grid next = calculateNextGeneration(g);
	EXPECT_TRUE(next.empty());
}

// ═══════════════════════════════════════════
// countNeighbors — юнит-тесты внутренней функции.
// Нельзя сделать визуальными: функция возвращает int,
// а не поле. Проверяем корректность подсчёта напрямую.
// ═══════════════════════════════════════════

// L-фигура: проверка подсчёта для клеток с 2 и 3 соседями.
TEST(CountNeighbors, ThreeAlive)
{
	Grid g = gridFromString(
		"*****\n"
		"* # *\n"
		"*## *\n"
		"*   *\n"
		"*****");
	EXPECT_EQ(countNeighbors(g, 1, 2), 2);
	EXPECT_EQ(countNeighbors(g, 2, 1), 2);
	EXPECT_EQ(countNeighbors(g, 1, 1), 3);
}

// Одна клетка в углу: все соседи — * или пусто → 0 соседей.
// Проверяет, что * не считается живым.
TEST(CountNeighbors, CornerCellZeroNeighbors)
{
	Grid g = gridFromString(
		"*****\n"
		"*#  *\n"
		"*   *\n"
		"*****");
	EXPECT_EQ(countNeighbors(g, 1, 1), 0);
}

// ═══════════════════════════════════════════
// I/O — ввод-вывод.
// ═══════════════════════════════════════════

// Запись в stringstream → чтение обратно → поле идентично.
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

// Полный цикл через файлы:
// запись → чтение → вычисление → запись → чтение → проверка.
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
		writeField(g, f);
	}
	Grid read;
	{
		std::ifstream f(tmpIn);
		read = readField(f);
	}
	expectGridsEqual(read, g);

	Grid next = calculateNextGeneration(read);
	{
		std::ofstream f(tmpOut);
		writeField(next, f);
	}
	Grid readNext;
	{
		std::ifstream f(tmpOut);
		readNext = readField(f);
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
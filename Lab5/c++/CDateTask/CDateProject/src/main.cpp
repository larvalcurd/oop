#include "CDate.h"
#include <iomanip>
#include <iostream>
#include <sstream>

void printTestHeader(const std::string& title)
{
	std::cout << "\n--- " << title << " ---\n";
}

void demoConstructors()
{
	printTestHeader("Constructors & Getters");
	CDate d1; // default 01.01.1970
	CDate d2(1, Month::JANUARY, 2023); // explicit date
	CDate d3(365u); // 1 year after epoch (01.01.1971)

	std::cout << "Default: " << d1 << " (WeekDay: " << static_cast<int>(d1.GetWeekDay()) << ")\n";
	std::cout << "From parts: " << d2 << " (WeekDay: " << static_cast<int>(d2.GetWeekDay()) << ")\n";
	std::cout << "From timestamp 365: " << d3 << " (WeekDay: " << static_cast<int>(d3.GetWeekDay()) << ")\n";

	// Invalid constructor
	CDate invalidDate(29, Month::FEBRUARY, 2023);
	std::cout << "Invalid (29.02.2023): " << std::boolalpha << invalidDate.IsValid() << " -> " << invalidDate << "\n";
}

void demoArithmetic()
{
	printTestHeader("Arithmetic +, -, +=, -=");
	CDate d(28, Month::FEBRUARY, 2020); // leap year
	std::cout << "Initial: " << d << "\n";

	CDate d2 = d + 3;
	std::cout << "d + 3 = " << d2 << "\n";
	std::cout << "3 + d = " << 3 + d << " (commutative)\n";

	CDate d3 = d - 2;
	std::cout << "d - 2 = " << d3 << "\n";

	CDate d4(1, Month::JANUARY, 1970);
	CDate d5 = d4 - 1; // should become invalid
	std::cout << "01.01.1970 - 1 = " << d5 << " (invalid expected)\n";

	// difference between dates
	CDate a(1, Month::JANUARY, 2010);
	CDate b(30, Month::DECEMBER, 2009);
	int diff = a - b;
	std::cout << "01.01.2010 - 30.12.2009 = " << diff << " days\n";

	// +=, -=
	CDate mod(15, Month::MAY, 2023);
	std::cout << "Before += 10: " << mod;
	mod += 10;
	std::cout << " After: " << mod << "\n";

	mod -= 20;
	std::cout << "After -= 20: " << mod << "\n";
}

void demoComparisons()
{
	printTestHeader("Comparisons ==, !=, <, >, <=, >=");
	CDate d1(1, Month::JANUARY, 2000);
	CDate d2(1, Month::JANUARY, 2000);
	CDate d3(2, Month::JANUARY, 2000);
	CDate invalid(29, Month::FEBRUARY, 2001);

	std::cout << std::boolalpha;
	std::cout << d1 << " == " << d2 << " : " << (d1 == d2) << "\n";
	std::cout << d1 << " != " << d3 << " : " << (d1 != d3) << "\n";
	std::cout << d1 << " <  " << d3 << " : " << (d1 < d3) << "\n";
	std::cout << d3 << " >  " << d1 << " : " << (d3 > d1) << "\n";
	std::cout << d1 << " <= " << d2 << " : " << (d1 <= d2) << "\n";
	std::cout << d3 << " >= " << d1 << " : " << (d3 >= d1) << "\n";

	std::cout << "Invalid vs valid:\n";
	std::cout << "invalid == d1 : " << (invalid == d1) << "\n";
	std::cout << "invalid <  d1 : " << (invalid < d1) << "\n";
	std::cout << "invalid == invalid : " << (invalid == CDate(32, Month::JANUARY, 1970)) << "\n";
}

void demoIncrementDecrement()
{
	printTestHeader("Increment/Decrement operators");
	CDate d(31, Month::DECEMBER, 1999);
	std::cout << "Start: " << d << "\n";

	CDate postInc = d++;
	std::cout << "Postfix ++: " << postInc << " then " << d << "\n";

	CDate preInc = ++d;
	std::cout << "Prefix ++: " << preInc << " now " << d << "\n";

	CDate edge(1, Month::JANUARY, 1970);
	std::cout << "Edge: " << edge << " --edge gives: ";
	--edge;
	std::cout << edge << " (should be INVALID)\n";
}

void demoIO()
{
	printTestHeader("Stream I/O (operator<< and operator>>)");
	std::cout << "Using stringstream to test input.\n";

	// Valid input
	std::istringstream iss("15.08.2023");
	CDate d;
	if (iss >> d)
	{
		std::cout << "Read '15.08.2023' -> " << d << " (stream good)\n";
	}

	// Invalid date but correct format
	iss.clear();
	iss.str("31.04.2023");
	if (iss >> d)
	{
		std::cout << "Read '31.04.2023' -> " << d << " (stream good, date invalid)\n";
	}

	// INVALID string
	iss.clear();
	iss.str("INVALID");
	if (iss >> d)
	{
		std::cout << "Read 'INVALID' -> " << d << " (stream good, date invalid)\n";
	}

	// Malformed format
	iss.clear();
	iss.str("01/01/2020");
	if (!(iss >> d))
	{
		std::cout << "Read '01/01/2020' failed (stream failbit set)\n";
	}
}

void demoInvalidBehavior()
{
	printTestHeader("Operations on invalid dates");
	CDate invalid(32, Month::JANUARY, 1970);
	std::cout << "Invalid date: " << invalid << "\n";

	invalid += 5;
	std::cout << "invalid += 5 -> " << invalid << " (still invalid)\n";

	CDate d = invalid + 10;
	std::cout << "invalid + 10 = " << d << "\n";

	CDate d2 = invalid - 3;
	std::cout << "invalid - 3 = " << d2 << "\n";

	++invalid;
	std::cout << "++invalid -> " << invalid << "\n";
}

int main()
{
	std::cout << std::boolalpha;
	demoConstructors();
	demoArithmetic();
	demoComparisons();
	demoIncrementDecrement();
	demoIO();
	demoInvalidBehavior();

	std::cout << "\nAll demonstrations completed successfully.\n";
	return 0;
}
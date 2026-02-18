#pragma once

#include <array>
#include <iostream>

using Matrix3x3 = std::array<std::array<double, 3>, 3>;

enum class ReadResult
{
	Success,
	InvalidFormat, 
	InvalidValue 
};

ReadResult ReadMatrix(std::istream& input, Matrix3x3& matrix);

double Determinant(const Matrix3x3& matrix);

bool Invert(const Matrix3x3& matrix, Matrix3x3& result);

void PrintMatrix(std::ostream& output, const Matrix3x3& m);

void PrintHelp();
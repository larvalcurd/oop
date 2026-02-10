#pragma once
#include <iostream>

using Matrix3x3 = double[3][3];

// Возвращает:
// 0 — OK
// 1 — Invalid matrix format (не 3 строки или не 3 столбца)
// 2 — Invalid matrix (не число)
int ReadMatrix(std::istream& input, Matrix3x3& matrix);

// Детерминант 3×3
double Determinant(const Matrix3x3& matrix);

// Возвращает true, если обратимая.
// result = A^{-1}
bool Invert(const Matrix3x3& matrix, Matrix3x3& result);

// Печатает матрицу с fixed, precision=3, \t как разделитель
void PrintMatrix(std::ostream& output, const Matrix3x3& m);

// Печатает help по использованию программы
void PrintHelp();
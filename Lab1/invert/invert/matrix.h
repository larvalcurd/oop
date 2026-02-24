#pragma once

#include <array>
#include <iostream>
#include <optional>

constexpr std::size_t MATRIX_SIZE = 3;

using Matrix3x3 = std::array<std::array<double, MATRIX_SIZE>, MATRIX_SIZE>;

enum class ReadError
{
	None,
	InvalidFormat,
	InvalidValue
};

struct ReadMatrixResult
{
	Matrix3x3 matrix;
	ReadError error;
};

ReadMatrixResult ReadMatrix(std::istream& input);

double Determinant(const Matrix3x3& matrix);

Matrix3x3 ComputeAdjugate(const Matrix3x3& matrix);

std::optional<Matrix3x3> Invert(const Matrix3x3& matrix);

void PrintMatrix(std::ostream& output, const Matrix3x3& matrix);

void PrintHelp();

const char* GetReadErrorMessage(ReadError error);
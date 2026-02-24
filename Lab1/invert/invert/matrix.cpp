#include "matrix.h"
#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>

namespace
{

constexpr double EPSILON = 1e-9;

std::optional<double> ParseDouble(const std::string& token)
{
	if (token.empty())
	{
		return std::nullopt;
	}

	std::size_t idx = 0;
	double value;

	try
	{
		value = std::stod(token, &idx);
	}
	catch (...)
	{
		return std::nullopt;
	}

	if (idx != token.size())
	{
		return std::nullopt;
	}

	return value;
}

std::string TrimCarriageReturn(std::string line)
{
	if (!line.empty() && line.back() == '\r')
	{
		line.pop_back();
	}
	return line;
}

} // namespace

ReadMatrixResult ReadMatrix(std::istream& input)
{
	Matrix3x3 matrix{};
	std::string line;

	for (std::size_t row = 0; row < MATRIX_SIZE; ++row)
	{
		if (!std::getline(input, line))
		{
			return { {}, ReadError::InvalidFormat };
		}

		line = TrimCarriageReturn(line);
		std::istringstream ss(line);
		std::string token;
		std::size_t col = 0;

		while (std::getline(ss, token, '\t'))
		{
			if (col >= MATRIX_SIZE)
			{
				return { {}, ReadError::InvalidFormat };
			}

			auto value = ParseDouble(token);
			if (!value.has_value())
			{
				return { {}, ReadError::InvalidValue };
			}

			matrix[row][col] = value.value();
			++col;
		}

		if (col != MATRIX_SIZE)
		{
			return { {}, ReadError::InvalidFormat };
		}
	}

	return { matrix, ReadError::None };
}

double Determinant(const Matrix3x3& m)
{
	return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
		- m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
		+ m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
}

Matrix3x3 ComputeAdjugate(const Matrix3x3& m)
{
	Matrix3x3 adj{};

	adj[0][0] = m[1][1] * m[2][2] - m[1][2] * m[2][1];
	adj[0][1] = m[0][2] * m[2][1] - m[0][1] * m[2][2];
	adj[0][2] = m[0][1] * m[1][2] - m[0][2] * m[1][1];

	adj[1][0] = m[1][2] * m[2][0] - m[1][0] * m[2][2];
	adj[1][1] = m[0][0] * m[2][2] - m[0][2] * m[2][0];
	adj[1][2] = m[0][2] * m[1][0] - m[0][0] * m[1][2];

	adj[2][0] = m[1][0] * m[2][1] - m[1][1] * m[2][0];
	adj[2][1] = m[0][1] * m[2][0] - m[0][0] * m[2][1];
	adj[2][2] = m[0][0] * m[1][1] - m[0][1] * m[1][0];

	return adj;
}

std::optional<Matrix3x3> Invert(const Matrix3x3& matrix)
{
	double det = Determinant(matrix);

	if (std::abs(det) < EPSILON)
	{
		return std::nullopt;
	}

	Matrix3x3 adjugate = ComputeAdjugate(matrix);
	Matrix3x3 result{};
	double invDet = 1.0 / det;

	for (std::size_t i = 0; i < MATRIX_SIZE; ++i)
	{
		for (std::size_t j = 0; j < MATRIX_SIZE; ++j)
		{
			result[i][j] = adjugate[i][j] * invDet;
		}
	}

	return result;
}

void PrintMatrix(std::ostream& output, const Matrix3x3& m)
{
	output << std::fixed << std::setprecision(3);

	for (std::size_t i = 0; i < MATRIX_SIZE; ++i)
	{
		for (std::size_t j = 0; j < MATRIX_SIZE; ++j)
		{
			if (j > 0)
			{
				output << '\t';
			}
			output << m[i][j];
		}
		output << '\n';
	}
}

void PrintHelp()
{
	std::cout << "Usage:\n"
				 "	invert.exe			Read Matrix from stdin\n"
				 "	invert.exe <file>	Read Matrix from file\n"
				 "	invert.exe -h		Show help\n";
}

const char* GetReadErrorMessage(ReadError error)
{
	switch (error)
	{
	case ReadError::InvalidFormat:
		return "Invalid matrix format";
	case ReadError::InvalidValue:
		return "Invalid matrix";
	default:
		return "Unknown error";
	}
}
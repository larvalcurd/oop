#include "matrix.h"
#include <iomanip>
#include <string>
#include <sstream>

static bool ParseDouble(const std::string& token, double& value)
{
	std::size_t idx = 0;
	try {
		value = std::stod(token, &idx);
	} catch (const std::invalid_argument&) 
	{
		return false;
	}
	catch (const std::out_of_range&) 
	{
		return false;
	}
	return idx == token.size();
}

int ReadMatrix(std::istream& input, Matrix3x3& matrix)
{
	std::string line;
	for (int i = 0; i < 3; i++)
	{
		if (!std::getline(input, line))
			return 1;
		
		std::stringstream ss(line);
		std::string token;
		int col = 0;

		while (std::getline(ss, token, '\t'))
		{
			if (col >= 3)
				return 1;
			
			if (token.empty())
				return 2;

			double value;
			if (!ParseDouble(token, value))
				return 2;

			matrix[i][col] = value;
			col++;
		}

		if (col != 3)
			return 1;
	}
	return 0;
}

double Determinant(const Matrix3x3& m)
{
	double det =
		m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
		m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
		m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
	return det;
}

bool Invert(const Matrix3x3& matrix, Matrix3x3& result)
{
	double det = Determinant(matrix);
	if (det == 0)
	{
		return false; 
	}

	double invDet = 1.0 / det;
	result[0][0] = invDet * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]);
	result[0][1] = invDet * (matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2]);
	result[0][2] = invDet * (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]);
	
	result[1][0] = invDet * (matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2]);
	result[1][1] = invDet * (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]);
	result[1][2] = invDet * (matrix[0][2] * matrix[1][0] - matrix[0][0] * matrix[1][2]);
	
	result[2][0] = invDet * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
	result[2][1] = invDet * (matrix[0][1] * matrix[2][0] - matrix[0][0] * matrix[2][1]);
	result[2][2] = invDet * (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
	return true;
}

void PrintMatrix(std::ostream& output, const Matrix3x3& m)
{
	output << std::fixed << std::setprecision(3);
	for (int i = 0; i < 3; i++)
	{
		output << m[i][0] << "\t" << m[i][1] << "\t" << m[i][2] << "\n";
	}
}

void PrintHelp()
{
	std::cout <<
		"Usage:\n"
		"	invert.exe			Read Matrix from stdin\n"
		"	invert.exe <file>	Read Matrix from file\n"
		"	invert.exe -h		Show help\n";
}
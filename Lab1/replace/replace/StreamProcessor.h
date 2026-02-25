#pragma once
#include <iostream>
#include <string>

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString);

bool CopyFileWithReplacement(const std::string& inputFileName,
	const std::string& outputFileName,
	const std::string& searchString, const std::string& replacementString);
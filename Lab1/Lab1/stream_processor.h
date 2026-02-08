#pragma once

#include <string>
#include <iostream>

void processStream(std::istream& in,
	std::ostream& out,
	const std::string& search,
	const std::string& replace);
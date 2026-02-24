#pragma once
#include <string>
#include <string_view>

std::string toLower(const std::string& str);
std::string trim(const std::string& str);
bool hasCyrillic(std::string_view str);
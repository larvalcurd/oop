#pragma once
#include <string>
#include <string_view>

std::string toLower(std::string_view str);
std::string trim(std::string_view str);
bool hasCyrillic(std::string_view str);
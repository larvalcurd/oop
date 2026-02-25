#pragma once

#include <optional>
#include <string>

std::optional<char> TryDecodeEntity(const std::string& entity);
std::string HtmlDecode(const std::string& html);
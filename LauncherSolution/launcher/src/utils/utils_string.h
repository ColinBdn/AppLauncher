#pragma once

#include <string>
#include <vector>

std::string toLower(const std::string& str);
std::string toUpper(const std::string& str);
bool contains(const std::string& text, const std::string& search);
bool containsOr(const std::string& text, const std::vector<std::string>& searchList);
bool containsAnd(const std::string& text, const std::vector<std::string>& searchList);
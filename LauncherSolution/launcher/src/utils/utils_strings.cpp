#include "utils_string.h"

#include <algorithm>



std::string toLower(const std::string& str)
{
	std::string out = str;
	std::transform(out.begin(), out.end(), out.begin(), [](unsigned char c) { return std::tolower(c); });
	return out;
}

std::string toUpper(const std::string& str)
{
	std::string out = str;
	std::transform(out.begin(), out.end(), out.begin(), [](unsigned char c) { return std::toupper(c); });
	return out;
}


bool contains(const std::string& text, const std::string& search)
{
	return toLower(text).find(toLower(search)) != std::string::npos;
}

bool containsOr(const std::string& text, const std::vector<std::string>& searchList)
{
	for (const auto& search : searchList)
	{
		if (contains(text, search)) return true;
	}
	return false;
}

bool containsAnd(const std::string& text, const std::vector<std::string>& searchList)
{
	for (const auto& search : searchList)
	{
		if (!contains(text, search)) return false;
	}
	return true;
}
#pragma once

#include <string>
#include <map>
#include <vector>

std::map<std::string, std::string> parseCommandLine(int argc, char* argv[]);
std::vector<std::string> getKeyValues(std::string const& commandLine);
std::pair<std::string, std::string> getPair(std::string const& keyValue);

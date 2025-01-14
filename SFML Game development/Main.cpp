	// Includes librairie standard
#include <utility>
#include <regex>
#include <vector>
#include <filesystem>
#include <iostream>

	// Includes SFML
#include <SFML/System/Exception.hpp>

	// Includes personnalisés
#include "Main.h"
#include "Application.h"

#include "TileSet.h"

int main(int argc, char* argv[])
{
	std::map<std::string, std::string> commandLine{ parseCommandLine(argc, argv) };
	try
	{
		Maps::Tileset tileset{ std::filesystem::path(commandLine["path"]) / "Ressources/Tiled/Tilesets/Title.tsx" };
		Application application{ std::filesystem::path(commandLine["path"])};
		application.run();
	}
	catch(std::exception& e)
	{
		std::cerr << e.what();
	}
	return EXIT_SUCCESS;
}

std::map<std::string, std::string> parseCommandLine(int argc, char* argv[])
{
	std::map<std::string, std::string> keysValues;
	if (argc == 2)
	{
		std::vector<std::string> pairsKeyValue{ getKeyValues(std::string(argv[1])) };
		for (auto const& pairKeyValue : pairsKeyValue)
		{
			std::pair<std::string, std::string> pair{ getPair(pairKeyValue) };
			keysValues.insert(pair);
		}
	}
	return keysValues;
}

std::vector<std::string> getKeyValues(std::string const& commandLine)
{
	std::vector<std::string> pairsKeyValue;
	std::regex pattern{ "([^;]+)" };
	std::smatch matchs;
	std::regex_match(commandLine, matchs, pattern);
	for(std::size_t i=1; i<matchs.size(); ++i)
		pairsKeyValue.push_back(matchs[i].str());
	return pairsKeyValue;
}

std::pair<std::string, std::string> getPair(std::string const& keyValue)
{
	std::regex pattern{ "([^=]+)=([^=]*)" };
	std::smatch matchs;
	if (std::regex_match(keyValue, matchs, pattern))
		return std::make_pair<std::string, std::string>(matchs[1], matchs[2]);
	else
		return std::pair<std::string, std::string>();
}

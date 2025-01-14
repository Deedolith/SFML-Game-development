#pragma once

#include <memory>
#include <filesystem>

#include <SFML/Graphics/Font.hpp>

#include "Map.h"

template <class Ressource>
class RessourceLoader
{
public:
	static std::unique_ptr<Ressource> load(std::filesystem::path const& filename);
	template <class Parameter>
	static std::unique_ptr<Ressource> load(std::filesystem::path const& filename, Parameter const& secondParameter);
};

#include "RessourceLoader.inl"

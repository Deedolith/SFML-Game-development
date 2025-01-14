#pragma once

#include <filesystem>
#include <vector>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace Maps
{
	class Tileset
	{
	private:
		sf::Texture mTexture;
		std::vector<sf::IntRect> mTilesRect;
	private:
		void buildSet(std::filesystem::path const& path);
	public:
		Tileset() = delete;
		Tileset(std::filesystem::path const& path);
		sf::IntRect const getTextureRect(unsigned tileID) const;
		sf::Texture const& getTexture() const;
		unsigned getTileCount() const;
	};
}

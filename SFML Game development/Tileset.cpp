#include <pugixml.hpp>

#include "TileSet.h"

namespace Maps
{
	void Tileset::buildSet(std::filesystem::path const& path)
	{
		pugi::xml_document document;
		document.load_file(path.c_str());
		auto node{ document.select_node("//tileset").node() };
		int tileWidth{ node.attribute("tilewidth").as_int() };
		int tileHeight{ node.attribute("tileheight").as_int() };
		int tilesCount{ node.attribute("tilecount").as_int() };
		int columns{ node.attribute("columns").as_int() };

		node = document.select_node("//image").node();
		std::filesystem::path imagePath{ node.attribute("source").as_string() };
		if (!mTexture.loadFromFile(path.parent_path() / imagePath))
			throw std::runtime_error{ "Tiled::Tileset::Tileset - Failed to load " + imagePath.string() };
		int rows{ static_cast<int>(mTexture.getSize().y) / tileHeight };
		mTilesRect.push_back({ });
		for (int y{ 0 }; y < rows; ++y)
		{
			for (int x{ 0 }; x < columns; ++x)
				mTilesRect.push_back({ { x * tileWidth, y * tileHeight }, { tileWidth, tileHeight } });
		}
	}

	Tileset::Tileset(std::filesystem::path const& path) :
		mTilesRect{},
		mTexture{}
	{
		buildSet(path);
	}

	sf::IntRect const Tileset::getTextureRect(unsigned tileID) const
	{
		return mTilesRect[tileID];
	}

	sf::Texture& Tileset::getTexture()
	{
		return mTexture;
	}

	sf::Texture const& Tileset::getTexture() const
	{
		return mTexture;
	}

	unsigned Tileset::getTileCount() const
	{
		return static_cast<unsigned>(mTilesRect.size());
	}
}

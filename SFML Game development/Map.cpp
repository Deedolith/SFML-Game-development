#include <cassert>
#include <iterator>
#include <utility>

#include <SFML/Graphics/View.hpp>

#include <pugixml.hpp>

#include "Map.h"
#include "SpriteNode.h"

namespace Maps
{
	Map::Map(std::filesystem::path const& path) :
		mTilesets{},
		mPath{ path },
		mLayers{},
		mProperties{}
	{
		pugi::xml_document document;
		loadDocument(document);
		getTilesets(document);
		buildMap(document);
	}

	Map::Layer& Map::getLayer(size_t index)
	{
		return mLayers[index];
	}

	size_t Map::getLayerCount() const
	{
		return mLayers.size();
	}

	Property Map::getProperty(std::string const& property) const
	{
		auto found{ mProperties.find(property) };
		if (found == mProperties.end())
			assert(found != mProperties.end() && "The given property do not exist.");
		return Maps::Property{ found->second };
	}

	void Map::loadDocument(pugi::xml_document& document)
	{
		auto result{ document.load_file(mPath.c_str()) };
		if (!result)
			throw std::runtime_error{ "Tiled::Map::Map - Failed to load " + mPath.string() };
	}

	void Map::getTilesets(pugi::xml_document const& document)
	{
		auto nodes{ document.select_nodes("//tileset") };
		for (auto const& node : nodes)
		{
			std::filesystem::path tilesetPath{ node.node().attribute("source").as_string() };
			mTilesets.push_back({ mPath.parent_path() / tilesetPath });
		}
	}

	void Map::buildMap(pugi::xml_document const& document)
	{
		buildLayers(document);
		buildProperties(document);
	}

	void Map::buildLayers(pugi::xml_document const& document)
	{
		auto node{ document.select_node("//map").node() };
		unsigned tileWidth{ node.attribute("tilewidth").as_uint() };
		unsigned tileHeight{ node.attribute("tileheight").as_uint() };

		auto layers{ document.select_nodes("//layer") };
		for (auto const& node : layers)
		{
			// insert a new layer
			Layer layer{ node.node(), tileWidth, tileHeight, mTilesets };
			mLayers.push_back(layer);
		}
	}

	void Map::buildProperties(pugi::xml_document const& document)
	{
		auto node{ document.select_node("//properties").node() };
		for (auto& child : node.children())
		{
			std::string name{ child.attribute("name").as_string() };
			std::string value{ child.attribute("value").as_string() };
			auto pair{ std::make_pair(name, value) };
			mProperties.insert(pair);
		}
	}

	void Map::Layer::buildLayer(pugi::xml_node const& node, unsigned tileWidth, unsigned tileHeight, std::vector<Tileset> const& tilesets)
	{
		unsigned width{ node.attribute("width").as_uint() };
		unsigned height{ node.attribute("height").as_uint() };
		// get tiles IDs
		std::string data{ node.select_node(".//data").node().text().as_string() };
		std::vector<unsigned> tilesID{ splitString(data, ',') };

		// Fill the layer with tiles
		std::vector<sf::Sprite> tiles;
		for (unsigned x{ 0 }; x < width; ++x)
		{
			for (unsigned y{ 0 }; y < height; ++y)
			{
				unsigned index{ y * width + x };
				assert(index < tilesID.size());
				unsigned ID{ tilesID[index] };
				if (ID > 0)
				{
					for (auto& tileset : tilesets)
					{
						// if ID belong to the current tileset
						if (ID < tileset.getTileCount())
						{
							// create a new tile
							sf::IntRect textureRect{ tileset.getTextureRect(ID) };
							sf::Sprite tile{ tileset.getTexture(), textureRect };
							tile.setPosition({ static_cast<float>(x * tileWidth), static_cast<float>(y * tileHeight) });
							mTiles.push_back(tile);
							break;
						}
						else
							ID = ID - tileset.getTileCount() + 1;
					}
				}
			}
		}
	}

	void Map::Layer::buildProperties(pugi::xml_node const& node)
	{
		auto const& propertiesNode{ node.select_node(".//properties").node() };
		for (auto const& child : propertiesNode.children())
		{
			std::string name{ child.attribute("name").as_string() };
			std::string value{ child.attribute("value").as_string() };
			if (value.empty())
				value = child.text().as_string();
			auto pair{ std::make_pair(name, value) };
			mProperties.insert(pair);
		}
	}

	Map::Layer::Layer(pugi::xml_node const& node, unsigned tileWidth, unsigned tileHeight, std::vector<Tileset> const& tilesets) :
		mTiles{},
		mVisible{ node.attribute("visible").as_bool(true) },
		mProperties{}
	{
		buildLayer(node, tileWidth, tileHeight, tilesets);
		buildProperties(node);
	}

	void Map::Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (mVisible)
		{
			sf::View view{ target.getView() };
			sf::Vector2f viewSize{ view.getSize() };
			sf::Vector2f viewCenter{ view.getCenter() };
			sf::FloatRect viewRect{ viewCenter - viewSize / 2.f, viewSize };

			sf::FloatRect currentViewRect(viewCenter - viewSize / 2.f, viewSize);
			for (auto const& tile : mTiles)
			{
				if (viewRect.findIntersection(tile.getGlobalBounds()))
					target.draw(tile, states);
			}
		}
	}

	bool Map::Layer::getVisible() const
	{
		return mVisible;
	}

	void Map::Layer::setVisible(bool visible)
	{
		mVisible = visible;
	}

	Property Map::Layer::getProperty(std::string const& property) const
	{
		auto found{ mProperties.find(property) };
		if (found == mProperties.end())
			assert(found != mProperties.end() && "The given property do not exist.");
		return Property{ found->second };
	}
}

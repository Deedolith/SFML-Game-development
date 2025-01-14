#pragma once

#include <vector>
#include <map>
#include <filesystem>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <pugixml.hpp>

#include "Tileset.h"
#include "Property.h"
#include "Utilities.h"

namespace Maps
{
	class Map
	{
	public:
		class Layer :
			public sf::Drawable,
			public sf::Transformable
		{
		private:
			std::vector<sf::Sprite> mTiles;
			bool mVisible;
			std::map<std::string, std::string> mProperties;
		private:
			void buildLayer(pugi::xml_node const& node, unsigned tileWidth, unsigned tileHeight, std::vector<Tileset> const& tilesets);
			void buildProperties(pugi::xml_node const& node);
			void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
		public:
			Layer(pugi::xml_node const& node, unsigned tileWidth, unsigned tileHeight, std::vector<Tileset> const& tilesets);
			bool getVisible() const;
			void setVisible(bool visible);
			Maps::Property getProperty(std::string const& property) const;
		};
	private:
		std::filesystem::path mPath;
		std::vector<Tileset> mTilesets;
		std::vector<Layer> mLayers;
		std::map<std::string, std::string> mProperties;
	private:
		void loadDocument(pugi::xml_document& document);
		void getTilesets(pugi::xml_document const& document);
		void buildMap(pugi::xml_document const& document);
		void buildLayers(pugi::xml_document const& document);
		void buildProperties(pugi::xml_document const& document);
	public:
		Map(std::filesystem::path const& path);
		Layer& getLayer(size_t index);
		size_t getLayerCount() const;
		Maps::Property getProperty(std::string const& property) const;
	};
}

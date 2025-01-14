#pragma once

#include <filesystem>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/String.hpp>

#include "BitmapGlyph.h"

namespace Fonts
{
	namespace Bitmaps
	{
		class Font
		{
		private:
			sf::Texture mTexture;
			sf::Vector2i mGlyphSize;
			sf::String mCharacters;
		public:
			Font();
			Font(std::filesystem::path const& path, sf::Vector2i glyphSize = sf::Vector2i{ 8, 8 }, sf::String const& characters = "\"#$%&'()*+,-./0123456789:;<=>?ABCDEFGHIJKLMNOPQRSTUVWXYZ!_ ");
			bool loadFromFile(std::filesystem::path const& path);
			sf::Texture& getTexture();
			sf::Texture const& getTexture() const;
			sf::Vector2i getGlyphSize() const;
			void setGlyphSize(sf::Vector2i glyphSize);
			sf::String const getCharacters() const;
			Glyph getGlyph(char32_t character) const;
			bool hasGlyph(char32_t character) const;
		};
	}
}

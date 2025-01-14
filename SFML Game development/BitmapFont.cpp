#include "BitmapFont.h"

namespace Fonts
{
	namespace Bitmaps
	{
		Font::Font() :
			mTexture{},
			mGlyphSize{ 8u, 8u },
			mCharacters{ "\"#$%&'()*+,-./0123456789:;<=>?ABCDEFGHIJKLMNOPQRSTUVWXYZ!_ " }
		{
		}

		Font::Font(std::filesystem::path const& path, sf::Vector2i glyphSize, sf::String const& characters) :
			mTexture{ path },
			mGlyphSize{ glyphSize },
			mCharacters{ characters }
		{
		}

		bool Font::loadFromFile(std::filesystem::path const& path)
		{
			return mTexture.loadFromFile(path);
		}

		sf::Texture& Font::getTexture()
		{
			return mTexture;
		}

		sf::Texture const& Font::getTexture() const
		{
			return mTexture;
		}

		sf::Vector2i Font::getGlyphSize() const
		{
			return mGlyphSize;
		}

		void Font::setGlyphSize(sf::Vector2i glyphSize)
		{
			mGlyphSize = glyphSize;
		}

		sf::String const Font::getCharacters() const
		{
			return mCharacters;
		}

		Glyph Font::getGlyph(char32_t character) const
		{
			size_t index{ mCharacters.find(character) };
			if (index == sf::String::InvalidPos)
			{
				return Glyph{ sf::IntRect{ sf::Vector2i{ 0, 0 }, sf::Vector2i{ 0, 0 }} };
			}
			sf::IntRect rect{ sf::Vector2i{ static_cast<int>(index) * mGlyphSize.x, 0 }, mGlyphSize };
			return Glyph{ rect };
		}

		bool Font::hasGlyph(char32_t character) const
		{
			size_t index{ mCharacters.find(character) };
			return index != sf::String::InvalidPos;
		}
	}
}


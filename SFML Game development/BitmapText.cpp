#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "BitmapGlyph.h"
#include "BitmapText.h"

namespace Fonts
{
	namespace Bitmaps
	{
		void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			states.transform *= getTransform();
			for (auto const& sprite : mSprites)
				target.draw(sprite, states);
		}

		void Text::buildSprites()
		{
			mSprites.clear();
			sf::Texture& texture{ mFont.getTexture() };
			float x{ 0.f };
			for (auto character : mText)
			{
				Glyph glyph{ mFont.getGlyph(character) };
				sf::Sprite sprite{ texture, glyph.getTextureRect() };
				sprite.setOrigin(getOrigin() - sf::Vector2f{ x, 0.f });
				x += mFont.getGlyphSize().x;
				mSprites.push_back(sprite);
			}
		}

		Text::Text(Font const& font, sf::String const& text) :
			mFont{ font },
			mText{ text },
			mSprites{}
		{
			buildSprites();
		}

		sf::FloatRect Text::getLocalBounds() const
		{
			sf::Vector2f size{ static_cast<float>(mFont.getGlyphSize().x * mText.getSize()), static_cast<float>(mFont.getGlyphSize().y) };
			sf::Vector2f position{ getOrigin() - size / 2.f };
			return sf::FloatRect{ static_cast<sf::Vector2f>(position), static_cast<sf::Vector2f>(size) };
		}
		void Text::setText(sf::String const& text)
		{
			mText = text;
			buildSprites();
		}
	}
}

#pragma once

#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/String.hpp>

#include "BitmapFont.h"

namespace Fonts
{
	namespace Bitmaps
	{
		class Text :
			public sf::Drawable,
			public sf::Transformable
		{
		private:
			Font mFont;
			sf::String mText;
			std::vector<sf::Sprite> mSprites;
		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
			void buildSprites();
		public:
			Text(Font const& font, sf::String const& text = sf::String{});
			Text(Text const&) = delete;
			Text& operator=(Text const&) = delete;
			sf::FloatRect getLocalBounds() const;
			void setText(sf::String const& text);
		};
	}
}

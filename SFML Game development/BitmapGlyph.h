#pragma once

#include <SFML/Graphics/Rect.hpp>

namespace Fonts
{
	namespace Bitmaps
	{
		class Glyph
		{
		private:
			sf::IntRect mTextureRect;
		public:
			Glyph(sf::IntRect textureRect);
			sf::IntRect getTextureRect() const;
		};
	}
}

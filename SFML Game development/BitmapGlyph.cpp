#include "BitmapGlyph.h"

namespace Fonts
{
	namespace Bitmaps
	{
		Glyph::Glyph(sf::IntRect textureRect) :
			mTextureRect{ textureRect }
		{
		}

		sf::IntRect Glyph::getTextureRect() const
		{
			return mTextureRect;
		}
	}
}

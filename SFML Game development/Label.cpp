#include "Label.h"

namespace GUI
{
	void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mText, states);
	}

	Label::Label(std::string const& text, Fonts::Bitmaps::ID color, Fonts::Bitmaps::FontsHolder& fonts) :
		mText{ fonts.get(color), text }
	{
	}

	bool Label::isSelectable() const
	{
		return false;
	}

	void Label::setText(std::string const& text)
	{
		mText.setText(text);
	}

	sf::FloatRect Label::getLocalBounds() const
	{
		return mText.getLocalBounds();
	}
}
#include "Label.h"

void GUI::Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mText, states);
}

GUI::Label::Label(std::string const& text, Fonts::Bitmaps::ID color, Fonts::Bitmaps::FontsHolder& fonts) :
	mText{ fonts.get(color), text }
{
}

bool GUI::Label::isSelectable() const
{
	return false;
}

void GUI::Label::handleEvent(std::optional<sf::Event> const& event)
{
}

#include <SFML/Graphics/Rect.hpp>

#include "Utilities.h"

void centerOrigin(sf::Sprite& sprite)
{
	sf::FloatRect bounds{ sprite.getLocalBounds() };
	sprite.setOrigin(bounds.size / 2.f);
}

void centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds{ text.getLocalBounds() };
	text.setOrigin(bounds.size / 2.f);
}

void centerOrigin(Fonts::Bitmaps::Text& text)
{
	sf::FloatRect bounds{ text.getLocalBounds() };
	text.setOrigin(bounds.size / 2.f);
}

std::vector<unsigned> splitString(const std::string& s, char delimiter)
{
	std::vector<unsigned> tokens;
	std::stringstream ss{ s };
	std::string token;
	while (std::getline(ss, token, delimiter))
	{
		tokens.push_back(std::stoul(token));
	}
	return tokens;
}


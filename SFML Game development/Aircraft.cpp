#include <cassert>

#include <SFML/Graphics/Rect.hpp>

#include "Aircraft.h"
#include "Category.h"
#include "Utilities.h"

Textures::ID toTextureID(Aircraft::Type type)
{
	switch (type)
	{
	case Aircraft::Type::Player1:
		return Textures::ID::Player1;
		break;
	case Aircraft::Type::Player2:
		return Textures::ID::Player2;
		break;
	default:
		assert(false && "Invalid given type");
		return Textures::ID::Player1;
		break;
	}
}

Aircraft::Aircraft(Type type, Textures::TexturesHolder const& textures) :
	mType{ type },
	mSprite{ textures.get(toTextureID(type)) }
{
	centerOrigin(mSprite);
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

unsigned Aircraft::getCategory() const
{
	switch (mType)
	{
	case Aircraft::Type::Player1:
		return Category::Type::Player;
		break;
	case Aircraft::Type::Player2:
		return Category::Type::Player;
		break;
	default:
		return Category::Type::Ennemy;
		break;
	}
}

void Aircraft::accelerate(sf::Vector2f velocity)
{
	setVelocity(getVelocity() + velocity);
}

sf::Vector2f Aircraft::getSize() const
{
	return mSprite.getGlobalBounds().size;
}

#include "Entity.h"

void Entity::updateCurrent(sf::Time dt)
{
	move(mVelocity * dt.asSeconds());
}

void Entity::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
	setVelocity({ vx, vy });
}

sf::Vector2f Entity::getVelocity() const
{
	return mVelocity;
}

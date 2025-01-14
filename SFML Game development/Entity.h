#pragma once

#include <SFML/System/Vector2.hpp>

#include "SceneNode.h"

class Entity :
	public SceneNode
{
private:
	sf::Vector2f mVelocity;
private:
	void updateCurrent(sf::Time dt) override;
public:
	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity() const;
};


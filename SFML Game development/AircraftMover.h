#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

#include "Aircraft.h"

class AircraftMover
{
private:
	sf::Vector2f mVelocity;
public:
	AircraftMover(float vx, float vy);
	AircraftMover(sf::Vector2f velocity);
	void operator()(Aircraft& aircraft, sf::Time dt) const;
};


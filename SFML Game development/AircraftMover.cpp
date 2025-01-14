#include "AircraftMover.h"

AircraftMover::AircraftMover(float vx, float vy) :
	mVelocity{ vx, vy }
{
}

AircraftMover::AircraftMover(sf::Vector2f velocity) :
	mVelocity{ velocity }
{
}

void AircraftMover::operator()(Aircraft& aircraft, sf::Time dt) const
{
	aircraft.accelerate(mVelocity);
}

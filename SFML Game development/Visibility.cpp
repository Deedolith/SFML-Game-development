#include "Visibility.h"

Visibility::Visibility(bool state, sf::Time duration):
	mState{ state },
	mDuration{ duration }
{
}

bool Visibility::getState() const
{
	return mState;
}

sf::Time Visibility::getDuration() const
{
	return mDuration;
}

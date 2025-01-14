#include "Visibility.h"

Visibility::Visibility(bool state, unsigned duration):
	mState{ state },
	mDuration{ duration }
{
}

bool Visibility::getState() const
{
	return mState;
}

std::chrono::milliseconds Visibility::getDuration() const
{
	return mDuration;
}

#pragma once

#include <chrono>

class Visibility
{
private:
	bool mState;
	std::chrono::milliseconds mDuration;
public:
	Visibility(bool state, unsigned duration);
	bool getState() const;
	std::chrono::milliseconds getDuration() const;
};


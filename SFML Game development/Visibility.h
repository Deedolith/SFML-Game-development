#pragma once

#include <SFML/System/Time.hpp>

class Visibility
{
private:
	bool mState;
	sf::Time mDuration;
public:
	Visibility(bool state, sf::Time duration);
	bool getState() const;
	sf::Time getDuration() const;
};


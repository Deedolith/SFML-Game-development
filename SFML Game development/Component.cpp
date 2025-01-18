#include "Component.h"

namespace GUI
{
	Component::Component() :
		mIsSelected{ false },
		mIsActive{ false }
	{
	}

	bool Component::isSelected() const
	{
		return mIsSelected;
	}

	void Component::select()
	{
		mIsSelected = true;
	}

	void Component::deselect()
	{
		mIsSelected = false;
	}

	bool GUI::Component::isActive() const
	{
		return mIsActive;
	}

	void Component::activate()
	{
		mIsActive = true;
	}

	void Component::deactivate()
	{
		mIsActive = false;
	}

	bool Component::handleEvent(std::optional<sf::Event> const& event)
	{
		return true;
	}

	void Component::update(sf::Time dt)
	{
	}
}
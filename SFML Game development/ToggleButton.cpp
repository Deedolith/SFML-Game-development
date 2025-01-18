#include "ToggleButton.h"


namespace GUI
{
	ToggleButton::ToggleButton(std::string const& text, Fonts::Bitmaps::FontsHolder const& fonts, Textures::TexturesHolder const& textures) :
		Button{ text, fonts, textures },
		mIsPressed{ false }
	{
	}
	void ToggleButton::activate()
	{
		Button::activate();
		mIsPressed = true;
	}
	void ToggleButton::deactivate()
	{
		Button::deactivate();
		mIsPressed = false;
	}
	bool ToggleButton::isActive() const
	{
		return isSelected() && mIsPressed;
	}
	bool ToggleButton::handleEvent(std::optional<sf::Event> const& event)
	{
		if (auto keyRelased{ event->getIf<sf::Event::KeyReleased>() })
		{
			if (keyRelased->code == sf::Keyboard::Key::Enter)
			{
				if (mIsPressed)
					deactivate();
				else
					activate();
			}
			Button::callback();
		}
		return !mIsPressed;
	}
}

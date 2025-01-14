#include <memory>

#include "Button.h"
#include "Utilities.h"

namespace GUI
{
	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		if (isSelected())
		{
			for (auto const& sprite : mBackFrame)
				target.draw(sprite, states);
		}
		target.draw(*mText, states);
		if (isSelected())
		{
			for (auto const& sprite : mFrontFrame)
				target.draw(sprite, states);
		}
	}

	Button::Button(Fonts::Bitmaps::FontsHolder const& fonts, Textures::TexturesHolder const& textures, sf::String const& text) :
		Component{},
		mBackFrame{},
		mFrontFrame{},
		mNormalText{ fonts.get(Fonts::Bitmaps::ID::White), text },
		mPressedText{ fonts.get(Fonts::Bitmaps::ID::Red), text },
		mSelectedText{ fonts.get(Fonts::Bitmaps::ID::Cyan), text },
		mIsToggle{ false },
		mText{ &mNormalText },
		mCallback{}
	{
		sf::Vector2f const buttonCenter{ getLocalBounds().size / 2.f };
		sf::Vector2f textSize{ mNormalText.getLocalBounds().size };
		mNormalText.setOrigin(buttonCenter - textSize);
		mPressedText.setOrigin(mNormalText.getOrigin());
		mSelectedText.setOrigin(mNormalText.getOrigin());

			// Top left
		sf::IntRect textureRect{ {0, 0}, {24, 24} };
		sf::Sprite topLeftsprite{ textures.get(Textures::ID::GUIButtonFrontFrame), textureRect };
		topLeftsprite.setOrigin(getOrigin() + buttonCenter);
		mFrontFrame.push_back(topLeftsprite);

			// Top right
		textureRect.position = { 24, 0 };
		sf::Sprite topRightSprite{ textures.get(Textures::ID::GUIButtonFrontFrame), textureRect };
		topRightSprite.setOrigin(topLeftsprite.getOrigin() + sf::Vector2f{ -80.f, 0.f });
		mFrontFrame.push_back(topRightSprite);

			// Bottom left
		textureRect.position = { 0, 24 };
		sf::Sprite bottomLeftSprite{ textures.get(Textures::ID::GUIButtonFrontFrame), textureRect };
		bottomLeftSprite.setOrigin(topLeftsprite.getOrigin() + sf::Vector2f{ 0.f, -24.f });
		mFrontFrame.push_back(bottomLeftSprite);

			// Bottom right
		textureRect.position = { 24, 24 };
		sf::Sprite bottomRightSprite{ textures.get(Textures::ID::GUIButtonFrontFrame), textureRect };
		bottomRightSprite.setOrigin(topLeftsprite.getOrigin() + sf::Vector2f{ -80.f, -24.f });
		mFrontFrame.push_back(bottomRightSprite);
	}

	bool Button::isSelectable() const
	{
		return true;
	}
	
	void Button::activate()
	{
		Component::activate();
		if (mIsToggle)
			mText = &mPressedText;
		if (mCallback)
			mCallback();
		if (!mIsToggle)
			deactivate();
	}

	void Button::deactivate()
	{
		Component::deactivate();
		if (mIsToggle)
		{
			if (isSelected())
				mText = &mSelectedText;
			else
				mText = &mNormalText;
		}

	}

	void Button::select()
	{
		Component::select();
		mText = &mSelectedText;
	}

	void Button::deselect()
	{

		Component::deselect();
		mText = &mNormalText;
	}

	void Button::handleEvent(std::optional<sf::Event> const& event)
	{
	}

	void Button::setToggle(bool toggleState)
	{
		mIsToggle = toggleState;
	}

	void Button::setCallback(Callback callback)
	{
		mCallback = std::move(callback);
	}
	sf::FloatRect Button::getLocalBounds() const
	{
		return sf::FloatRect{ {0.f, 0.f},  { 112.f, 48.f } };
	}
}

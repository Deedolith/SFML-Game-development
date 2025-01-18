#include <memory>
#include <cassert>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Button.h"
#include "Utilities.h"

namespace GUI
{
	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		if (isSelected())
		{
			for (auto const& sprite : mBackFrameSprites)
				target.draw(sprite, states);
			for (auto const& sprite : mFrontFrameSprites)
				target.draw(sprite, states);
		}
		target.draw(*mText, states);
	}

	void Button::callback()
	{
		if(mCallback)
			mCallback();
	}

	void Button::buildText()
	{
		sf::Vector2f buttonCenter{ getLocalBounds().size / 2.f };
		sf::Vector2f textCenter{ mNormalText.getLocalBounds().size / 2.f };
		mNormalText.setOrigin(-buttonCenter + textCenter);
		mPressedText.setOrigin(mNormalText.getOrigin());
		mSelectedText.setOrigin(mNormalText.getOrigin());
	}

	void Button::buildFrontFrame(Textures::TexturesHolder const& textures)
	{
		// Top left
		sf::IntRect textureRect{ {0, 0}, {24, 24} };
		sf::Sprite topLeftSprite{ textures.get(Textures::ID::GUIButtonFrontFrame), textureRect };
		mFrontFrameSprites.push_back(topLeftSprite);

		// Top right
		textureRect.position = { 24, 0 };
		sf::Sprite topRightSprite{ textures.get(Textures::ID::GUIButtonFrontFrame), textureRect };
		topRightSprite.setOrigin(topLeftSprite.getOrigin() + sf::Vector2f{ -88.f, 0.f });
		mFrontFrameSprites.push_back(topRightSprite);

		// Bottom left
		textureRect.position = { 0, 24 };
		sf::Sprite bottomLeftSprite{ textures.get(Textures::ID::GUIButtonFrontFrame), textureRect };
		bottomLeftSprite.setOrigin(topLeftSprite.getOrigin() + sf::Vector2f{ 0.f, -24.f });
		mFrontFrameSprites.push_back(bottomLeftSprite);

		// Bottom right
		textureRect.position = { 24, 24 };
		sf::Sprite bottomRightSprite{ textures.get(Textures::ID::GUIButtonFrontFrame), textureRect };
		bottomRightSprite.setOrigin(topLeftSprite.getOrigin() + sf::Vector2f{ -88.f, -24.f });
		mFrontFrameSprites.push_back(bottomRightSprite);

		for (auto const& sprite : mFrontFrameSprites)
			mFrontFrameRects.push_back(sprite.getTextureRect());
	}

	void Button::buildBackFrame(Textures::TexturesHolder const& textures)
	{
		sf::IntRect textureRect{ {8, 0}, {8, 8} };
		sf::Sprite topSprite{ textures.get(Textures::ID::GUIButtonBackFrame), textureRect };
		topSprite.setOrigin(getOrigin() + sf::Vector2f{ -8.f, -8.f });
		for (size_t i{ 0u }; i < 10u; ++i)
		{
			topSprite.setOrigin(topSprite.getOrigin() + sf::Vector2f{ -8.f, 0.f });
			mBackFrameSprites.push_back(topSprite);
		}

			// Right
		textureRect.position = { 24, 0 };
		sf::Sprite rightSprite{ textures.get(Textures::ID::GUIButtonBackFrame), textureRect };
		rightSprite.setOrigin(getOrigin() + sf::Vector2f{ -96.f, 0.f });
		for (size_t i{ 0u }; i < 4; ++i)
		{
			rightSprite.setOrigin(rightSprite.getOrigin() + sf::Vector2f{ 0.f, -8.f });
			mBackFrameSprites.push_back(rightSprite);
		}

			// Bottom
		textureRect.position = { 16, 0 };
		sf::Sprite bottomSprite{ textures.get(Textures::ID::GUIButtonBackFrame), textureRect };
		bottomSprite.setOrigin(getOrigin() + sf::Vector2f{ -8.f, -32.f });
		for (size_t i{ 0u }; i < 10; ++i)
		{
			bottomSprite.setOrigin(bottomSprite.getOrigin() + sf::Vector2f{ -8.f, 0.f });
			mBackFrameSprites.push_back(bottomSprite);
		}

			// Left
		textureRect.position = { 0, 0 };
		sf::Sprite leftSprite{ textures.get(Textures::ID::GUIButtonBackFrame), textureRect };
		leftSprite.setOrigin(getOrigin() + sf::Vector2f{ -8.f, 0.f });
		for (size_t i{ 0u }; i < 4; ++i)
		{
			leftSprite.setOrigin(leftSprite.getOrigin() + sf::Vector2f{ 0.f, -8.f });
			mBackFrameSprites.push_back(leftSprite);
		}

		for (auto const& sprite : mBackFrameSprites)
			mBackFrameRects.push_back(sprite.getTextureRect());
	}

	void Button::updateBackFrame()
	{
		for (size_t i{ 0u }; i < mBackFrameSprites.size(); ++i)
		{
			sf::IntRect textureRect{ mBackFrameSprites[i].getTextureRect() };
			textureRect.position.y = mBackFrameRects[i].position.y + 8 * static_cast<int>(mFrameIndex);
			mBackFrameSprites[i].setTextureRect(textureRect);
		}
	}

	void Button::updateFrontFrame()
	{
		for (size_t i{ 0u }; i<mFrontFrameSprites.size(); ++i)
		{
			sf::IntRect textureRect{ mFrontFrameSprites[i].getTextureRect()};
			textureRect.position.y = mFrontFrameRects[i].position.y + 48 * static_cast<int>(mFrameIndex);
			mFrontFrameSprites[i].setTextureRect(textureRect);
		}
	}

	Button::Button(std::string const& text, Fonts::Bitmaps::FontsHolder const& fonts, Textures::TexturesHolder const& textures) :
		Component{},
		mBackFrameSprites{},
		mBackFrameRects{},
		mFrontFrameSprites{},
		mFrontFrameRects{},
		mNormalText{ fonts.get(Fonts::Bitmaps::ID::White), text },
		mPressedText{ fonts.get(Fonts::Bitmaps::ID::Red), text },
		mSelectedText{ fonts.get(Fonts::Bitmaps::ID::Cyan), text },
		mText{ &mNormalText },
		mCallback{},
		mElapsedTime{ sf::Time::Zero },
		mFrameIndex{ 0u },
		mTimeForUpdate{ sf::seconds(3.f / 60.f) }
	{
		assert((text.size() <= 10) && "The given text is too long.");
		buildBackFrame(textures);
		buildText();
		buildFrontFrame(textures);
	}

	bool Button::isSelectable() const
	{
		return true;
	}
	
	void Button::activate()
	{
		Component::activate();
			mText = &mPressedText;
	}

	void Button::deactivate()
	{
		Component::deactivate();
		mText = &mSelectedText;
		callback();
	}

	bool Button::isActive() const
	{
		return false;
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

	bool Button::handleEvent(std::optional<sf::Event> const& event)
	{
		if (auto keyPressed{ event->getIf<sf::Event::KeyPressed>() })
		{
			if (keyPressed->code == sf::Keyboard::Key::Enter)
				activate();
		}
		else if (auto keyReleased{ event->getIf<sf::Event::KeyReleased>() })
		{
				if (keyReleased->code == sf::Keyboard::Key::Enter)
					deactivate();
		}
		return true;
	}

	void Button::setCallback(Callback callback)
	{
		mCallback = std::move(callback);
	}
	sf::FloatRect Button::getLocalBounds() const
	{
		return sf::FloatRect{ {0.f, 0.f},  { 112.f, 48.f } };
	}
	void Button::update(sf::Time dt)
	{
		mElapsedTime += dt;
		if (mTimeForUpdate < mElapsedTime)
		{
			mElapsedTime = sf::Time::Zero;
			mFrameIndex = (mFrameIndex + 1) % 6;
			updateBackFrame();
			updateFrontFrame();
		}
	}
}

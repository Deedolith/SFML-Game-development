#include <cassert>

#include <SFML/Graphics/RenderWindow.hpp>

#include "TitleState.h"
#include "Textures.h"
#include "Fonts.h"
#include "SpriteNode.h"
#include "Utilities.h"

namespace States
{
	TitleState::TitleState(StateStack& stack, State::Context context) :
		State{ stack, context },
		mText{ context.bitmapFonts->get(Fonts::Bitmaps::ID::Cyan), "PRESS ANY KEY TO START" },
		mShowText{ true },
		mTextEffectTime{ sf::Time::Zero },
		mBackground{ context.maps->get(Maps::ID::Title) }
	{
		sf::FloatRect bound{ mText.getLocalBounds() };
		mText.setOrigin(bound.size / 2.f);
		sf::View view{ context.window->getView() };
		sf::Vector2f position{ view.getCenter() };
		mText.setPosition({ position });
	}

	void TitleState::draw()
	{
		sf::RenderWindow& window{ *getContext().window };
		for (size_t i{ 0 }; i < mBackground.getLayerCount(); ++i)
			window.draw(mBackground.getLayer(i));
		if (mShowText)
			window.draw(mText);
	}

	bool TitleState::update(sf::Time dt)
	{
		mTextEffectTime += dt;
		if (mTextEffectTime >= sf::seconds(0.5f))
		{
			mShowText = !mShowText;
			mTextEffectTime = sf::Time::Zero;
		}
		return true;
	}

	bool TitleState::handleEvent(std::optional<sf::Event> const& event)
	{
		if (event->getIf<sf::Event::KeyPressed>())
		{
			requestStackPop();
			requestStackPushBack(States::ID::Menu);
		}
		return true;
	}
}

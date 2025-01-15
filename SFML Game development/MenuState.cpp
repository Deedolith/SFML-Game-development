#include <optional>
#include <memory>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include "MenuState.h"
#include "Utilities.h"
#include "Button.h"

namespace States
{
	MenuState::MenuState(StateStack& stack, State::Context context) :
		State{ stack, context },
		mBackground{ context.maps->get(Maps::ID::Title) },
		mGUIcontainer{}
	{
		auto playButton{ std::make_shared<GUI::Button>(*context.bitmapFonts, *context.textures, "PLAY") };
		playButton->setPosition(context.window->getView().getSize() / 2.f - sf::Vector2f{ 0.f, 24.f });
		playButton->setCallback([this]()
			{
				requestStackPushFront(States::ID::Game);
				requestStackPushBack(States::ID::TransitionForward);
			});
		mGUIcontainer.pack(playButton);

		auto exitButton{ std::make_shared<GUI::Button>(*context.bitmapFonts, *context.textures, "EXIT") };
		exitButton->setPosition(playButton->getPosition() + sf::Vector2f{ 0.f, 48.f });
		exitButton->setCallback([this]()
			{
				requestStackPop();
			});
		mGUIcontainer.pack(exitButton);
	}

	void MenuState::draw()
	{
		sf::RenderWindow& window{ *getContext().window };
		window.setView(window.getDefaultView());
		for (size_t i{ 0 }; i < mBackground.getLayerCount(); ++i)
			window.draw(mBackground.getLayer(i));
		window.draw(mGUIcontainer);
	}

	bool MenuState::update(sf::Time dt)
	{
		mGUIcontainer.update(dt);
		return false;
	}

	bool States::MenuState::handleEvent(std::optional<sf::Event> const& event)
	{
		mGUIcontainer.handleEvent(event);
		return true;
	}
}

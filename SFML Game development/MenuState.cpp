#include <optional>
#include <memory>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

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
		auto playButton{ std::make_shared<GUI::Button>("PLAY",  *getContext().bitmapFonts, *getContext().textures)};
		centerOrigin(*playButton);
		playButton->setPosition(context.window->getView().getSize() / 2.f - sf::Vector2f{ 0.f, 20.f });
		playButton->setCallback([this]()
			{
				requestStackPushFront(States::ID::Game);
				requestStackPushBack(States::ID::TransitionForward);
			});
		mGUIcontainer.pack(playButton);

		auto settingsButton{ std::make_shared<GUI::Button>("SETTINGS", *getContext().bitmapFonts, *getContext().textures) };
		centerOrigin(*settingsButton);
		settingsButton->setPosition(playButton->getPosition() + sf::Vector2f{ 0.f, 40.f });
		settingsButton->setCallback([this]()
			{
				requestStackPushBack(States::ID::Settings);
			});
		mGUIcontainer.pack(settingsButton);

		auto exitButton{ std::make_shared<GUI::Button>("EXIT", *getContext().bitmapFonts, *getContext().textures)};
		centerOrigin(*exitButton);
		exitButton->setPosition(settingsButton->getPosition() + sf::Vector2f{ 0.f, 40.f });
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
		return false;
	}
}

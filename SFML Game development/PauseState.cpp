#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "PauseState.h"
#include "Utilities.h"

namespace States
{
	PauseState::PauseState(StateStack& stack, State::Context context) :
		State{ stack, context },
		mTextRows{}
	{
		sf::RenderWindow& window{ *getContext().window };
		sf::Vector2f viewSize = context.window->getView().getSize();

		Ptr pauseText{ std::make_unique<BitmapText>(context.bitmapFonts->get(Fonts::Bitmaps::ID::Red), "GAME PAUSED") };
		centerOrigin(*pauseText);
		pauseText->setPosition(sf::Vector2f{ 0.5f * viewSize.x, 0.4f * viewSize.y });
		
		Ptr instructionText_1{ std::make_unique<BitmapText>(context.bitmapFonts->get(Fonts::Bitmaps::ID::White), "PRESS \"P\" TO CONTINUE") };
		centerOrigin(*instructionText_1);
		instructionText_1->setPosition(pauseText->getPosition() + sf::Vector2f{ 0.f, 10.f });
		
		Ptr instructionText_2{ std::make_unique<BitmapText>(context.bitmapFonts->get(Fonts::Bitmaps::ID::White), "OR ESCAPE") };
		centerOrigin(*instructionText_2);
		instructionText_2->setPosition(instructionText_1->getPosition() + sf::Vector2f{ 0.f, 10.f });
		
		Ptr instructionText_3{ std::make_unique<BitmapText>(context.bitmapFonts->get(Fonts::Bitmaps::ID::White), "TO RETURN TO MAIN MENU") };
		centerOrigin(*instructionText_3);
		instructionText_3->setPosition(instructionText_2->getPosition() + sf::Vector2f{ 0.f, 10.f });

		mTextRows.push_back(std::move(pauseText));
		mTextRows.push_back(std::move(instructionText_1));
		mTextRows.push_back(std::move(instructionText_2));
		mTextRows.push_back(std::move(instructionText_3));
	}

	void PauseState::draw()
	{
		sf::RenderWindow& window{ *getContext().window };
		window.setView(window.getDefaultView());
		sf::RectangleShape backGroundShape{ sf::Vector2f{ window.getSize() } };
		backGroundShape.setFillColor(sf::Color{ 0u, 0u, 0u, 150 });
		window.draw(backGroundShape);
		for (auto const& text : mTextRows)
			window.draw(*text);
	}

	bool PauseState::update(sf::Time dt)
	{
		return false;
	}

	bool PauseState::handleEvent(std::optional<sf::Event> const& event)
	{
		if (auto keyPressed{ event->getIf<sf::Event::KeyPressed>() })
		{
			if (keyPressed->code == sf::Keyboard::Key::P)
			{
				requestStackPop();
			}
			else if (keyPressed->code == sf::Keyboard::Key::Escape)
			{
				requestStackClear();
				requestStackPushBack(States::ID::Menu);
			}
		}
		return false;
	}
}

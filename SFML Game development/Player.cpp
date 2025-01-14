#include <iostream>
#include <utility>

#include <SFML/Window/Keyboard.hpp>

#include "Player.h"
#include "Command.h"
#include "Aircraft.h"
#include "AircraftMover.h"

bool Player::isRealTimeAction(Action action)
{
	switch (action)
	{
	case Action::Fire:
		return false;
		break;
	default:
		return true;
		break;
	}
}

void Player::setInitialKeyBinding()
{
	mKeyBinding[sf::Keyboard::Key::Q] = Action::MoveLeft;
	mKeyBinding[sf::Keyboard::Key::D] = Action::MoveRight;
	mKeyBinding[sf::Keyboard::Key::Z] = Action::MoveUp;
	mKeyBinding[sf::Keyboard::Key::S] = Action::MoveDown;
}

void Player::setInitialActionBinding()
{
	float const playerSpeed{ 30.f };
	mActionBinding[Action::MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
	mActionBinding[Action::MoveRight].action = derivedAction<Aircraft>(AircraftMover(playerSpeed, 0.f));
	mActionBinding[Action::MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
	mActionBinding[Action::MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f, playerSpeed));

	for (auto& pair : mActionBinding)
		pair.second.category = Category::Type::Player;
}

Player::Player() :
	mKeyBinding{},
	mActionBinding{}
{
	setInitialKeyBinding();
	setInitialActionBinding();
}

void Player::handleEvent(std::optional<sf::Event> const& event, CommandQueue& commands)
{
	if (event->is<sf::Event::KeyPressed>())
	{
		if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::P)
		{
			Command output;
			output.category = Category::Player;
			output.action = [](SceneNode& node, sf::Time dt)
				{
					std::cout << node.getPosition().x << ", " << node.getPosition().y << std::endl;
				};
			commands.push(output);
		}
	}
}

void Player::handleRealTimeInput(CommandQueue& commands)
{
	for (auto pair : mKeyBinding)
	{
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second))
		{
			commands.push(mActionBinding[pair.second]);
		}
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	for(auto pair : mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Key::Unknown;
}

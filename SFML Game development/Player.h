#pragma once

#include <optional>
#include <map>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "CommandQueue.h"
#include "Command.h"

class Player
{
public:
	enum class Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		Fire
	};
private:
	std::map<sf::Keyboard::Key, Action> mKeyBinding;
	std::map<Action, Command> mActionBinding;
private:
	static bool isRealTimeAction(Action action);
	void setInitialKeyBinding();
	void setInitialActionBinding();
public:
	Player();
	void handleEvent(std::optional<sf::Event> const& event, CommandQueue& commands);
	void handleRealTimeInput(CommandQueue& commands);
	void assignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key getAssignedKey(Action action) const;
};


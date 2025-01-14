#pragma once

#include <optional>
#include <filesystem>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "StateStack.h"
#include "State.h"
#include "World.h"
#include "Player.h"

namespace States
{
	class GameState :
		public State
	{
	private:
		World mWorld;
		Player& mPlayer;
	public:
		GameState(StateStack& stack, State::Context context);
		virtual void draw() override;
		virtual bool update(sf::Time dt) override;
		virtual bool handleEvent(std::optional<sf::Event> const& event) override;
	};
}

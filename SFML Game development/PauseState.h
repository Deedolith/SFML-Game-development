#pragma once

#include <optional>
#include <vector>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "StateStack.h"
#include "State.h"
#include "BitmapText.h"

namespace States
{
	class PauseState :
		public State
	{
	private:
		std::vector<Fonts::Bitmaps::Text> mTextRows;
	public:
		PauseState(StateStack& stack, State::Context context);
		void draw() override;
		bool update(sf::Time dt)  override;
		bool handleEvent(std::optional<sf::Event> const& event) override;
	};
}

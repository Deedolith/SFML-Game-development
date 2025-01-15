#pragma once

#include <optional>
#include <vector>
#include <memory>

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
		using BitmapText = Fonts::Bitmaps::Text;
		using Ptr = std::unique_ptr<BitmapText>;
	private:
		std::vector<Ptr> mTextRows;
	public:
		PauseState(StateStack& stack, State::Context context);
		void draw() override;
		bool update(sf::Time dt)  override;
		bool handleEvent(std::optional<sf::Event> const& event) override;
	};
}

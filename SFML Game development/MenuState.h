#pragma once

#include "State.h"
#include "StateStack.h"
#include "Map.h"
#include "Container.h"

namespace States
{
	class MenuState :
		public State
	{
	private:
		enum Option
		{
			Play,
			Exit
		};
	private:
		Maps::Map mBackground;
		GUI::Container mGUIcontainer;
	private:

	public:
		MenuState(StateStack& stack, State::Context context);
		void draw() override;
		bool update(sf::Time dt) override;
		bool handleEvent(std::optional<sf::Event> const& event) override;
	};
}

#pragma once

#include <optional>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "StateStack.h"
#include "State.h"
#include "ParallelTask.h"

namespace States
{
	class LoadingState :
		public State
	{
	private:
		sf::Text mLoadingText;
		sf::RectangleShape mProgressBarBackground;
		sf::RectangleShape mProgressBar;
		ParallelTask mLoadingTask;
	private:
		void setCompletion(float percent);
	public:
		LoadingState(StateStack& stack, State::Context context);
		void draw() override;
		bool update(sf::Time dt) override;
		bool handleEvent(std::optional<sf::Event> const& event) override;
	};
}

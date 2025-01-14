#include "GameState.h"
#include "StateIdentifiers.h"

namespace States
{
	GameState::GameState(StateStack& stack, State::Context context) :
		State(stack, context),
		mWorld{ context },
		mPlayer{ *context.player }
	{
	}

	void GameState::draw()
	{
		mWorld.draw();
	}

	bool GameState::update(sf::Time dt)
	{
		mWorld.update(dt);
		CommandQueue& commands = mWorld.getCommandQueue();
		mPlayer.handleRealTimeInput(commands);
		return true;
	}

	bool GameState::handleEvent(std::optional<sf::Event> const& event)
	{
		// Game input handling
		CommandQueue& commands = mWorld.getCommandQueue();
		mPlayer.handleEvent(event, commands);

		// Escape pressed, trigger the pause screen
		if (auto keyPressed{ event->getIf<sf::Event::KeyPressed>() })
		{
			if (keyPressed->code == sf::Keyboard::Key::P)
				requestStackPushBack(States::ID::Pause);
		}
		return true;
	}
}
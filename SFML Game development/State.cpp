#include "State.h"
#include "StateStack.h"

namespace States
{
	void State::requestStackPushBack(States::ID stateID)
	{
		mStack->pushBackState(stateID);
	}

	void State::requestStackPushFront(States::ID stateID)
	{
		mStack->pushFrontState(stateID);
	}

	void State::requestStackPop()
	{
		mStack->popState();
	}

	void State::requestStackClear()
	{
		mStack->clearStates();
	}

	State::Context State::getContext() const
	{
		return mContext;
	}

	State::State(StateStack& stack, State::Context context) :
		mStack(&stack),
		mContext(context)
	{
	}

	State::~State()
	{
	}

	State::Context::Context(sf::RenderWindow& window, Textures::TexturesHolder& textures, Fonts::FontsHolder& fonts, Fonts::Bitmaps::FontsHolder& bitmapFonts, Maps::MapsHolder& maps, Player& player, std::filesystem::path const& basePath) :
		window{ &window },
		textures{ &textures },
		fonts{ &fonts },
		bitmapFonts{ &bitmapFonts },
		maps{ &maps },
		player{ &player },
		basePath{ basePath }
	{
	}
}

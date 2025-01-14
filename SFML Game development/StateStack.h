#pragma once

#include <vector>
#include <map>
#include <functional>
#include <memory>
#include <optional>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "State.h"
#include "StateIdentifiers.h"

namespace States
{
	class StateStack
	{
	public:
		enum class Action
		{
			PushBack,
			PushFront,
			Pop,
			Clear
		};
	private:
		class PendingChange
		{
		public:
			Action action;
			States::ID stateID;
		public:
			PendingChange(Action action, States::ID stateID = States::ID::None);
		};
	private:
		std::vector<State::Ptr> mStack;
		std::vector<StateStack::PendingChange> mPendingList;
		State::Context mContext;
		std::map<States::ID, std::function<State::Ptr(void)>> mFactories;
	private:
		State::Ptr createState(States::ID stateID);
		void applyPendingChanges();
	public:
		StateStack(State::Context context);
		StateStack(StateStack const&) = delete;
		StateStack& operator=(StateStack const&) = delete;
		template <class T>
		void registerState(States::ID stateID);
		void update(sf::Time dt);
		void draw();
		void handleEvent(std::optional<sf::Event> const& event);
		void pushBackState(States::ID stateID);
		void pushFrontState(States::ID stateID);
		void popState();
		void clearStates();
		bool isEmpty() const;
	};
}
#include "StateStack.inl"

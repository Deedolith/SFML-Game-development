#include <cassert>

#include "StateStack.h"

namespace States
{
    State::Ptr StateStack::createState(States::ID stateID)
    {
        auto found{ mFactories.find(stateID) };
        assert(found != mFactories.end() && "The given stateID is not registered");
        return found->second();
    }

    void StateStack::applyPendingChanges()
    {
        for (auto change : mPendingList)
        {
            switch (change.action)
            {
            case Action::PushBack:
                mStack.push_back(createState(change.stateID));
                break;
            case Action::PushFront:
                mStack.push_back(createState(change.stateID));
                std::rotate(mStack.rbegin(), mStack.rbegin() + 1, mStack.rend());
                break;
            case Action::Pop:
                mStack.pop_back();
                break;
            case Action::Clear:
                mStack.clear();
                break;
            default:
                assert(false && "Unknown requested change.");
                break;
            }
        }
        mPendingList.clear();
    }

    StateStack::StateStack(State::Context context) :
        mStack(),
        mPendingList(),
        mContext(context),
        mFactories()
    {
    }

    void StateStack::update(sf::Time dt)
    {
        for (auto it{ mStack.rbegin() }; it != mStack.rend(); ++it)
        {
            if (!(*it)->update(dt))
                break;
        }
        applyPendingChanges();
    }

    void StateStack::draw()
    {
        for (auto& state : mStack)
            state->draw();
    }

    void StateStack::handleEvent(std::optional<sf::Event> const& event)
    {
        for (auto it{ mStack.rbegin() }; it != mStack.rend(); ++it)
        {
            if (!(*it)->handleEvent(event))
                break;
        }
        applyPendingChanges();
    }

    void StateStack::pushBackState(States::ID stateID)
    {
        mPendingList.push_back(PendingChange{ Action::PushBack, stateID });
    }

    void StateStack::pushFrontState(States::ID stateID)
    {
        mPendingList.push_back(PendingChange{ Action::PushFront, stateID });
    }

    void StateStack::popState()
    {
        mPendingList.push_back(PendingChange{ Action::Pop });
    }

    void StateStack::clearStates()
    {
        mPendingList.push_back(PendingChange{ Action::Clear });
    }

    bool StateStack::isEmpty() const
    {
        return mStack.empty();
    }

    StateStack::PendingChange::PendingChange(Action action, States::ID stateID) :
        action{ action },
        stateID{ stateID }
    {
    }
}

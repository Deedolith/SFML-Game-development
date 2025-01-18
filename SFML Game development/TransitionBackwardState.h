#pragma once

#include <optional>
#include <vector>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

#include "StateStack.h"
#include "State.h"
#include "Visibility.h"

namespace States
{
    class TransitionBackwardState :
        public State
    {
    private:
        sf::Time mElapsedTime;
        Maps::Map mMap;
        std::vector<std::vector<Visibility>> mLayerVisibilities;
        sf::Time const mTimePerFrame;
        sf::Time mDuration;
    private:
        void updateLayers();
        void updateLayer(Maps::Map::Layer& layer, size_t index);
    public:
        TransitionBackwardState(StateStack& stack, State::Context context);
        virtual void draw() override;
        virtual bool update(sf::Time dt) override;
        virtual bool handleEvent(std::optional<sf::Event> const& event) override;
    };
}


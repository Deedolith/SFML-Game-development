#pragma once

#include <optional>
#include <vector>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "StateIdentifiers.h"
#include "StateStack.h"
#include "State.h"
#include "Map.h"
#include "Visibility.h"

namespace States
{
    class TransitionForwardState :
        public State
    {
    private:
        sf::Time mElapsedTime;
        Maps::Map mMap;
        std::vector<std::vector<Visibility>> mLayerVisibilities;
    private:
        void updateLayers();
        void updateLayer(Maps::Map::Layer& layer, size_t index);
    public:
        TransitionForwardState(StateStack& stack, State::Context context);
        void draw() override;
        bool update(sf::Time dt) override;
        bool handleEvent(std::optional<sf::Event> const& event) override;
    };
}

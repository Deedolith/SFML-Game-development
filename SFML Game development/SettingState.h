#pragma once

#include <optional>
#include <array>
#include <memory>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>

#include "State.h"
#include "StateStack.h"
#include "Container.h"
#include "Button.h"
#include "Label.h"
#include "Map.h"
#include "Player.h"

namespace States
{
    class SettingState :
        public State
    {
    private:
        GUI::Container mGUIcontainer;
        Maps::Map mBackgroundMap;
        std::array<GUI::Button::Ptr, Player::Action::ActionsCount> mBindingButtons;
        std::array<GUI::Label::Ptr, Player::Action::ActionsCount> mLabels;
    private:
        void buildButtonAndLabel(Player::Action action, sf::Vector2f const& position, std::string const& text);
        void updateLabels();
    public:
        SettingState(StateStack& stack, State::Context context);
        void draw() override;
        bool update(sf::Time dt) override;
        bool handleEvent(std::optional<sf::Event> const& event) override;
    };
}


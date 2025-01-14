#pragma once

#include <optional>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include "State.h"
#include "StateStack.h"
#include "BitmapText.h"
#include "Map.h"

namespace States
{
    class TitleState :
        public State
    {
    private:
        Fonts::Bitmaps::Text mText;
        bool mShowText;
        sf::Time mTextEffectTime;
        Maps::Map mBackground;
    public:
        TitleState(StateStack& stack, State::Context context);
        void draw() override;
        bool update(sf::Time dt) override;
        bool handleEvent(std::optional<sf::Event> const& event) override;
    };
}

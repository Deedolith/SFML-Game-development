#pragma once

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "BitmapFontsHolder.h"
#include "TexturesHolder.h"
#include "BitmapText.h"
#include "Button.h"

namespace GUI
{
    class ToggleButton :
        public Button
    {
    public:
        using Ptr = std::shared_ptr<ToggleButton>;
    private:
        bool mIsPressed;
    private:
        //void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    public:
        ToggleButton(std::string const& text, Fonts::Bitmaps::FontsHolder const& fonts, Textures::TexturesHolder const& textures);
        //bool isSelectable() const override final;
        void activate() override;
        void deactivate() override;
        bool isActive() const override;
        //void select() override;
        //void deselect() override;
        bool handleEvent(std::optional<sf::Event> const& event) override final;
        //void setCallback(Button::Callback callback);
        //sf::FloatRect getLocalBounds() const;
        //void update(sf::Time dt) override;
    };
}


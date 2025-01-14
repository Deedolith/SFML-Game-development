#pragma once

#include <vector>
#include <functional>
#include <memory>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "Component.h"
#include "BitmapFont.h"
#include "BitmapText.h"
#include "BitmapFontsHolder.h"
#include "TexturesHolder.h"

namespace GUI
{
    class Button :
        public Component
    {
    public:
        using Callback = std::function<void()>;
        using Ptr = std::shared_ptr<Button>;
    private:
        std::vector<sf::Sprite> mBackFrame;
        std::vector<sf::Sprite> mFrontFrame;
        Fonts::Bitmaps::Text mNormalText;
        Fonts::Bitmaps::Text mPressedText;
        Fonts::Bitmaps::Text mSelectedText;
        Fonts::Bitmaps::Text* mText;
        bool mIsToggle;
        Callback mCallback;
    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    public:
        Button(Fonts::Bitmaps::FontsHolder const& fonts, Textures::TexturesHolder const& textures, sf::String const& text);
        bool isSelectable() const override final;
        void activate() override;
        void deactivate() override;
        void select() override;
        void deselect() override;
        void handleEvent(std::optional<sf::Event> const& event) override final;
        void setToggle(bool toggleState);
        void setCallback(Callback callback);
        sf::FloatRect getLocalBounds() const;
    };
}

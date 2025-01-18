#pragma once

#include <vector>
#include <functional>
#include <memory>
#include <chrono>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>

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
        std::vector<sf::Sprite> mBackFrameSprites;
        std::vector<sf::IntRect> mBackFrameRects;
        std::vector<sf::Sprite> mFrontFrameSprites;
        std::vector<sf::IntRect> mFrontFrameRects;
        Fonts::Bitmaps::Text mNormalText;
        Fonts::Bitmaps::Text mPressedText;
        Fonts::Bitmaps::Text mSelectedText;
        Fonts::Bitmaps::Text* mText;
        Callback mCallback;
        sf::Time mElapsedTime;
        unsigned mFrameIndex;
        sf::Time const mTimeForUpdate;
    protected:
        void callback();
    private:
        void buildText();
        void buildFrontFrame(Textures::TexturesHolder const& textures);
        void buildBackFrame(Textures::TexturesHolder const& textures);
        void updateBackFrame();
        void updateFrontFrame();
    protected:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    public:
        Button(std::string const& text, Fonts::Bitmaps::FontsHolder const& fonts, Textures::TexturesHolder const& textures);
        virtual ~Button() = default;
        bool isSelectable() const override;
        virtual void activate() override;
        virtual void deactivate() override;
        virtual bool isActive() const override;
        void select() override;
        void deselect() override;
        virtual bool handleEvent(std::optional<sf::Event> const& event) override;
        void setCallback(Callback callback);
        sf::FloatRect getLocalBounds() const;
        void update(sf::Time dt) override;
    };
}

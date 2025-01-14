#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "SceneNode.h"

class SpriteNode :
    public SceneNode
{
private:
    sf::Sprite mSprite;
private:
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    explicit SpriteNode(sf::Texture const& texture);
    SpriteNode(sf::Texture const& texture, sf::IntRect const& rect);
};


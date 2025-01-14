#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include "Entity.h"
#include "Textures.h"
#include "TexturesHolder.h"

class Aircraft :
    public Entity
{
public:
    enum class Type
    {
        Player1,
        Player2
    };
private:
    Type mType;
    sf::Sprite mSprite;
public:
    explicit Aircraft(Type type, Textures::TexturesHolder const& textures);
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    unsigned getCategory() const override;
    void accelerate(sf::Vector2f velocity);
	sf::Vector2f getSize() const;
};

Textures::ID toTextureID(Aircraft::Type type);


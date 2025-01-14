#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "BitmapText.h"

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);
void centerOrigin(Fonts::Bitmaps::Text& text);
std::vector<unsigned> splitString(const std::string& s, char delimiter);


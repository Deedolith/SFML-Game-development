#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "BitmapText.h"

//void centerOrigin(sf::Sprite& sprite);
//void centerOrigin(sf::Text& text);
//void centerOrigin(Fonts::Bitmaps::Text& text);
template <class T>
void centerOrigin(T& item);
std::vector<unsigned> splitString(const std::string& s, char delimiter);
std::string keyToString(sf::Keyboard::Key key);
std::string toUpperCase(std::string string);

#include "Utilities.inl"

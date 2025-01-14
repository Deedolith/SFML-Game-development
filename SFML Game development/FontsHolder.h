#pragma once

#include <SFML/Graphics/Font.hpp>

#include "RessourceHolder.h"
#include "Fonts.h"

namespace Fonts
{
	using FontsHolder = RessourceHolder<sf::Font, Fonts::ID>;
}
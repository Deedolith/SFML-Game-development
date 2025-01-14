#pragma once

#include <SFML/Graphics/Texture.hpp>

#include "RessourceHolder.h"
#include "Textures.h"

namespace Textures
{
	using TexturesHolder = RessourceHolder<sf::Texture, Textures::ID>;
}

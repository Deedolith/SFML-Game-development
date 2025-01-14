#pragma once

#include "RessourceHolder.h"
#include "Map.h"
#include "Maps.h"

namespace Maps
{
	using MapsHolder = RessourceHolder<Map, Maps::ID>;
}

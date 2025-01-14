#pragma once

namespace Category
{
	enum Type
	{
		None = 0,
		Scene = 1 << 0,
		Player = 1 << 1,
		Allied = 1 << 2,
		Ennemy = 1 << 3
	};
}

#include "Category.h"

inline Category::Type operator|(Category::Type lft, Category::Type rgt)
{
	return static_cast<Category::Type>(static_cast<unsigned>(lft) | static_cast<unsigned>(rgt));
}

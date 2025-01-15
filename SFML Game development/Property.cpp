#include <string>

#include "Property.h"

namespace Maps
{
	Property::Property(std::string const& value) :
		mValue{ value }
	{
	}

	unsigned Property::as_uint() const
	{
		return std::stoul(mValue);
	}

	int Property::as_int() const
	{
		return std::stoi(mValue);
	}

	std::string Property::as_string() const
	{
		return mValue;
	}
}

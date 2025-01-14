#pragma once

#include <vector>

#include <pugixml.hpp>

namespace Maps
{
	class Property
	{
	private:
		std::string mValue;
	public:
		Property(std::string const& value);
		unsigned as_uint() const;
		std::string as_string() const;
	};
}


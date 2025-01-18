#pragma once

#include <string>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "Component.h"
#include "BitmapText.h"
#include "BitmapFontsHolder.h"

namespace GUI
{
	class Label :
		public Component
	{
	public:
		using Ptr = std::shared_ptr<Label>;
	private:
		Fonts::Bitmaps::Text mText;
	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		Label(std::string const& text, Fonts::Bitmaps::ID color, Fonts::Bitmaps::FontsHolder& fonts);
		bool isSelectable() const override final;
		void setText(std::string const& text);
		sf::FloatRect getLocalBounds() const;
	};
}

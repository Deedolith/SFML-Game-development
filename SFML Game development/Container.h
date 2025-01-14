#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "Component.h"

namespace GUI
{
	class Container :
		public Component
	{
	public:
		using Ptr = std::shared_ptr<Container>;
	private:
		std::vector<Component::Ptr> mChildren;
		int mSelectedChild;
	private:
		void select(std::size_t index);
		bool hasSelection() const;
		void selectNext();
		void selectPrevious();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		Container();
		void pack(Component::Ptr component);
		bool isSelectable() const override;
		void handleEvent(std::optional<sf::Event> const& event) override;
	};
}


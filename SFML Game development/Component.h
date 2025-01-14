#pragma once

#include <memory>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>

namespace GUI
{
	class Component :
		public sf::Transformable,
		public sf::Drawable
	{
	public:
		using Ptr = std::shared_ptr<Component>;
	private:
		bool mIsSelected;
		bool mIsActive;
	public:
		Component();
		Component(Component const&) = delete;
		Component& operator=(Component const&) = delete;
		virtual ~Component();
		virtual bool isSelectable() const = 0;
		bool isSelected() const;
		virtual void select();
		virtual void deselect();
		virtual bool isActive() const;
		virtual void activate();
		virtual void deactivate();
		virtual void handleEvent(std::optional<sf::Event> const& event) = 0;
	};
}

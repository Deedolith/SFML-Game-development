#include "Container.h"

namespace GUI
{
	void Container::select(std::size_t index)
	{
		if (mChildren[index]->isSelectable())
		{
			if (hasSelection())
				mChildren[mSelectedChild]->deselect();
			mChildren[index]->select();
			mSelectedChild = static_cast<int>(index);
		}
	}

	bool Container::hasSelection() const
	{
		for (auto const& child : mChildren)
		{
			if (child->isSelected())
				return true;
		}
		return false;
	}

	void Container::selectNext()
	{
		if (!hasSelection())
			return;
		// Search next component that is selectable, wrap around if necessary
		int next{ mSelectedChild };
		do
			next = (next + 1) % mChildren.size();
		while (!mChildren[next]->isSelectable());
		// Select that component
		select(next);
	}

	void Container::selectPrevious()
	{
		if (!hasSelection())
			return;
		// Search previous component that is selectable, wrap around if necessary
		int previous{ mSelectedChild };
		do
			previous = static_cast<int>((previous + mChildren.size() - 1) % mChildren.size());
		while (!mChildren[previous]->isSelectable());
		// Select that component
		select(previous);
	}

	void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		for (auto const& child : mChildren)
			target.draw(*child, states);
	}

	Container::Container() :
		mChildren{},
		mSelectedChild{ -1 }
	{
	}

	void Container::pack(Component::Ptr component)
	{
		mChildren.push_back(component);
		if (!hasSelection() && component->isSelectable())
			select(mChildren.size() - 1);
	}

	bool Container::isSelectable() const
	{
		return false;
	}

	bool Container::handleEvent(std::optional<sf::Event> const& event)
	{
		if (hasSelection() && mChildren[mSelectedChild]->isSelected())
		{
			bool bubbleEvent{ mChildren[mSelectedChild]->handleEvent(event) };
			if (bubbleEvent)
			{
				if (auto keyReleased{ event->getIf< sf::Event::KeyReleased>() })
				{
					if (keyReleased->code == sf::Keyboard::Key::Z)
						selectPrevious();
					else if (keyReleased->code == sf::Keyboard::Key::S)
						selectNext();
				}
			}
			return bubbleEvent;
		}
		return true;
	}

	void Container::update(sf::Time dt)
	{
		for (auto const& child : mChildren)
			child->update(dt);
	}
}
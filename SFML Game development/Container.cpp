#include "Container.h"

void GUI::Container::select(std::size_t index)
{
	if (mChildren[index]->isSelectable())
	{
		if (hasSelection())
			mChildren[mSelectedChild]->deselect();
		mChildren[index]->select();
		mSelectedChild = static_cast<int>(index);
	}
}

bool GUI::Container::hasSelection() const
{
	for(auto const& child : mChildren)
	{
		if (child->isSelected())
			return true;
	}
	return false;
}

void GUI::Container::selectNext()
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

void GUI::Container::selectPrevious()
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

void GUI::Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	for (auto const& child : mChildren)
		target.draw(*child, states);
}

GUI::Container::Container() :
	mChildren{},
	mSelectedChild{ -1 }
{
}

void GUI::Container::pack(Component::Ptr component)
{
	mChildren.push_back(component);
	if (!hasSelection() && component->isSelectable())
		select(mChildren.size() - 1);
}

bool GUI::Container::isSelectable() const
{
	return false;
}

void GUI::Container::handleEvent(std::optional<sf::Event> const& event)
{
	if (hasSelection() && mChildren[mSelectedChild]->isActive())
		mChildren[mSelectedChild]->handleEvent(event);
	else if (auto keyReleased{ event->getIf< sf::Event::KeyReleased>() })
	{
		if (keyReleased->code == sf::Keyboard::Key::Z)
			selectPrevious();
		else if (keyReleased->code == sf::Keyboard::Key::S)
			selectNext();
		else if (keyReleased->code == sf::Keyboard::Key::Enter)
		{
			if (hasSelection())
				mChildren[mSelectedChild]->activate();
		}
	}
}

void GUI::Container::update(sf::Time dt)
{
	for (auto const& child : mChildren)
		child->update(dt);
}

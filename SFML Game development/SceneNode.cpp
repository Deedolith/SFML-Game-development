#include <algorithm>
#include <cassert>

#include "SceneNode.h"

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto const& child : mChildren)
		child->draw(target, states);
}

void SceneNode::updateCurrent(sf::Time dt)
{
}

void SceneNode::updateChildren(sf::Time dt)
{
	for (auto const& child : mChildren)
		child->update(dt);
}

void SceneNode::onCommand(Command const& command, sf::Time dt)
{
	if (command.category & getCategory())
		command.action(*this, dt);
	for (auto& child : mChildren)
		child->onCommand(command, dt);
}

SceneNode::SceneNode() :
	mParent{ nullptr },
	mChildren{}
{
}

void SceneNode::attachChild(Ptr child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(SceneNode const& node)
{
	auto found{ std::find_if(mChildren.begin(), mChildren.end(),
		[&](Ptr& p)->bool
		{
			return p.get() == &node;
		}
	) };
	assert(found != mChildren.end());

	Ptr result{ std::move(*found) };
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}

void SceneNode::update(sf::Time dt)
{
	updateCurrent(dt);
	updateChildren(dt);
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform{ sf::Transform::Identity };
	for (auto const* node{ this }; node != nullptr; node = node->mParent)
		transform = node->getTransform() * transform;
	return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f{};
}

unsigned SceneNode::getCategory() const
{
	return Category::Type::Scene;
}

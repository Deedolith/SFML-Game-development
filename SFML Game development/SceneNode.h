#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Vector2.hpp>

#include "Category.h"
#include "Command.h"

class Command;

class SceneNode :
	public sf::Transformable,
	public sf::Drawable
{
public:
	using Ptr = std::unique_ptr<SceneNode>;
private:
	std::vector<Ptr> mChildren;
	SceneNode* mParent;
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void updateCurrent(sf::Time dt);
	void updateChildren(sf::Time dt);
public:
	SceneNode();
	SceneNode(SceneNode const&) = delete;
	SceneNode& operator=(SceneNode const&) = delete;
	void attachChild(Ptr child);
	Ptr detachChild(SceneNode const& node);
	void update(sf::Time dt);
	sf::Transform getWorldTransform() const;
	sf::Vector2f getWorldPosition() const;
	virtual unsigned getCategory() const;
	void onCommand(Command const& command, sf::Time dt);
};


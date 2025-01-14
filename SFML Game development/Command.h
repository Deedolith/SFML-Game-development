#pragma once

#include <functional>
#include <cassert>

#include <SFML/System/Time.hpp>

#include "SceneNode.h"

class SceneNode;

class Command
{
private:
public:
	std::function<void (SceneNode&, sf::Time)> action;
	unsigned category;
public:
	Command();
};

template <class GameObject, class Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn);

#include "Command.inl"

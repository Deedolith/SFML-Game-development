template<class GameObject, class Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
	return [=](SceneNode& node, sf::Time dt)
		{
			// Check if cast is safe
			assert(dynamic_cast<GameObject*>(&node) != nullptr);
			fn(static_cast<GameObject&>(node), dt);
		};
}

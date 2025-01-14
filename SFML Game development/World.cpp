#include <memory>
#include <algorithm>

#include <SFML/Graphics/Texture.hpp>

#include "World.h"
#include "SpriteNode.h"

void World::buildScene()
{
	for (std::size_t i{ 0 }; i < World::Layer::LayerCount; ++i)
	{
		SceneNode::Ptr layer{ std::make_unique<SceneNode>() };
		mSceneLayers[i] = layer.get();
		mSceneGraph.attachChild(std::move(layer));
	}

		// background
	sf::Texture& texture{ mTextures.get(Textures::ID::Background) };
	sf::IntRect textureRect{ mWorldBounds };
	std::unique_ptr<SpriteNode> backgroundSprite{ std::make_unique<SpriteNode>(texture, textureRect) };
	backgroundSprite->setPosition({ mWorldBounds.position });
	mSceneLayers[World::Layer::Background]->attachChild(std::move(backgroundSprite));

		// airplane
	std::unique_ptr<Aircraft> playerAircraft{ std::make_unique<Aircraft>(Aircraft::Type::Player1, mTextures) };
	mPlayerAircraft = playerAircraft.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
	mSceneLayers[World::Layer::Air]->attachChild(std::move(playerAircraft));
}

void World::adaptPlayerVelocity()
{
	sf::Vector2f velocity{ mPlayerAircraft->getVelocity() };
	if (velocity.x != 0.f && velocity.y != 0.f)
		mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));
	mPlayerAircraft->accelerate({ 0.f, mScrollSpeed });
}

void World::adaptPlayerPosition()
{
	sf::FloatRect viewBounds{ mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize() };
	float borderDistance{ 0.f };
	sf::Vector2f position{ mPlayerAircraft->getPosition() };
	// keep player's position inside the screen bounds
		// from left and right
	position.x = std::max(position.x, viewBounds.position.x + borderDistance);
	position.x = std::min(position.x, viewBounds.position.x + viewBounds.size.x - borderDistance);
		// from top
	borderDistance = mPlayerAircraft->getSize().y / 2.f;
	position.y = std::max(position.y, viewBounds.position.y + borderDistance +3.F);
		// from bottom
	position.y = std::min(position.y, viewBounds.position.y + viewBounds.size.y - borderDistance);
	mPlayerAircraft->setPosition(position);

}

World::World(States::State::Context context) :
	mWindow{ *context.window },
	mWorldView{ mWindow.getDefaultView() },
	mTextures{ *context.textures },
	mBitmapFonts{ *context.bitmapFonts },
	mSceneGraph{},
	mSceneLayers{nullptr},
	mWorldBounds{ { 0.f, 0.f }, { 336.f, 6080.f } },
	mSpawnPosition{ mWorldBounds.size.x / 2.f, mWorldBounds.size.y - mWorldView.getSize().y },
	mScrollSpeed{ -320.f / 30.32f },
	mPlayerAircraft{ nullptr },
	mCommandQueue{}
{
	buildScene();
	mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{
		// Update aircraft
	mPlayerAircraft->setVelocity(0.f, 0.f);

		// forward commands to the scene graph
	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);

	adaptPlayerVelocity();
	mSceneGraph.update(dt);
	adaptPlayerPosition();

	// Scroll the view vertically
	sf::Vector2f viewPosition{ 0.f, mWorldView.getCenter().y + mScrollSpeed * dt.asSeconds() };

	// Scroll the view horizontally
	sf::Vector2f position{ mPlayerAircraft->getPosition() };
	sf::Vector2f viewSize{ mWorldView.getSize() };
	viewPosition.x = std::max(position.x, mWorldBounds.position.x + viewSize.x / 2.f);
	viewPosition.x = std::min(viewPosition.x, mWorldBounds.position.x + mWorldBounds.size.x - viewSize.x / 2.f);
	mWorldView.setCenter(viewPosition);
}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

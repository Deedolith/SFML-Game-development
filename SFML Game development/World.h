#pragma once

#include <array>
#include <filesystem>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "TexturesHolder.h"
#include "BitmapFontsHolder.h"
#include "SceneNode.h"
#include "Aircraft.h"
#include "CommandQueue.h"
#include "State.h"

class World
{
private:
	enum Layer
	{
		Background,
		Air,
		LayerCount
	};
private:
	sf::RenderWindow& mWindow;
	sf::View mWorldView;
	Textures::TexturesHolder& mTextures;
	Fonts::Bitmaps::FontsHolder& mBitmapFonts;
	SceneNode mSceneGraph;
	std::array<SceneNode*, World::Layer::LayerCount> mSceneLayers;
	sf::FloatRect mWorldBounds;
	sf::Vector2f mSpawnPosition;
	float mScrollSpeed;
	Aircraft* mPlayerAircraft;
	CommandQueue mCommandQueue;

private:
	void buildScene();
	void adaptPlayerVelocity();
	void adaptPlayerPosition();
public:
	explicit World(States::State::Context context);
	World(World const&) = delete;
	World& operator=(World const&) = delete;
	void update(sf::Time dt);
	void draw();
	CommandQueue& getCommandQueue();
};


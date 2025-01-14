#pragma once

#include <filesystem>
#include <memory>
#include <optional>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include "TexturesHolder.h"
#include "FontsHolder.h"
#include "BitmapFontsHolder.h"
#include "MapsHolder.h"
#include "Player.h"
#include "StateStack.h"

class Application
{
private:
	static sf::Time const mTimePerFrame;
	static float const mAspectRatio;
	std::filesystem::path const mBasePath;
	static sf::Vector2u const mSize;
	sf::RenderWindow mWindow;
	Textures::TexturesHolder mTextures;
	Fonts::FontsHolder mFonts;
	Fonts::Bitmaps::FontsHolder mBitmapFonts;
	Maps::MapsHolder mMaps;
	Player mPlayer;
	States::StateStack mStateStack;
	std::unique_ptr<sf::Text> mStatisticsText;
	sf::Time mStatisticsUpdateTime;
	std::size_t mStatisticsNumFrames;
private:
	void processEvents();
	void update(sf::Time dt);
	void render();
	void updateStatistics(sf::Time dt);
	void registerStates();
	void loadRessources();
	void loadTextures();
	void loadFonts();
	void loadBitmapFonts();
	void loadMaps();
public:
	Application(Application const&) = delete;
	Application& operator=(Application const&) = delete;
	Application(std::filesystem::path const& basePath = std::filesystem::path());
	void run();
};


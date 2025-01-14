#include <SFML/Window/VideoMode.hpp>

#include "Application.h"
#include "StateIdentifiers.h"
#include "Fonts.h"
#include "FontLoader.h"
#include "Textures.h"
#include "TextureLoader.h"
#include "BitmapFonts.h"
#include "BitmapFontLoader.h"
#include "Maps.h"
#include "MapLoader.h"
#include "TitleState.h"
#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"
#include "LoadingState.h"
#include "TransitionForwardState.h"
#include "TransitionBackwardState.h"

const sf::Time Application::mTimePerFrame = sf::seconds(1.f / 60.f);
const sf::Vector2u Application::mSize = { 240u, 320u };
const float Application::mAspectRatio{ static_cast<float>(mSize.x) / static_cast<float>(mSize.y) };

void Application::processEvents()
{
	while (std::optional<sf::Event> const event{ mWindow.pollEvent() })
	{
		// Handle window events
		if (event->is<sf::Event::Closed>())
			mWindow.close();
		else if (event->is<sf::Event::Resized>())
		{
			sf::Vector2u size{ mWindow.getSize() };
			size.x = static_cast<unsigned>(static_cast<float>(size.y) * mAspectRatio);
			mWindow.setSize(size);
		}
		// Handle input events
		mStateStack.handleEvent(event);
	}
}

void Application::update(sf::Time dt)
{
	mStateStack.update(dt);
}

void Application::render()
{
	mWindow.clear();
	mStateStack.draw();
	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(*mStatisticsText);
	mWindow.display();
}

void Application::updateStatistics(sf::Time dt)
{
	mStatisticsUpdateTime += dt;
	mStatisticsNumFrames += 1;
	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText->setString("FPS: " + std::to_string(mStatisticsNumFrames));
		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Application::registerStates()
{
	mStateStack.registerState<States::TitleState>(States::ID::Title);
	mStateStack.registerState<States::MenuState>(States::ID::Menu);
	mStateStack.registerState<States::GameState>(States::ID::Game);
	mStateStack.registerState<States::PauseState>(States::ID::Pause);
	mStateStack.registerState<States::LoadingState>(States::ID::Load);
	mStateStack.registerState<States::TransitionForwardState>(States::ID::TransitionForward);
	mStateStack.registerState<States::TransitionBackwardState>(States::ID::TransitionBackward);
}

void Application::loadRessources()
{
	loadTextures();
	loadFonts();
	loadBitmapFonts();
	loadMaps();
}

void Application::loadTextures()
{
	mTextures.insert(Textures::ID::Player1, std::move(Textures::TextureLoader::load(mBasePath / "Ressources/Graphic/Player/Raiden Fighter Red.png")));
	mTextures.insert(Textures::ID::Player2, std::move(Textures::TextureLoader::load(mBasePath / "Ressources/Graphic/Player/Raiden Fighter Blue.png")));
	mTextures.insert(Textures::ID::Background, std::move(Textures::TextureLoader::load(mBasePath / "Ressources/Graphic/Environment/Level 1.png")));
	mTextures.insert(Textures::ID::GUIButtonBackFrame, std::move(Textures::TextureLoader::load(mBasePath / "Ressources/Graphic/GUI/ButtonBackFrame.png")));
	mTextures.insert(Textures::ID::GUIButtonFrontFrame, std::move(Textures::TextureLoader::load(mBasePath / "Ressources/Graphic/GUI/ButtonFrontFrame.png")));
}

void Application::loadFonts()
{
	mFonts.insert(Fonts::ID::Sansation, std::move(Fonts::FontLoader::load(mBasePath / "Ressources/Font/Sansation.ttf")));
}

void Application::loadBitmapFonts()
{
	mBitmapFonts.insert(Fonts::Bitmaps::ID::Cyan, std::move(Fonts::Bitmaps::FontLoader::load(mBasePath / "Ressources/BitmapFont/Cyan.png")));
	mBitmapFonts.insert(Fonts::Bitmaps::ID::Green, std::move(Fonts::Bitmaps::FontLoader::load(mBasePath / "Ressources/BitmapFont/Green.png")));
	mBitmapFonts.insert(Fonts::Bitmaps::ID::Orange, std::move(Fonts::Bitmaps::FontLoader::load(mBasePath / "Ressources/BitmapFont/Orange.png")));
	mBitmapFonts.insert(Fonts::Bitmaps::ID::Red, std::move(Fonts::Bitmaps::FontLoader::load(mBasePath / "Ressources/BitmapFont/Red.png")));
	mBitmapFonts.insert(Fonts::Bitmaps::ID::White, std::move(Fonts::Bitmaps::FontLoader::load(mBasePath / "Ressources/BitmapFont/White.png")));
	mBitmapFonts.insert(Fonts::Bitmaps::ID::Yellow, std::move(Fonts::Bitmaps::FontLoader::load(mBasePath / "Ressources/BitmapFont/Yellow.png")));
}

void Application::loadMaps()
{
	mMaps.insert(Maps::ID::Title, std::move(Maps::MapLoader::load(mBasePath / "Ressources/Tiled/Map/Title.tmx")));
	mMaps.insert(Maps::ID::Transition, std::move(Maps::MapLoader::load(mBasePath / "Ressources/Tiled/Map/Transition.tmx")));
}

Application::Application(std::filesystem::path const& basePath) :
	mBasePath{ basePath },
	mWindow{ sf::VideoMode(mSize), "SFML Application" },
	mTextures{},
	mFonts{},
	mPlayer{},
	mBitmapFonts{},
	mMaps{},
	mStateStack{ States::State::Context{ mWindow, mTextures, mFonts, mBitmapFonts, mMaps, mPlayer, mBasePath } },
	mStatisticsText{ nullptr },
	mStatisticsUpdateTime{},
	mStatisticsNumFrames{ 0u }
{
	mWindow.setKeyRepeatEnabled(false);
	loadRessources();
	mStatisticsText = std::move(std::make_unique<sf::Text>(mFonts.get(Fonts::ID::Sansation)));

	mStatisticsText->setFont(mFonts.get(Fonts::ID::Sansation));
	mStatisticsText->setPosition({ 5.f, 5.f });
	mStatisticsText->setCharacterSize(10u);
	registerStates();
	mStateStack.pushBackState(States::ID::Load);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate{ sf::Time::Zero };
	while (mWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > mTimePerFrame)
		{
			timeSinceLastUpdate -= mTimePerFrame;
			processEvents();
			update(mTimePerFrame);

			// Check inside this loop, because stack might be empty before update() call
			if (mStateStack.isEmpty())
				mWindow.close();

		}
		updateStatistics(dt);
		render();
	}
}

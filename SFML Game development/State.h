#pragma once

#include <optional>
#include <memory>
#include <filesystem>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "StateIdentifiers.h"
#include "TexturesHolder.h"
#include "FontsHolder.h"
#include "BitmapFontsHolder.h"
#include "MapsHolder.h"
#include "Player.h"

namespace States
{
	class StateStack;

	class State
	{
	public:
		using Ptr = std::unique_ptr<State>;
	public:
		class Context
		{
		private:
		public:
			Context(sf::RenderWindow& window, Textures::TexturesHolder& textures, Fonts::FontsHolder& fonts, Fonts::Bitmaps::FontsHolder& bitmapFonts, Maps::MapsHolder& maps, Player& player, std::filesystem::path const& basePath);
			sf::RenderWindow* window;
			Textures::TexturesHolder* textures;
			Fonts::FontsHolder* fonts;
			Fonts::Bitmaps::FontsHolder* bitmapFonts;
			Maps::MapsHolder* maps;
			Player* player;
			std::filesystem::path basePath;
		};
	private:
		StateStack* mStack;
		Context mContext;
	protected:
		void requestStackPushBack(States::ID stateID);
		void requestStackPushFront(States::ID stateID);
		void requestStackPop();
		void requestStackClear();
		Context getContext() const;
	public:
		State(StateStack& stack, Context context);
		virtual ~State();
		virtual void draw() = 0;
		virtual bool update(sf::Time dt) = 0;
		virtual bool handleEvent(std::optional<sf::Event> const& event) = 0;
	};
}

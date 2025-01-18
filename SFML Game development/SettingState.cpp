#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "SettingState.h"
#include "ToggleButton.h"
#include "Utilities.h"

void States::SettingState::buildButtonAndLabel(Player::Action action, sf::Vector2f const& position, std::string const& text)
{
	mBindingButtons[action] = std::make_shared<GUI::ToggleButton>(text, *getContext().bitmapFonts, *getContext().textures);
	//mBindingButtons[action]->setToggle(true);
	mBindingButtons[action]->setPosition(position);
	mLabels[action] = std::make_shared<GUI::Label>(std::string{}, Fonts::Bitmaps::ID::White, *getContext().bitmapFonts);
	sf::Vector2f labelPosition{ mBindingButtons[action]->getLocalBounds().position };
	sf::Vector2f labelSize{ mLabels[action]->getLocalBounds().size };
	sf::Vector2f buttonSize{ mBindingButtons[action]->getLocalBounds().size };
	labelPosition.x += buttonSize.x + 24.f;
	labelPosition.y = buttonSize.y / 2.f - labelSize.y / 2.f;
	mLabels[action]->setPosition(position + labelPosition);
}

void States::SettingState::updateLabels()
{
	Player& player{ *getContext().player };
	for (size_t i{ 0 };  i<mLabels.size(); ++i)
	{
		sf::Keyboard::Key key{ player.getAssignedKey(static_cast<Player::Action>(i)) };
		mLabels[i]->setText(keyToString(key));
	}
}

States::SettingState::SettingState(StateStack& stack, State::Context context):
	State{ stack, context },
	mGUIcontainer{},
	mBindingButtons{},
	mLabels{},
	mBackgroundMap{ context.maps->get(Maps::ID::Title) }
{
	sf::Vector2f position{ 0.f, 8.f };
	buildButtonAndLabel(Player::Action::MoveLeft, position, "MOVE LEFT");
	buildButtonAndLabel(Player::Action::MoveRight, position + sf::Vector2f{ 0.f, 40.f }, "MOVE RIGHT");
	buildButtonAndLabel(Player::Action::MoveUp, position + sf::Vector2f{ 0.f, 80.f }, "MOVE UP");
	buildButtonAndLabel(Player::Action::MoveDown, position + sf::Vector2f{ 0.f, 120.f }, "MOVE DOWN");
	buildButtonAndLabel(Player::Action::Fire, position + sf::Vector2f{ 0.f, 160.f }, "FIRE");
	buildButtonAndLabel(Player::Action::LaunchMissile, position + sf::Vector2f{ 0.f, 200.f }, "MISSILE");
	updateLabels();
	auto backButton{ std::make_shared<GUI::Button>("BACK", *getContext().bitmapFonts, *getContext().textures) };
	backButton->setPosition(position + sf::Vector2f{ 64.f, 260.f });
	backButton->setCallback([this]()
		{
			requestStackPop();
		});

	for (auto const& button : mBindingButtons)
		mGUIcontainer.pack(button);
	for (auto const& label : mLabels)
		mGUIcontainer.pack(label);
	mGUIcontainer.pack(backButton);
}

void States::SettingState::draw()
{
	sf::RenderWindow& window{ *getContext().window };
	window.setView(window.getDefaultView());
	for (size_t i{ 0 }; i < mBackgroundMap.getLayerCount(); ++i)
		window.draw(mBackgroundMap.getLayer(i));
	window.draw(mGUIcontainer);
}

bool States::SettingState::update(sf::Time dt)
{
	mGUIcontainer.update(dt);
	return false;
}

bool States::SettingState::handleEvent(std::optional<sf::Event> const& event)
{
	bool isKeyBinding{ false };
	for (size_t action{ 0 }; action < Player::Action::ActionsCount; ++action)
	{
		if (mBindingButtons[action]->isActive())
		{
			isKeyBinding = true;
			if (auto keyReleased{ event->getIf<sf::Event::KeyReleased>() })
			{
				getContext().player->assignKey(static_cast<Player::Action>(action), keyReleased->code);
				mBindingButtons[action]->deactivate();
			}
			break;
		}
	}
	if (isKeyBinding)
		updateLabels();
	else
		mGUIcontainer.handleEvent(event);
	return false;
}

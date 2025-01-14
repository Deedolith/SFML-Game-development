#include <SFML/Graphics/RenderWindow.hpp>

#include "LoadingState.h"
#include "Fonts.h"
#include "Utilities.h"

namespace States
{
	void LoadingState::setCompletion(float percent)
	{
		if (percent > 1.f) // clamp
			percent = 1.f;
		mProgressBar.setSize(sf::Vector2f(mProgressBarBackground.getSize().x * percent, mProgressBar.getSize().y));
	}

	LoadingState::LoadingState(StateStack& stack, State::Context context) :
		States::State{ stack, context },
		mLoadingText{ context.fonts->get(Fonts::ID::Sansation), "Loading ressources" },
		mProgressBarBackground{},
		mProgressBar{},
		mLoadingTask{}
	{
		sf::RenderWindow& window{ *getContext().window };
		sf::Vector2f viewSize{ window.getView().getSize() };

		mLoadingText.setCharacterSize(20);
		centerOrigin(mLoadingText);
		mLoadingText.setPosition(sf::Vector2f{ viewSize.x / 2.f, viewSize.y / 2.f + 50.f });

		mProgressBarBackground.setFillColor(sf::Color::White);
		mProgressBarBackground.setSize(sf::Vector2f{ viewSize.x - 20.f, 10.f });
		mProgressBarBackground.setPosition(sf::Vector2f{ 10.f, mLoadingText.getPosition().y + 40.f });

		mProgressBar.setFillColor(sf::Color(100, 100, 100));
		mProgressBar.setSize(sf::Vector2f{ 200.f, 10.f });
		mProgressBar.setPosition(sf::Vector2f{ 10.f, mLoadingText.getPosition().y + 40.f });

		setCompletion(0.f);
		mLoadingTask.execute();
	}

	void LoadingState::draw()
	{
		sf::RenderWindow& window{ *getContext().window };
		window.setView(window.getDefaultView());

		window.draw(mProgressBarBackground);
		window.draw(mProgressBar);
		window.draw(mLoadingText);
	}

	bool LoadingState::update(sf::Time dt)
	{
		if (mLoadingTask.isFinished())
		{
			requestStackPop();
			requestStackPushBack(States::ID::Title);
		}
		else
			setCompletion(mLoadingTask.getCompletion());
		return true;
	}

	bool LoadingState::handleEvent(std::optional<sf::Event> const& event)
	{
		return true;
	}
}

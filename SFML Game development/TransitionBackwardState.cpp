#include <algorithm>

#include <SFML/Graphics/RenderWindow.hpp>

#include "TransitionBackwardState.h"

namespace States
{
	void TransitionBackwardState::updateLayers()
	{
		for (size_t i{ 0 }; i < mMap.getLayerCount(); ++i)
			updateLayer(mMap.getLayer(i), i);
	}

	void TransitionBackwardState::updateLayer(Maps::Map::Layer& layer, size_t index)
	{
		for (size_t i{ 0 }; i < mLayerVisibilities[index].size(); ++i)
		{
			sf::Time duration{ sf::Time::Zero };
			for (auto const& visibility : mLayerVisibilities[index])
			{
				duration += visibility.getDuration();
				if (mElapsedTime < duration)
				{
					layer.setVisible(visibility.getState());
					break;
				}
			}
		}
	}

	States::TransitionBackwardState::TransitionBackwardState(StateStack& stack, State::Context context):
		State{ stack, context },
		mElapsedTime{ sf::Time::Zero },
		mMap{ context.maps->get(Maps::ID::Transition) },
		mLayerVisibilities{},
		mTimePerFrame{ sf::seconds(1.f / 60.f )},
		mDuration{ sf::seconds(mMap.getProperty("Duration").as_float() * mTimePerFrame.asSeconds()) }
	{
		for (unsigned i{ 0 }; i < mMap.getLayerCount(); ++i)
		{
			Maps::Map::Layer& layer{ mMap.getLayer(i) };
			layer.setVisible(true);
			std::string xmlFragment{ layer.getProperty("Durations").as_string() };
			pugi::xml_document property;
			property.load_string(xmlFragment.c_str());
			auto items{ property.select_nodes("//item") };
			std::vector<Visibility> visibilities{};
			for (auto const& item : items)
			{
				bool visible{ item.node().attribute("visible").as_bool() };
				sf::Time duration{ sf::seconds(item.node().attribute("frames").as_float() * mTimePerFrame.asSeconds()) };
				visibilities.push_back(Visibility{ visible, duration });
				std::reverse(visibilities.begin(), visibilities.end());
			}
			mLayerVisibilities.push_back(visibilities);
		}
	}

	void TransitionBackwardState::draw()
	{
		sf::RenderWindow& window{ *getContext().window };
		window.setView(window.getDefaultView());
		for (size_t i{ 0 }; i < mMap.getLayerCount(); ++i)
			window.draw(mMap.getLayer(i));
	}

	bool TransitionBackwardState::update(sf::Time dt)
	{
		mElapsedTime += dt;
		if (mElapsedTime >= mDuration)
			requestStackPop();
		else
			updateLayers();
		return true;
	}

	bool TransitionBackwardState::handleEvent(std::optional<sf::Event> const& event)
	{
		return false;
	}
}
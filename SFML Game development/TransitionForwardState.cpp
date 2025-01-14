#include <string>

#include "TransitionForwardState.h"

namespace States
{
	void TransitionForwardState::updateLayers()
	{
		for (size_t i{ 0 }; i < mMap.getLayerCount(); ++i)
			updateLayer(mMap.getLayer(i), i);
	}
	void TransitionForwardState::updateLayer(Maps::Map::Layer& layer, size_t index)
	{
		for (size_t i{ 0 }; i < mLayerVisibilities[index].size(); ++i)
		{
			std::chrono::milliseconds duration{ std::chrono::milliseconds::zero() };
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
	TransitionForwardState::TransitionForwardState(StateStack& stack, State::Context context) :
		State{ stack, context },
		mElapsedTime{ sf::Time::Zero },
		mMap{ context.maps->get(Maps::ID::Transition) },
		mLayerVisibilities{}
	{
		for (unsigned i{ 0 }; i < mMap.getLayerCount(); ++i)
		{
			Maps::Map::Layer& layer{ mMap.getLayer(i) };
			std::string xmlFragment{ layer.getProperty("Durations").as_string() };
			pugi::xml_document property;
			property.load_string(xmlFragment.c_str());
			auto items{ property.select_nodes("//item") };
			std::vector<Visibility> visibilities{};
			for (auto const& item : items)
			{
				bool visible{ item.node().attribute("visible").as_bool()};
				unsigned duration{ item.node().attribute("duration").as_uint()};
				visibilities.push_back(Visibility{ visible, duration });
			}
			mLayerVisibilities.push_back(visibilities);
		}
	}

	void TransitionForwardState::draw()
	{
		sf::RenderWindow& window{ *getContext().window };
		window.setView(window.getDefaultView());
		for (size_t i{ 0 }; i < mMap.getLayerCount(); ++i)
			window.draw(mMap.getLayer(i));
	}

	bool TransitionForwardState::update(sf::Time dt)
	{
		mElapsedTime += dt;
		std::chrono::milliseconds duration{ mMap.getProperty("Duration").as_uint() };
		if (mElapsedTime >= duration)
		{
			requestStackPop();
			requestStackPop();
			requestStackPushBack(States::ID::TransitionBackward);
		}
		else
			updateLayers();
		return false;
	}

	bool TransitionForwardState::handleEvent(std::optional<sf::Event> const& event)
	{
		return false;
	}
}
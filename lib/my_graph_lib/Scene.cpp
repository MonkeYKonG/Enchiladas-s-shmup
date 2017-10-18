#include "Scene.hpp"

namespace	my
{
	void Scene::PollEvents(sf::RenderWindow & window) noexcept
	{
		sf::Event event;

		m_events.clear();
		while (window.pollEvent(event))
			m_events.push_back(event);
	}
}
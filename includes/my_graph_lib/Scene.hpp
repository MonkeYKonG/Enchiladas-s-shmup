#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "SceneReturnValue.hh"

namespace	my
{
	class 	Scene : public sf::Drawable, public sf::Transformable
	{
	public:
		virtual ~Scene(){}
		
		virtual const SceneReturnValue& Update(const sf::RenderWindow & window) = 0;
		virtual void Initialize() = 0;
		virtual void Reset() = 0;

	protected:
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const = 0;
		void PollEvents(sf::RenderWindow & window);

		std::vector<sf::Event>	m_events;
	};

	typedef std::shared_ptr<Scene> ScenePtr;
}
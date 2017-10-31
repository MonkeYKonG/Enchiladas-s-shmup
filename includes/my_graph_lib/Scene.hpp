#pragma once

#include <exception>
#include <memory>
#include <SFML/Graphics.hpp>
#include "SceneReturnValue.hh"
#include "XMLNode.hpp"

namespace	my
{
	class 	Scene : public sf::Drawable, public sf::Transformable
	{
	public:
		typedef std::shared_ptr<Scene> ScenePtr;

		virtual ~Scene() noexcept {}
		
		virtual const SceneReturnValue Update(sf::RenderWindow & window) throw (std::exception) = 0;
		virtual void Initialize(XMLNode::XMLNodePtr sceneRoot) noexcept = 0;
		virtual void Reset() noexcept = 0;

	protected:
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const = 0;
		void PollEvents(sf::RenderWindow & window) noexcept;

		std::vector<sf::Event>	m_events;
	};
}
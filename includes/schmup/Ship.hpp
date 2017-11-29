#pragma once

#include "my_graph_lib/Node.hpp"
#include "ShipModule.hpp"

namespace my
{
	namespace schmup
	{
		class Ship : public Node
		{
		public:
			typedef std::list<ShipModule::ShipModulePtr> ShipModuleList;

			virtual bool IsIntersect(const sf::Vector2f & point) const noexcept;
			virtual bool IsIntersect(const sf::FloatRect & square) const noexcept;
			virtual const sf::FloatRect GetHitBox() const noexcept;

			void AddModule(ShipModule::ShipModulePtr newModule) noexcept;

		private:
			virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept;

			ShipModuleList m_modules;
		};
	}
}
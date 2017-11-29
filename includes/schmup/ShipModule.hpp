#pragma once

#include "my_graph_lib/SpriteObject.hpp"
#include "my_objects_lib/AliveObject.hpp"

namespace my
{
	namespace schmup
	{
		class ShipModule : public SpriteObject, public AliveObject
		{
		public:
			typedef std::shared_ptr<ShipModule> ShipModulePtr;

			ShipModule();
			virtual ~ShipModule();

			const sf::Vector2i GetShipPosition() const noexcept;
			void SetShipPosition(const sf::Vector2i & shipPosition) noexcept;

		protected:
			unsigned m_regenFramerate;
			unsigned m_regenCurFramerate;
			sf::Vector2i m_shipPosition;
		};
	}
}
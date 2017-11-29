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

		protected:
			unsigned m_regenFramerate;
			unsigned m_regenCurFramerate;
		};
	}
}
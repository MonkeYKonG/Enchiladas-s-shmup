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

		private:
			ShipModuleList m_modules;
		};
	}
}
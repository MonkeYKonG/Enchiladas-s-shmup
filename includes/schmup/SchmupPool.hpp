#pragma once

#include "my_objects_lib/ObjectPool.hpp"
#include "ShipModule.hpp"

namespace my
{
	namespace schmup
	{
		class SchmupPool : public ObjectPool
		{
		public:
			static ShipModule::ShipModulePtr CreateShipModule(XMLNode::XMLNodePtr shipModuleNode) throw(std::out_of_range, std::invalid_argument);

		private:
			SchmupPool();
			~SchmupPool();
		};
	}
}
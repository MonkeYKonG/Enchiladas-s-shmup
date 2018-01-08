#pragma once

#include <memory>
#include "my_graph_lib/XMLNode.hpp"
#include "my_graph_lib/SpriteObject.hpp"
#include "my_objects_lib/AliveObject.hpp"

namespace my
{
	namespace schmup
	{
		class Module : public AliveObject, public SpriteObject
		{
		public:
			typedef std::shared_ptr<Module> ModulePtr;

			virtual ~Module() {}

			ModulePtr Create(XMLNode::XMLNodePtr moduleNode) throw (std::out_of_range, std::invalid_argument);

		protected:

		private:
			Module();
		};
	}
}
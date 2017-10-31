#pragma once

#include "my_graph_lib/GameManager.hpp"

namespace	my
{
	namespace	schmup
	{
		class SchmupGameManager : public GameManager
		{
		public:
			SchmupGameManager();
			~SchmupGameManager();

		private:
			void	InitializeScenes(XMLNode::XMLNodePtr scenesRoot) throw (std::out_of_range, std::invalid_argument);
		};
	}
}
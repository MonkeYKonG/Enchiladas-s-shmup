#pragma once

#include "my_graph_lib/Scene.hpp"

namespace	my
{
	namespace schmup
	{
		class ScenePool
		{
		public:
			static Scene::ScenePtr CreateScene(const std::string & className);
		
		private:
			typedef Scene::ScenePtr (*createSceneFunction)();
			typedef std::pair<const std::string, createSceneFunction> FunctionsIndexs;

			static const unsigned			CLASS_NAMES_NBR = 2;
			static const std::string		MAINMENU_CLASS_NAME;
			static const std::string		SCHMUP_CLASS_NAME;
			static const FunctionsIndexs	CLASS_NAMES[CLASS_NAMES_NBR];

			ScenePool();
			~ScenePool();
			
			static Scene::ScenePtr CreateMainMenu();
			static Scene::ScenePtr CreateSchmup();
		};
	}
}
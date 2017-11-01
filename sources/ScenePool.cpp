#include "ScenePool.hpp"
#include "my_menu_lib/MainMenu.hpp"

namespace	my
{
	namespace	schmup
	{
		const std::string ScenePool::MAINMENU_CLASS_NAME = "MainMenu";
		const ScenePool::FunctionsIndexs ScenePool::CLASS_NAMES[1] = 
		{ 
			ScenePool::FunctionsIndexs(ScenePool::MAINMENU_CLASS_NAME, &ScenePool::CreateMainMenu)
		};

		Scene::ScenePtr ScenePool::CreateMainMenu()
		{
			return (Scene::ScenePtr(new MainMenu()));
		}

		Scene::ScenePtr	ScenePool::CreateScene(const std::string & className)
		{
			for (unsigned i = 0; i < CLASS_NAMES_NBR; ++i)
				if (CLASS_NAMES[i].first == className)
					return (CLASS_NAMES[i].second());
			return (0);
		}
	}
}
#include "ScenePool.hpp"
#include "SchmupMainMenu.hpp"
#include "SchmupMainGame.hpp"

namespace	my
{
	namespace	schmup
	{
		const std::string ScenePool::MAINMENU_CLASS_NAME = "MainMenu";
		const std::string ScenePool::SCHMUP_CLASS_NAME = "Schmup";
		const ScenePool::FunctionsIndexs ScenePool::CLASS_NAMES[ScenePool::CLASS_NAMES_NBR] = 
		{ 
			ScenePool::FunctionsIndexs(ScenePool::MAINMENU_CLASS_NAME, &ScenePool::CreateMainMenu),
			ScenePool::FunctionsIndexs(ScenePool::SCHMUP_CLASS_NAME, &ScenePool::CreateSchmup)
		};

		Scene::ScenePtr ScenePool::CreateMainMenu()
		{
			return (Scene::ScenePtr(new SchmupMainMenu()));
		}

		Scene::ScenePtr my::schmup::ScenePool::CreateSchmup()
		{
			return (Scene::ScenePtr(new SchmupMainGame()));
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
#include "SchmupGameManager.hpp"
#include "my_menu_lib/MainMenu.hpp"
#include "ScenePool.hpp"
#include <iostream>

namespace	my
{
	namespace schmup
	{
		const std::string	SchmupGameManager::SCENE_CLASS_ARGUMENT = "class";
		const std::string	SchmupGameManager::SCENE_MAINMENU_CLASS = "MainMenu";

		SchmupGameManager::SchmupGameManager()
		{}

		SchmupGameManager::~SchmupGameManager()
		{}

		void	SchmupGameManager::InitializeScenes(XMLNode::XMLNodePtr scenesRoot) throw (std::out_of_range, std::invalid_argument)
		{
			std::string	stkClass;

			if (!scenesRoot)
				throw (std::invalid_argument("scenesRoot is null"));
			try
			{
				for (unsigned i = 0; i < scenesRoot->GetChilds().size(); ++i)
				{
					Scene::ScenePtr newScene = ScenePool::CreateScene(scenesRoot->GetChilds()[i]->GetContent(SCENE_CLASS_ARGUMENT).second);
					if (!newScene)
						throw (std::invalid_argument("unknow scene class"));
					newScene->Initialize(scenesRoot->GetChilds()[i]);
					m_window.scenes.push_back(newScene);
				}
			}
			catch (const std::out_of_range & e)
			{
				throw (e);
			}
			catch (const std::invalid_argument & e)
			{
				throw (e);
			}
		}
	}
}
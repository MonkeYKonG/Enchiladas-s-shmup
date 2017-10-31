#include "SchmupGameManager.hpp"
#include "my_menu_lib/MainMenu.hpp"
#include <iostream>

namespace	my
{
	namespace schmup
	{
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
					if ((stkClass = scenesRoot->GetChilds()[i]->GetContent("class").second) == "MainMenu")
						m_window.scenes.push_back(Scene::ScenePtr(new MainMenu()));
					else
						throw (std::invalid_argument("unknow scene class"));
					m_window.scenes.back()->Initialize(scenesRoot->GetChilds()[i]);
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
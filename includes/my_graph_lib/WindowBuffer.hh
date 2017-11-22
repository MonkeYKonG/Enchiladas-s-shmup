#pragma once

#include "Scene.hpp"

namespace	my
{
  //! Fenêtre de rendu. Contient les différentes scènes du jeu.
	struct  WindowBuffer : public sf::RenderWindow
	{
		typedef std::shared_ptr<WindowBuffer> WindowBufferPtr;

	  //! Tableau de scenes
		std::vector<Scene::ScenePtr>	scenes;
	  //! index de la scène courante
		int								curScene;
	};
}

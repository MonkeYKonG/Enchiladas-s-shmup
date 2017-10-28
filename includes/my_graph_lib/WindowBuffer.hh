#pragma once

#include "Scene.hpp"

namespace	my
{
	struct  WindowBuffer : public sf::RenderWindow
	{
		typedef std::shared_ptr<WindowBuffer> WindowBufferPtr;

		std::vector<Scene::ScenePtr>	scenes;
		int								curScene;
	};
}
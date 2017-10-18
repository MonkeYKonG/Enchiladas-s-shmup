#pragma once

#include "Scene.hpp"

namespace	my
{
	struct  WindowBuffer
	{
		typedef std::shared_ptr<WindowBuffer> WindowBufferPtr;

		sf::Vector2u					windowSize;
		unsigned						bitsPerPixel;
		sf::RenderWindow				window;
		std::vector<Scene::ScenePtr>	scenes;
		int								curScene;
	};
}
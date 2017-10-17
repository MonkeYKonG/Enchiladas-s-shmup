#pragma once

#include "Scene.hpp"

namespace	my
{
	struct  WindowBuffer
	{
		sf::Vector2u			windowSize;
		unsigned				bitsPerPixel;
		sf::RenderWindow		window;
		std::vector<ScenePtr>	scenes;
		int						curScene;
	};

	typedef std::shared_ptr<WindowBuffer> WindowBufferPtr;
}
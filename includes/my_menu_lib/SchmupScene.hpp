#pragma once

#include "my_graph_lib/Scene.hpp"

namespace my
{
	class SchmupScene : public Scene
	{
	public:
		SchmupScene();
		virtual ~SchmupScene() {}

		const SceneReturnValue Update(sf::RenderWindow & window) throw (std::exception) = 0;
		void Initialize(XMLNode::XMLNodePtr sceneRoot) throw (std::out_of_range, std::invalid_argument) = 0;
		void Reset() throw(std::out_of_range, std::invalid_argument) = 0;

	private:

	};
}
#pragma once

#include "my_graph_lib/Scene.hpp"
#include "my_graph_lib/SpriteObject.hpp"
#include "my_graph_lib/TextObject.hpp"

namespace	my
{
	class MainMenu : public Scene
	{
	public:
		MainMenu();
		~MainMenu();

		const SceneReturnValue	Update(sf::RenderWindow & window) throw (std::exception);
		void Initialize(XMLNode::XMLNodePtr sceneRoot) throw (std::out_of_range, std::invalid_argument);
		void Reset() throw (std::out_of_range, std::invalid_argument);

	private:
		static const std::string	SCENE_BACKGROUND_NODE;

		void draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept;

		SpriteObject::SpriteObjectPtr m_background;
		XMLNode::XMLNodePtr m_root;
	};
}
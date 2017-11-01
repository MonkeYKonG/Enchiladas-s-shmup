#pragma once

#include "my_graph_lib/Scene.hpp"
#include "my_graph_lib/SpriteObject.hpp"
#include "my_graph_lib/TextObject.hpp"
#include "my_objects_lib/Panel.hpp"

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
		typedef void (MainMenu::*InitializationFunction)(XMLNode::XMLNodePtr);
		typedef std::pair<std::string, InitializationFunction> InitFunctionPair;

		static const std::string	SCENE_BACKGROUND_NODE;
		static const std::string	SCENE_PANEL_NODE;

		void draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept;

		void InitializeFunctions() noexcept;
		void InitializeBackground(XMLNode::XMLNodePtr backgroundNode) throw (std::out_of_range, std::invalid_argument);
		void InitializePanel(XMLNode::XMLNodePtr panelNode) throw (std::out_of_range, std::invalid_argument);

		SpriteObject::SpriteObjectPtr m_background;
		std::vector<Panel::PanelPtr> m_panels;
		XMLNode::XMLNodePtr m_root;
		std::vector<InitFunctionPair> m_initializationFunctions;
	};
}
#pragma once

#include "my_graph_lib/Scene.hpp"
#include "my_graph_lib/SpriteObject.hpp"
#include "my_graph_lib/TextObject.hpp"
#include "my_objects_lib/Panel.hpp"
#include "my_objects_lib/Cursor.hpp"

namespace	my
{
	class MainMenu : public Scene
	{
	public:
		MainMenu();
		virtual ~MainMenu() {}

		virtual const SceneReturnValue	Update(const sf::Vector2i & mousePos) throw (std::exception);
		virtual void Initialize(XMLNode::XMLNodePtr sceneRoot) throw (std::out_of_range, std::invalid_argument);
		virtual void Reset() throw (std::out_of_range, std::invalid_argument);

	protected:
		typedef void (MainMenu::*InitializationFunction)(XMLNode::XMLNodePtr);
		typedef std::pair<std::string, InitializationFunction> InitFunctionPair;

		static const std::string	SCENE_CURSOR_NODE;
		static const std::string	SCENE_BACKGROUND_NODE;
		static const std::string	SCENE_PANEL_NODE;

		void draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept;

		void InitializeFunctions() noexcept;
		void InitializeCursor(XMLNode::XMLNodePtr cursorNode) throw (std::out_of_range, std::invalid_argument);
		void InitializeBackground(XMLNode::XMLNodePtr backgroundNode) throw (std::out_of_range, std::invalid_argument);
		void InitializePanel(XMLNode::XMLNodePtr panelNode) throw (std::out_of_range, std::invalid_argument);

		void UpdateObjects(const sf::Vector2i & mousePos) throw (std::out_of_range);

		SpriteObject::SpriteObjectPtr m_background;
		std::vector<Panel::PanelPtr> m_panels;
		Cursor::CursorPtr m_cursor;
		XMLNode::XMLNodePtr m_root;
		std::vector<InitFunctionPair> m_initializationFunctions;
	};
}
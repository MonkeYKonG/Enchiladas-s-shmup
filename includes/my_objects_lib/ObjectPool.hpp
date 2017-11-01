#pragma once

#include "my_graph_lib/SpriteObject.hpp"
#include "my_graph_lib/XMLNode.hpp"
#include "my_objects_lib/Panel.hpp"

namespace	my
{
	class ObjectPool
	{
	public:
		static SpriteObject::SpriteObjectPtr CreateSprite(XMLNode::XMLNodePtr spriteNode) throw (std::out_of_range, std::invalid_argument);
		static TextObject::TextObjectPtr CreateText(XMLNode::XMLNodePtr textNode) throw (std::out_of_range, std::invalid_argument);
		static Panel::PanelPtr CreatePanel(XMLNode::XMLNodePtr panelNode) throw (std::out_of_range, std::invalid_argument);
	
	private:
		typedef SpriteObject::SpriteObjectPtr (*CreateSpriteFunctions)(XMLNode::XMLNodePtr spriteNode);
		typedef std::pair<const std::string, CreateSpriteFunctions> CreateSpriteFunctionsIndexs;

		static const unsigned		SPRITE_OBJECT_CLASS_NBR = 1;
		static const std::string	SPRITE_BACKGROUND_CLASS_NAME;
		static const CreateSpriteFunctionsIndexs CREATE_SPRITE_INDEXS[SPRITE_OBJECT_CLASS_NBR];

		static const std::string	PANEL_BACKGROUND_NODE_NAME;
		static const std::string	PANEL_TITLE_NODE_NAME;
		static const std::string	PANEL_BORDER_NODE_NAME;

		static const std::string	TEXT_FONT_NODE_NAME;
		static const std::string	TEXT_SPRITE_NODE_NAME;
		static const std::string	TEXT_COLOR_NODE_NAME;
		static const std::string	TEXT_CHARSIZE_NODE_NAME;

		static const std::string	COLOR_RED_CONTENT_NAME;
		static const std::string	COLOR_GREEN_CONTENT_NAME;
		static const std::string	COLOR_BLUE_CONTENT_NAME;
		static const std::string	COLOR_ALPHA_CONTENT_NAME;

		ObjectPool();
		~ObjectPool();

		static sf::Color CreateColor(XMLNode::XMLNodePtr colorNode) throw (std::out_of_range, std::invalid_argument);

		static SpriteObject::SpriteObjectPtr CreateBackground(XMLNode::XMLNodePtr backgroundNode) throw (std::out_of_range, std::invalid_argument);
	};
}
#pragma once

#include "my_graph_lib/SpriteObject.hpp"
#include "my_graph_lib/XMLNode.hpp"
#include "my_objects_lib/Panel.hpp"
#include "Cursor.hpp"
#include "SpriteButton.hpp"
#include "Player.hpp"

namespace	my
{
	class ObjectPool
	{
	public:
		static SpriteObject::SpriteObjectPtr CreateSprite(XMLNode::XMLNodePtr spriteNode) throw (std::out_of_range, std::invalid_argument);
		static TextObject::TextObjectPtr CreateText(XMLNode::XMLNodePtr textNode) throw (std::out_of_range, std::invalid_argument);
		static Border::BorderPtr CreateBorder(XMLNode::XMLNodePtr borderNode) throw (std::out_of_range, std::invalid_argument);
		static Panel::PanelPtr CreatePanel(XMLNode::XMLNodePtr panelNode) throw (std::out_of_range, std::invalid_argument);
		static Cursor::CursorPtr CreateCursor(XMLNode::XMLNodePtr cursorNode) throw (std::out_of_range, std::invalid_argument);
		static SpriteButton::SpriteButtonPtr CreateSpriteButton(XMLNode::XMLNodePtr spriteButtonNode) throw (std::out_of_range, std::invalid_argument);
		static Player::PlayerPtr CreatePlayer(XMLNode::XMLNodePtr playerNode) throw (std::out_of_range, std::invalid_argument);

		static sf::Keyboard::Key StrToInput(const std::string & str) throw (std::invalid_argument);
		static Direction StrToDirection(const std::string & str) throw (std::invalid_argument);
	
	private:
		typedef SpriteObject::SpriteObjectPtr (*CreateSpriteFunctions)(XMLNode::XMLNodePtr spriteNode);
		typedef std::pair<const std::string, CreateSpriteFunctions> CreateSpriteFunctionsIndexs;

		static const unsigned		SPRITE_OBJECT_CLASS_NBR = 1;
		static const std::string	SPRITE_BACKGROUND_CLASS_NAME;
		static const CreateSpriteFunctionsIndexs CREATE_SPRITE_INDEXS[SPRITE_OBJECT_CLASS_NBR];

		static const std::string	PANEL_BACKGROUND_NODE_NAME;
		static const std::string	PANEL_TITLE_NODE_NAME;
		static const std::string	PANEL_BORDER_NODE_NAME;
		static const std::string	PANEL_BUTTONS_NODE_NAME;
		static const std::string	PANEL_SPRITE_BUTTONS_NODE_CONTENT_VALUE;
		static const std::string	PANEL_TEXT_BUTTONS_NODE_CONTENT_VALUE;

		static const std::string	TEXT_FONT_NODE_NAME;
		static const std::string	TEXT_SPRITE_NODE_NAME;
		static const std::string	TEXT_COLOR_NODE_NAME;
		static const std::string	TEXT_CHARSIZE_NODE_NAME;

		static const std::string	BORDER_OUTLINE_NODE_NAME;
		static const std::string	BORDER_CORNER_NODE_NAME;

		static const std::string	COLOR_RED_CONTENT_NAME;
		static const std::string	COLOR_GREEN_CONTENT_NAME;
		static const std::string	COLOR_BLUE_CONTENT_NAME;
		static const std::string	COLOR_ALPHA_CONTENT_NAME;

		static const std::string	ANIMATION_RECTS_NODE_NAME;
		static const std::string	ANIMATION_FRAMERATE_NODE_NAME;
		static const std::string	ANIMATION_LOOP_NODE_NAME;

		static const std::string	OBJECT_TEXTURE_NODE_NAME;
		static const std::string	OBJECT_ANIMATIONS_NODE_NAME;

		static const std::string	PLAYER_INPUTS_NODE_NAME;

		static const std::string	HEIGHT_NODE_CONTENT;
		static const std::string	WIDTH_NODE_CONTENT;
		static const std::string	X_NODE_CONTENT;
		static const std::string	Y_NODE_CONTENT;
		static const std::string	TILE_HEIGHT_NODE_CONTENT;
		static const std::string	TILE_WIDTH_NODE_CONTENT;
		static const std::string	CLASS_NODE_CONTENT;
		static const std::string	KEY_NODE_CONTENT;
		static const std::string	INPUT_NODE_CONTENT;
		static const std::string	DIRECTION_NODE_CONTENT;

		ObjectPool();
		~ObjectPool() {}

		static void SetSpriteDefaults(XMLNode::XMLNodePtr spriteNode, SpriteObject * sprite) throw (std::out_of_range, std::invalid_argument);

		static bool CreateBoolean(XMLNode::XMLNodePtr boolNode) throw (std::out_of_range, std::invalid_argument);
		static sf::Color CreateColor(XMLNode::XMLNodePtr colorNode) throw (std::out_of_range, std::invalid_argument);
		static AnimatedObject::Animation CreateAnimation(XMLNode::XMLNodePtr animationNode) throw (std::out_of_range, std::invalid_argument);
		static Player::InputPair CreateInput(XMLNode::XMLNodePtr inputNode) throw (std::out_of_range, std::invalid_argument);

		static SpriteObject::SpriteObjectPtr CreateBackground(XMLNode::XMLNodePtr backgroundNode) throw (std::out_of_range, std::invalid_argument);
	};
}
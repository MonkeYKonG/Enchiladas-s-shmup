#include "ObjectPool.hpp"
#include "Border.hpp"
#include "my_graph_lib/ResourcesLoader.hpp"

namespace	my
{
	const std::string	ObjectPool::SPRITE_BACKGROUND_CLASS_NAME = "background";
	const ObjectPool::CreateSpriteFunctionsIndexs ObjectPool::CREATE_SPRITE_INDEXS[ObjectPool::SPRITE_OBJECT_CLASS_NBR] =
	{
		ObjectPool::CreateSpriteFunctionsIndexs(ObjectPool::SPRITE_BACKGROUND_CLASS_NAME, &ObjectPool::CreateBackground)
	};

	const std::string	ObjectPool::PANEL_BACKGROUND_NODE_NAME = "background";
	const std::string 	ObjectPool::PANEL_TITLE_NODE_NAME = "title";
	const std::string 	ObjectPool::PANEL_BORDER_NODE_NAME = "border";
	const std::string 	ObjectPool::PANEL_BUTTONS_NODE_NAME = "buttons";
	const std::string 	ObjectPool::PANEL_SPRITE_BUTTONS_NODE_CONTENT_VALUE = "sprite";
	const std::string 	ObjectPool::PANEL_TEXT_BUTTONS_NODE_CONTENT_VALUE = "text";

	const std::string 	ObjectPool::TEXT_FONT_NODE_NAME = "font";
	const std::string 	ObjectPool::TEXT_SPRITE_NODE_NAME = "text";
	const std::string 	ObjectPool::TEXT_COLOR_NODE_NAME = "color";
	const std::string 	ObjectPool::TEXT_CHARSIZE_NODE_NAME = "charSize";

	const std::string	ObjectPool::BORDER_OUTLINE_NODE_NAME = "outline";
	const std::string	ObjectPool::BORDER_CORNER_NODE_NAME = "corner";

	const std::string 	ObjectPool::COLOR_RED_CONTENT_NAME = "red";
	const std::string 	ObjectPool::COLOR_GREEN_CONTENT_NAME = "green";
	const std::string 	ObjectPool::COLOR_BLUE_CONTENT_NAME = "blue";
	const std::string 	ObjectPool::COLOR_ALPHA_CONTENT_NAME = "alpha";

	const std::string	ObjectPool::ANIMATION_RECTS_NODE_NAME = "rects";
	const std::string	ObjectPool::ANIMATION_FRAMERATE_NODE_NAME = "framerateMax";
	const std::string	ObjectPool::ANIMATION_LOOP_NODE_NAME = "loop";

	const std::string	ObjectPool::OBJECT_TEXTURE_NODE_NAME = "texture";
	const std::string	ObjectPool::OBJECT_ANIMATIONS_NODE_NAME = "animations";

	const std::string	ObjectPool::PLAYER_INPUTS_NODE_NAME = "inputs";

	const std::string 	ObjectPool::HEIGHT_NODE_CONTENT = "height";
	const std::string 	ObjectPool::WIDTH_NODE_CONTENT = "width";
	const std::string 	ObjectPool::X_NODE_CONTENT = "x";
	const std::string 	ObjectPool::Y_NODE_CONTENT = "y";
	const std::string 	ObjectPool::TILE_WIDTH_NODE_CONTENT = "tileX";
	const std::string 	ObjectPool::TILE_HEIGHT_NODE_CONTENT = "tileY";
	const std::string 	ObjectPool::CLASS_NODE_CONTENT = "class";
	const std::string 	ObjectPool::KEY_NODE_CONTENT = "key";
	const std::string 	ObjectPool::INPUT_NODE_CONTENT = "input";
	const std::string 	ObjectPool::DIRECTION_NODE_CONTENT = "direction";

	void ObjectPool::SetSpriteDefaults(XMLNode::XMLNodePtr spriteNode, SpriteObject * sprite) throw(std::out_of_range, std::invalid_argument)
	{
		XMLNode::XMLNodePtr childStk;

		if (!sprite)
			throw (std::invalid_argument("ObjectPool: SetSpriteDefaults: null sprite"));
		if (!spriteNode)
			throw (std::invalid_argument("ObjectPool: SetSpriteDefaults: null node"));
		try
		{
			sprite->SetTexture(ResourcesLoader::GetTexture(spriteNode->GetChild(OBJECT_TEXTURE_NODE_NAME)->GetValue()));
			if (spriteNode->ChildExist(OBJECT_ANIMATIONS_NODE_NAME))
			{
				childStk = spriteNode->GetChild(OBJECT_ANIMATIONS_NODE_NAME);
				for (unsigned i = 0; i < childStk->GetChilds().size(); ++i)
					sprite->AddAnimation(CreateAnimation(childStk->GetChilds()[i]));
			}
			if (spriteNode->ContentExist(X_NODE_CONTENT) && spriteNode->ContentExist(Y_NODE_CONTENT))
				sprite->setPosition(std::stoul(spriteNode->GetContent(X_NODE_CONTENT).second), std::stoul(spriteNode->GetContent(Y_NODE_CONTENT).second));
		}
		catch (const std::out_of_range & e)
		{
			throw (e);
		}
		catch (const std::invalid_argument & e)
		{
			throw (e);
		}
	}

	bool		ObjectPool::CreateBoolean(XMLNode::XMLNodePtr boolNode) throw (std::out_of_range, std::invalid_argument)
	{
		if (!boolNode)
			throw (std::invalid_argument("CreateBoolean: null node"));
		try
		{
			if (boolNode->GetValue() == "true")
				return (true);
			if (boolNode->GetValue() == "false")
				return (false);
		}
		catch (const std::out_of_range & e)
		{
			throw (e);
		}
		catch (const std::invalid_argument & e)
		{
			throw (e);
		}
		throw (std::invalid_argument("CreateBool: invalid value: " + boolNode->GetValue()));
	}

	sf::Color 	ObjectPool::CreateColor(XMLNode::XMLNodePtr colorNode) throw (std::out_of_range, std::invalid_argument)
	{
		sf::Color newColor;

		if (!colorNode)
			throw (std::invalid_argument("CreateColor: null node"));
		try
		{
			newColor.r = std::stoul(colorNode->GetContent(COLOR_RED_CONTENT_NAME).second);
			newColor.g = std::stoul(colorNode->GetContent(COLOR_GREEN_CONTENT_NAME).second);
			newColor.b = std::stoul(colorNode->GetContent(COLOR_BLUE_CONTENT_NAME).second);
			if (colorNode->ContentExist(COLOR_ALPHA_CONTENT_NAME))
				newColor.b = std::stoul(colorNode->GetContent(COLOR_ALPHA_CONTENT_NAME).second);
		}
		catch (const std::out_of_range & e)
		{
			throw (e);
		}
		catch (const std::invalid_argument & e)
		{
			throw (e);
		}
		return (newColor);
	}

	AnimatedObject::Animation	ObjectPool::CreateAnimation(XMLNode::XMLNodePtr animationNode)
	{
		XMLNode::XMLNodePtr childStk;
		AnimatedObject::Animation newAnimation;

		if (!animationNode)
			throw (std::invalid_argument("CreateAnimation: null node"));
		try
		{
			newAnimation.key = animationNode->GetContent(KEY_NODE_CONTENT).second;
			childStk = animationNode->GetChild(ANIMATION_RECTS_NODE_NAME);
			for (unsigned i = 0; i < childStk->GetChilds().size(); ++i)
				newAnimation.rects.push_back(sf::IntRect(std::stoul(childStk->GetChilds()[i]->GetContent(X_NODE_CONTENT).second), std::stoul(childStk->GetChilds()[i]->GetContent(Y_NODE_CONTENT).second), std::stoul(childStk->GetChilds()[i]->GetContent(TILE_WIDTH_NODE_CONTENT).second), std::stoul(childStk->GetChilds()[i]->GetContent(TILE_HEIGHT_NODE_CONTENT).second)));
			if (animationNode->ChildExist(ANIMATION_FRAMERATE_NODE_NAME))
				newAnimation.framerateMax = std::stoul(animationNode->GetChild(ANIMATION_FRAMERATE_NODE_NAME)->GetValue());
			if (animationNode->ChildExist(ANIMATION_LOOP_NODE_NAME))
				newAnimation.loop = CreateBoolean(animationNode->GetChild(ANIMATION_LOOP_NODE_NAME));
		}
		catch (const std::out_of_range & e)
		{
			throw (e);
		}
		catch (const std::invalid_argument & e)
		{
			throw (e);
		}
		return (newAnimation);
	}

	Player::InputPair ObjectPool::CreateInput(XMLNode::XMLNodePtr inputNode) throw(std::out_of_range, std::invalid_argument)
	{
		Player::InputPair newInput;

		try
		{
			newInput.first = StrToInput(inputNode->GetContent(INPUT_NODE_CONTENT).second);
			newInput.second = StrToDirection(inputNode->GetContent(DIRECTION_NODE_CONTENT).second);
		}
		catch (const std::out_of_range & e)
		{
			throw (e);
		}
		catch (const std::invalid_argument & e)
		{
			throw (e);
		}
		return (newInput);
	}

	SpriteObject::SpriteObjectPtr ObjectPool::CreateBackground(XMLNode::XMLNodePtr backgroundNode) throw (std::out_of_range, std::invalid_argument)
	{
		SpriteObject::SpriteObjectPtr	newBackground;

		if (!backgroundNode)
			throw (std::invalid_argument("CreateBackgtound: null ptr"));
		newBackground = SpriteObject::SpriteObjectPtr(new SpriteObject());
		try
		{
			SetSpriteDefaults(backgroundNode, &(*newBackground));
			newBackground->SetOrigin(newBackground->GetSprite().getGlobalBounds().width / 2, newBackground->GetSprite().getGlobalBounds().height / 2);
		}
		catch (const std::out_of_range & e)
		{
			throw (e);
		}
		catch (const std::invalid_argument & e)
		{
			throw (e);
		}
		return (newBackground);
	}

	SpriteObject::SpriteObjectPtr ObjectPool::CreateSprite(XMLNode::XMLNodePtr spriteNode) throw (std::out_of_range, std::invalid_argument)
	{
		if (!spriteNode)
			throw (std::invalid_argument("CreateSprite: null node"));
		try
		{
			for (unsigned i = 0; i < SPRITE_OBJECT_CLASS_NBR; ++i)
			{
				if (CREATE_SPRITE_INDEXS[i].first == spriteNode->GetName())
				{
					return (CREATE_SPRITE_INDEXS[i].second(spriteNode));
				}
			}
		}
		catch (const std::out_of_range & e)
		{
			throw (e);
		}
		catch (const std::invalid_argument & e)
		{
			throw (e);
		}
		throw (std::invalid_argument("CreateSprite: can't createSpite: invalid node name: " + spriteNode->GetName()));
	}

	TextObject::TextObjectPtr ObjectPool::CreateText(XMLNode::XMLNodePtr textNode) throw (std::out_of_range, std::invalid_argument)
	{
		TextObject::TextObjectPtr newText;

		if (!textNode)
			throw (std::invalid_argument("CreateText: null node"));
		newText = TextObject::TextObjectPtr(new TextObject());
		try
		{
			if (textNode->ChildExist(TEXT_FONT_NODE_NAME))
				newText->SetFont(ResourcesLoader::GetFont(textNode->GetChild(TEXT_FONT_NODE_NAME)->GetValue()));
			if (textNode->ChildExist(TEXT_SPRITE_NODE_NAME))
				newText->SetText(textNode->GetChild(TEXT_SPRITE_NODE_NAME)->GetValue());
			if (textNode->ChildExist(TEXT_COLOR_NODE_NAME))
			 	newText->SetColor(ObjectPool::CreateColor(textNode->GetChild(TEXT_COLOR_NODE_NAME)));
			if (textNode->ChildExist(TEXT_CHARSIZE_NODE_NAME))
				newText->SetSize(std::stoul(textNode->GetChild(TEXT_CHARSIZE_NODE_NAME)->GetValue()));
		}
		catch (const std::out_of_range & e)
		{
			throw (e);
		}
		catch (const std::invalid_argument & e)
		{
			throw (e);
		}
		return (newText);
	}

	Border::BorderPtr ObjectPool::CreateBorder(XMLNode::XMLNodePtr borderNode) throw (std::out_of_range, std::invalid_argument)
	{
		Border::BorderPtr newBorder;

		if (!borderNode)
			throw (std::invalid_argument("CreateBorder: null ptr"));
		newBorder = Border::BorderPtr(new Border());
		try
		{
			newBorder->SetSize(sf::Vector2u(std::stoul(borderNode->GetContent(WIDTH_NODE_CONTENT).second), std::stoul(borderNode->GetContent(HEIGHT_NODE_CONTENT).second)));
			newBorder->SetTileSize(sf::Vector2u(std::stoul(borderNode->GetContent(TILE_HEIGHT_NODE_CONTENT).second), std::stoul(borderNode->GetContent(TILE_WIDTH_NODE_CONTENT).second)));
			newBorder->SetTextureKey(borderNode->GetChild(OBJECT_TEXTURE_NODE_NAME)->GetValue());
			newBorder->SetCornerSubrect(sf::IntRect(std::stoul(borderNode->GetChild(BORDER_CORNER_NODE_NAME)->GetContent(X_NODE_CONTENT).second), std::stoul(borderNode->GetChild(BORDER_CORNER_NODE_NAME)->GetContent(Y_NODE_CONTENT).second), newBorder->GetTileSize().x, newBorder->GetTileSize().y));
			newBorder->SetOutlineSubrect(sf::IntRect(std::stoul(borderNode->GetChild(BORDER_OUTLINE_NODE_NAME)->GetContent(X_NODE_CONTENT).second), std::stoul(borderNode->GetChild(BORDER_OUTLINE_NODE_NAME)->GetContent(Y_NODE_CONTENT).second), newBorder->GetTileSize().x, newBorder->GetTileSize().y));
			newBorder->InitializeChilds();
			newBorder->setOrigin(newBorder->GetSize().x / 2, newBorder->GetSize().y / 2);
		}
		catch (const std::out_of_range & e)
		{
			throw (e);
		}
		catch (const std::invalid_argument & e)
		{
			throw (e);
		}
		return (newBorder);
	}

	Panel::PanelPtr	ObjectPool::CreatePanel(XMLNode::XMLNodePtr panelNode) throw (std::out_of_range, std::invalid_argument)
	{
		XMLNode::XMLNodePtr childStk;
		Panel::PanelPtr newPanel;

		if (!panelNode)
			throw (std::invalid_argument("CreatePanel: null node"));
		newPanel = Panel::PanelPtr(new Panel());
		try
		{
			if (panelNode->ChildExist(PANEL_BACKGROUND_NODE_NAME))
			 	newPanel->SetBackground(ObjectPool::CreateSprite(panelNode->GetChild(PANEL_BACKGROUND_NODE_NAME)));
			if (panelNode->ChildExist(PANEL_TITLE_NODE_NAME))
			  	newPanel->SetTitle(ObjectPool::CreateText(panelNode->GetChild(PANEL_TITLE_NODE_NAME)));
			if (panelNode->ChildExist(PANEL_BORDER_NODE_NAME))
			 	newPanel->SetBorder(ObjectPool::CreateBorder(panelNode->GetChild(PANEL_BORDER_NODE_NAME)));
			if (panelNode->ChildExist(PANEL_BUTTONS_NODE_NAME))
			{
				childStk = panelNode->GetChild(PANEL_BUTTONS_NODE_NAME);
				for (unsigned i = 0; i < childStk->GetChilds().size(); ++i)
				{
					if (childStk->GetChilds()[i]->GetContent(CLASS_NODE_CONTENT).second == PANEL_SPRITE_BUTTONS_NODE_CONTENT_VALUE)
						newPanel->AddSpriteButton(CreateSpriteButton(childStk->GetChilds()[i]));
					else if (childStk->GetChilds()[i]->GetContent(CLASS_NODE_CONTENT).second == PANEL_TEXT_BUTTONS_NODE_CONTENT_VALUE)
						newPanel->AddTextButton(CreateText(childStk->GetChilds()[i]));
				}
			}
			if (panelNode->ContentExist(X_NODE_CONTENT) && panelNode->ContentExist(Y_NODE_CONTENT))
			 	newPanel->setPosition(std::stoul(panelNode->GetContent(X_NODE_CONTENT).second), std::stoul(panelNode->GetContent(Y_NODE_CONTENT).second));
		}
		catch (const std::out_of_range & e)
		{
			throw (e);
		}
		catch (const std::invalid_argument & e)
		{
			throw (e);
		}
		return (newPanel);
	}

	Cursor::CursorPtr ObjectPool::CreateCursor(XMLNode::XMLNodePtr cursorNode) throw (std::out_of_range, std::invalid_argument)
	{
		XMLNode::XMLNodePtr childStk;
		Cursor::CursorPtr newCursor;

		if (!cursorNode)
			throw (std::invalid_argument("CreateCursor: null node"));
		newCursor = Cursor::CursorPtr(new Cursor());
		try
		{
			SetSpriteDefaults(cursorNode, newCursor.get());
		}
		catch (const std::out_of_range & e)
		{
			throw (e);
		}
		catch (const std::invalid_argument & e)
		{
			throw (e);
		}
		return (newCursor);
	}

	SpriteButton::SpriteButtonPtr	ObjectPool::CreateSpriteButton(XMLNode::XMLNodePtr spriteButtonNode) throw (std::out_of_range, std::invalid_argument)
	{
		XMLNode::XMLNodePtr childStk;
		SpriteButton::SpriteButtonPtr newSpriteButton;

		if (!spriteButtonNode)
			throw (std::invalid_argument("ObjectPool: CreateSpriteButton: null node"));
		newSpriteButton = SpriteButton::SpriteButtonPtr(new SpriteButton());
		try
		{
			SetSpriteDefaults(spriteButtonNode, newSpriteButton.get());
		}
		catch (const std::out_of_range & e)
		{
			throw (e);
		}
		catch (const std::invalid_argument & e)
		{
			throw (e);
		}
		return (newSpriteButton);
	}

	Player::PlayerPtr ObjectPool::CreatePlayer(XMLNode::XMLNodePtr playerNode) throw(std::out_of_range, std::invalid_argument)
	{
		XMLNode::XMLNodePtr childStk;
		Player::PlayerPtr newPlayer;

		newPlayer = Player::PlayerPtr(new Player());
		try
		{
			SetSpriteDefaults(playerNode, newPlayer.get());
			if (playerNode->ChildExist(PLAYER_INPUTS_NODE_NAME))
			{
				childStk = playerNode->GetChild(PLAYER_INPUTS_NODE_NAME);
				for (unsigned i = 0; i < childStk->GetChilds().size(); ++i)
					newPlayer->AddInputs(CreateInput(childStk->GetChilds()[i]));
			}
		}
		catch (const std::out_of_range & e)
		{
			throw (e);
		}
		catch (const std::invalid_argument & e)
		{
			throw (e);
		}
		return (newPlayer);
	}

	sf::Keyboard::Key ObjectPool::StrToInput(const std::string & str) throw(std::invalid_argument)
	{
		return sf::Keyboard::Key();
	}

	Direction ObjectPool::StrToDirection(const std::string & str) throw(std::invalid_argument)
	{
		return Direction();
	}
}
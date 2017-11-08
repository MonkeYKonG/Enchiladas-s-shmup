#include "ObjectPool.hpp"
#include "Border.hpp"
#include "my_graph_lib/ResourcesLoader.hpp"

namespace	my
{
	const std::string	ObjectPool::SPRITE_BACKGROUND_CLASS_NAME = "background";
	const std::string	ObjectPool::SPRITE_BUTTON_CLASS_NAME = "sprite";
	const ObjectPool::CreateSpriteFunctionsIndexs ObjectPool::CREATE_SPRITE_INDEXS[ObjectPool::SPRITE_OBJECT_CLASS_NBR] =
	{
		ObjectPool::CreateSpriteFunctionsIndexs(ObjectPool::SPRITE_BACKGROUND_CLASS_NAME, &ObjectPool::CreateBackground),
		ObjectPool::CreateSpriteFunctionsIndexs(ObjectPool::SPRITE_BUTTON_CLASS_NAME, &ObjectPool::CreateSpriteButton)
	};

	const std::string	ObjectPool::PANEL_BACKGROUND_NODE_NAME = "background";
	const std::string 	ObjectPool::PANEL_TITLE_NODE_NAME = "title";
	const std::string 	ObjectPool::PANEL_BORDER_NODE_NAME = "border";

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

	const std::string	ObjectPool::OBJECT_TEXTURE_NODE_NAME = "texture";

	const std::string 	ObjectPool::HEIGHT_NODE_CONTENT = "height";
	const std::string 	ObjectPool::WIDTH_NODE_CONTENT = "width";
	const std::string 	ObjectPool::X_NODE_CONTENT = "x";
	const std::string 	ObjectPool::Y_NODE_CONTENT = "y";
	const std::string 	ObjectPool::TILE_WIDTH_NODE_CONTENT = "tileX";
	const std::string 	ObjectPool::TILE_HEIGHT_NODE_CONTENT = "tileY";

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

	SpriteObject::SpriteObjectPtr ObjectPool::CreateBackground(XMLNode::XMLNodePtr backgroundNode) throw (std::out_of_range, std::invalid_argument)
	{
		SpriteObject::SpriteObjectPtr	newBackground;

		if (!backgroundNode)
			throw (std::invalid_argument("CreateBackgtound: null ptr"));
		newBackground = SpriteObject::SpriteObjectPtr(new SpriteObject());
		try
		{
			newBackground->SetTexture(ResourcesLoader::GetTexture(backgroundNode->GetValue()));
			newBackground->SetOrigin(newBackground->GetSprite().getGlobalBounds().width / 2, newBackground->GetSprite().getGlobalBounds().height / 2);
			if (backgroundNode->ContentExist(X_NODE_CONTENT) && backgroundNode->ContentExist(Y_NODE_CONTENT))
				newBackground->setPosition(std::stoul(backgroundNode->GetContent(X_NODE_CONTENT).second), std::stoul(backgroundNode->GetContent(Y_NODE_CONTENT).second));
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

	SpriteObject::SpriteObjectPtr	ObjectPool::CreateSpriteButton(XMLNode::XMLNodePtr spriteButtonNode) throw (std::out_of_range, std::invalid_argument)
	{
		SpriteObject::SpriteObjectPtr	newSpriteButton;

		if (!spriteButtonNode)
			throw (std::invalid_argument("CreateSpriteButton: null ptr"));
		newSpriteButton = SpriteObject::SpriteObjectPtr(new SpriteObject());
		try
		{
			newSpriteButton->SetTexture(ResourcesLoader::GetTexture(spriteButtonNode->GetChild(OBJECT_TEXTURE_NODE_NAME)->GetValue()));
			//Set animations
			newSpriteButton->SetOrigin(newSpriteButton->GetSprite().getGlobalBounds().width / 2, newSpriteButton->GetSprite().getGlobalBounds().height / 2);
			if (spriteButtonNode->ContentExist(X_NODE_CONTENT) && spriteButtonNode->ContentExist(Y_NODE_CONTENT))
				newSpriteButton->setPosition(std::stoul(spriteButtonNode->GetContent(X_NODE_CONTENT).second), std::stoul(spriteButtonNode->GetContent(Y_NODE_CONTENT).second));
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
		Cursor::CursorPtr newCursor;

		if (!cursorNode)
			throw (std::invalid_argument("CreateCursor: null node"));
		newCursor = Cursor::CursorPtr(new Cursor());
		try
		{
			//if (cursorNode->ChildExist(OBJECT_TEXTURE_NODE_NAME))
				newCursor->SetTexture(ResourcesLoader::GetTexture(cursorNode->GetChild(OBJECT_TEXTURE_NODE_NAME)->GetValue()));
			// Set animaitions here
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
}
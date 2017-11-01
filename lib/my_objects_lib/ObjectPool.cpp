#include "ObjectPool.hpp"
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

	const std::string 	ObjectPool::TEXT_FONT_NODE_NAME = "font";
	const std::string 	ObjectPool::TEXT_SPRITE_NODE_NAME = "text";
	const std::string 	ObjectPool::TEXT_COLOR_NODE_NAME = "color";
	const std::string 	ObjectPool::TEXT_CHARSIZE_NODE_NAME = "charSize";

	const std::string 	ObjectPool::COLOR_RED_CONTENT_NAME = "red";
	const std::string 	ObjectPool::COLOR_GREEN_CONTENT_NAME = "green";
	const std::string 	ObjectPool::COLOR_BLUE_CONTENT_NAME = "blue";
	const std::string 	ObjectPool::COLOR_ALPHA_CONTENT_NAME = "alpha";

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
		return (0);
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
				newPanel->SetBorder(ObjectPool::CreateSprite(panelNode->GetChild(PANEL_BORDER_NODE_NAME)));
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
}
#include "ObjectPool.hpp"
#include "Border.hpp"
#include "my_graph_lib/ResourcesLoader.hpp"

namespace	my
{
	ObjectPool::KeysMap ObjectPool::keysMap = ObjectPool::KeysMap();
	ObjectPool::DirectionsMap ObjectPool::directionsMap = ObjectPool::DirectionsMap();

	const std::string	ObjectPool::SPRITE_BACKGROUND_CLASS_NAME = "background";;
	const ObjectPool::CreateSpriteFunctionsIndexs ObjectPool::CREATE_SPRITE_INDEXS[ObjectPool::SPRITE_OBJECT_CLASS_NBR] =
	{
		ObjectPool::CreateSpriteFunctionsIndexs(ObjectPool::SPRITE_BACKGROUND_CLASS_NAME, &ObjectPool::CreateBackground)
	};

	const std::string	ObjectPool::PANEL_BACKGROUND_NODE_NAME = "background";
	const std::string 	ObjectPool::PANEL_TITLE_NODE_NAME = "title";
	const std::string 	ObjectPool::PANEL_BORDER_NODE_NAME = "border";
	const std::string 	ObjectPool::PANEL_BUTTONS_NODE_NAME = "buttons";
	const std::string 	ObjectPool::PANEL_TEXTS_NODE_NAME = "texts";
	const std::string 	ObjectPool::PANEL_SPRITES_NODE_NAME = "sprites";
	const std::string 	ObjectPool::PANEL_PROGRESS_BARS_NODE_NAME = "progressBars";
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

	const std::string	ObjectPool::DEPLACEMENT_DIRECTION_NODE_NAME = "direction";

	const std::string	ObjectPool::OBJECT_TEXTURE_NODE_NAME = "texture";
	const std::string	ObjectPool::OBJECT_ANIMATIONS_NODE_NAME = "animations";
	const std::string	ObjectPool::OBJECT_DEPLACEMENTS_NODE_NAME = "deplacements";
	const std::string	ObjectPool::OBJECT_SHOOTS_NODE_NAME = "shoots";

	const std::string	ObjectPool::PLAYER_INPUTS_DEPLACEMENT_NODE_NAME = "inputsDeplacement";
	const std::string	ObjectPool::PLAYER_INPUTS_SHOOT_NODE_NAME = "inputsShoot";

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
	const std::string	ObjectPool::SPEED_NODE_CONTENT = "speed";
	const std::string	ObjectPool::FRAMERATE_MAX_NODE_CONTENT = "framerateMax";
	const std::string	ObjectPool::TRAVEL_TIME_NODE_CONTENT = "travelTime";
	const std::string	ObjectPool::DAMAGE_NODE_CONTENT = "damage";
	const std::string	ObjectPool::MAX_HP_NODE_CONTENT = "maxHP";
	const std::string	ObjectPool::HP_NODE_CONTENT = "HP";
	const std::string	ObjectPool::ATK_NODE_CONTENT = "atk";
	const std::string	ObjectPool::DEF_NODE_CONTENT = "def";

	void ObjectPool::SetNodeDefaults(XMLNode::XMLNodePtr nodeNode, Node * node) throw(std::out_of_range, std::invalid_argument)
	{
		XMLNode::XMLNodePtr childStk;

		if (!node)
			throw (std::invalid_argument("ObjectPool: SetNodeDefaults: null node ptr"));
		if (!nodeNode)
			throw (std::invalid_argument("ObjectPool: SetNodeDefaults: null node"));
		try
		{
			if (nodeNode->ContentExist(X_NODE_CONTENT) && nodeNode->ContentExist(Y_NODE_CONTENT))
				node->setPosition(std::stol(nodeNode->GetContent(X_NODE_CONTENT).second), std::stol(nodeNode->GetContent(Y_NODE_CONTENT).second));
			if (nodeNode->ChildExist(OBJECT_DEPLACEMENTS_NODE_NAME))
			{
				childStk = nodeNode->GetChild(OBJECT_DEPLACEMENTS_NODE_NAME);
				if (childStk->ContentExist(SPEED_NODE_CONTENT))
					node->SetSpeed(std::stof(childStk->GetContent(SPEED_NODE_CONTENT).second));
				if (childStk->ChildExist(DEPLACEMENT_DIRECTION_NODE_NAME))
					node->SetDirection(CreateVector2f(childStk->GetChild(DEPLACEMENT_DIRECTION_NODE_NAME)));
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
	}

	void ObjectPool::SetSpriteDefaults(XMLNode::XMLNodePtr spriteNode, SpriteObject * sprite) throw(std::out_of_range, std::invalid_argument)
	{
		XMLNode::XMLNodePtr childStk;

		if (!sprite)
			throw (std::invalid_argument("ObjectPool: SetSpriteDefaults: null sprite"));
		if (!spriteNode)
			throw (std::invalid_argument("ObjectPool: SetSpriteDefaults: null node"));
		try
		{
			SetNodeDefaults(spriteNode, sprite);
			sprite->SetTexture(ResourcesLoader::GetTexture(spriteNode->GetChild(OBJECT_TEXTURE_NODE_NAME)->GetValue()));
			if (spriteNode->ChildExist(OBJECT_ANIMATIONS_NODE_NAME))
			{
				childStk = spriteNode->GetChild(OBJECT_ANIMATIONS_NODE_NAME);
				for (unsigned i = 0; i < childStk->GetChilds().size(); ++i)
					sprite->AddAnimation(CreateAnimation(childStk->GetChilds()[i]));
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
	}

	void ObjectPool::SetShooterDefaults(XMLNode::XMLNodePtr shooterNode, Shooter * shooter) throw (std::out_of_range, std::invalid_argument)
	{
		if (!shooter)
			throw (std::invalid_argument("ObjectPool: SetShooterDefaults: null shooter"));
		if (!shooterNode)
			throw (std::invalid_argument("ObjectPool: SetShooterDefaults: null node"));
		try
		{
			if (shooterNode->ContentExist(FRAMERATE_MAX_NODE_CONTENT))
				shooter->SetShootFramerateMax(std::stoul(shooterNode->GetContent(FRAMERATE_MAX_NODE_CONTENT).second));
			for (unsigned i = 0; i < shooterNode->GetChilds().size(); ++i)
				shooter->AddShootNode(shooterNode->GetChilds()[i]->GetContent(KEY_NODE_CONTENT).second, shooterNode->GetChilds()[i]);
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

	void ObjectPool::SetStatsContainerDefaults(XMLNode::XMLNodePtr statsContainerNode, StatsContainer * statsContainer) throw (std::out_of_range, std::invalid_argument)
	{
		if (!statsContainer)
			throw (std::invalid_argument("ObjectPool: SetStatsContainerDefaults: null alive object"));
		if (!statsContainer)
			throw (std::invalid_argument("ObjectPool: SetStatsContainerDefaults: null node"));
		try
		{
			if (statsContainerNode->ContentExist(ATK_NODE_CONTENT))
				statsContainer->SetAtk(std::stoul(statsContainerNode->GetContent(ATK_NODE_CONTENT).second));
			if (statsContainerNode->ContentExist(DEF_NODE_CONTENT))
				statsContainer->SetDef(std::stoul(statsContainerNode->GetContent(DEF_NODE_CONTENT).second));
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

	void		ObjectPool::SetAliveObjectDefaults(XMLNode::XMLNodePtr aliveObjectNode, AliveObject * aliveObject) throw (std::out_of_range, std::invalid_argument)
	{
		if (!aliveObject)
			throw (std::invalid_argument("ObjectPool: SetAliveObjectDefaults: null alive object"));
		if (!aliveObject)
			throw (std::invalid_argument("ObjectPool: SetAliveObjectDefaults: null node"));
		try
		{
			if (aliveObjectNode->ContentExist(MAX_HP_NODE_CONTENT))
			{
				aliveObject->SetMaxHP(std::stoul(aliveObjectNode->GetContent(MAX_HP_NODE_CONTENT).second));
				if (aliveObjectNode->ContentExist(HP_NODE_CONTENT))
					aliveObject->SetCurHP(std::stoul(aliveObjectNode->GetContent(HP_NODE_CONTENT).second));
				else
					aliveObject->SetCurHP(aliveObject->GetMaxHP());
			}
			SetStatsContainerDefaults(aliveObjectNode, aliveObject);
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

	sf::Vector2f	ObjectPool::CreateVector2f(XMLNode::XMLNodePtr vector2fNode) throw (std::out_of_range, std::invalid_argument)
	{
		sf::Vector2f newVector;

		if (!vector2fNode)
			throw (std::invalid_argument("ObjectPool: CreateVector2f: null node"));
		try
		{
			newVector.x = std::stof(vector2fNode->GetContent(X_NODE_CONTENT).second);
			newVector.y = std::stof(vector2fNode->GetContent(Y_NODE_CONTENT).second);
		}
		catch (const std::out_of_range & e)
		{
			throw (e);
		}
		catch (const std::invalid_argument & e)
		{
			throw (e);
		}
		return (newVector);
	}

  AnimatedObject::Animation	ObjectPool::CreateAnimation(XMLNode::XMLNodePtr animationNode) throw (std::out_of_range, std::invalid_argument)
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

	Player::InputDeplacement ObjectPool::CreateInputDeplacement(XMLNode::XMLNodePtr inputNode) throw(std::out_of_range, std::invalid_argument)
	{
		Player::InputDeplacement newInput;

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

	Player::InputShoot ObjectPool::CreateInputShoot(XMLNode::XMLNodePtr inputNode) throw (std::out_of_range, std::invalid_argument)
	{
		Player::InputShoot newInput;

		try
		{
			newInput.first = StrToInput(inputNode->GetContent(INPUT_NODE_CONTENT).second);
			newInput.second = inputNode->GetContent(KEY_NODE_CONTENT).second;
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
			SetNodeDefaults(textNode, newText.get());
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
			if (panelNode->ChildExist(PANEL_TEXTS_NODE_NAME))
			{
				childStk = panelNode->GetChild(PANEL_TEXTS_NODE_NAME);
				for (unsigned i = 0; i < childStk->GetChilds().size(); ++i)
					newPanel->AddText(CreateText(childStk->GetChilds()[i]));
			}
			if (panelNode->ChildExist(PANEL_SPRITES_NODE_NAME))
			{
				childStk = panelNode->GetChild(PANEL_SPRITES_NODE_NAME);
				for (unsigned i = 0; i < childStk->GetChilds().size(); ++i)
					newPanel->AddSprite(CreateSprite(childStk->GetChilds()[i]));
			}
			if (panelNode->ChildExist(PANEL_PROGRESS_BARS_NODE_NAME))
			{
				childStk = panelNode->GetChild(PANEL_PROGRESS_BARS_NODE_NAME);
				for (unsigned i = 0; i < childStk->GetChilds().size(); ++i)
					newPanel->AddProgressBars(CreateProgressBar(childStk->GetChilds()[i]));
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
			if (spriteButtonNode->ChildExist(PANEL_TITLE_NODE_NAME))
				newSpriteButton->SetText(CreateText(spriteButtonNode->GetChild(PANEL_TITLE_NODE_NAME)));
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
			SetAliveObjectDefaults(playerNode, newPlayer.get());
			if (playerNode->ChildExist(PLAYER_INPUTS_DEPLACEMENT_NODE_NAME))
			{
				childStk = playerNode->GetChild(PLAYER_INPUTS_DEPLACEMENT_NODE_NAME);
				for (unsigned i = 0; i < childStk->GetChilds().size(); ++i)
					newPlayer->AddInputDeplacement(CreateInputDeplacement(childStk->GetChilds()[i]));
			}
			if (playerNode->ChildExist(PLAYER_INPUTS_SHOOT_NODE_NAME))
			{
				childStk = playerNode->GetChild(PLAYER_INPUTS_SHOOT_NODE_NAME);
				for (unsigned i = 0; i < childStk->GetChilds().size(); ++i)
					newPlayer->AddInputShoot(CreateInputShoot(childStk->GetChilds()[i]));
			}
			if (playerNode->ChildExist(OBJECT_SHOOTS_NODE_NAME))
				SetShooterDefaults(playerNode->GetChild(OBJECT_SHOOTS_NODE_NAME), newPlayer.get());
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

	Enemy::EnemyPtr ObjectPool::CreateEnemy(XMLNode::XMLNodePtr enemyNode) throw(std::out_of_range, std::invalid_argument)
	{
		Enemy::EnemyPtr newEnemy;

		if (!enemyNode)
			throw (std::invalid_argument("ObjectPool: CreateEnemy: null node"));
		newEnemy = Enemy::EnemyPtr(new Enemy());
		try
		{
			SetSpriteDefaults(enemyNode, newEnemy.get());
			SetAliveObjectDefaults(enemyNode, newEnemy.get());
			if (enemyNode->ChildExist(OBJECT_SHOOTS_NODE_NAME))
			{
				SetShooterDefaults(enemyNode->GetChild(OBJECT_SHOOTS_NODE_NAME), newEnemy.get());
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
		return (newEnemy);
	}

	Bullet::BulletPtr ObjectPool::CreateBullet(XMLNode::XMLNodePtr bulletNode) throw (std::out_of_range, std::invalid_argument)
	{
		Bullet::BulletPtr newBullet;

		if (!bulletNode)
			throw (std::invalid_argument("ObjectPool: CreateBullet: null node"));
		newBullet = Bullet::BulletPtr(new Bullet());
		try
		{
			SetSpriteDefaults(bulletNode, newBullet.get());
			newBullet->SetTravelTime(std::stoul(bulletNode->GetContent(TRAVEL_TIME_NODE_CONTENT).second));
			newBullet->SetDamage(std::stoul(bulletNode->GetContent(DAMAGE_NODE_CONTENT).second));
			newBullet->SetOnDeplacement(true);
		}
		catch (const std::out_of_range & e)
		{
			throw (e);
		}
		catch (const std::invalid_argument & e)
		{
			throw (e);
		}
		return (newBullet);
	}

	ProgressBar::ProgressBarPtr ObjectPool::CreateProgressBar(XMLNode::XMLNodePtr progressBarNode) throw (std::out_of_range, std::invalid_argument)
	{
		ProgressBar::ProgressBarPtr newProgressBar;

		if (!progressBarNode)
			throw (std::invalid_argument("ObjectPool: CreateProgressBar: null node"));
		newProgressBar = ProgressBar::ProgressBarPtr(new ProgressBar());
		try
		{
			SetSpriteDefaults(progressBarNode, newProgressBar.get());
		}
		catch (const std::out_of_range & e)
		{
			throw (e);
		}
		catch (const std::invalid_argument & e)
		{
			throw (e);
		}
		return (newProgressBar);
	}

	void ObjectPool::InitializeKeysMap() noexcept
	{
		keysMap["A"] = sf::Keyboard::A;
		keysMap["B"] = sf::Keyboard::B;
		keysMap["C"] = sf::Keyboard::C;
		keysMap["D"] = sf::Keyboard::D;
		keysMap["E"] = sf::Keyboard::E;
		keysMap["F"] = sf::Keyboard::F;
		keysMap["G"] = sf::Keyboard::G;
		keysMap["H"] = sf::Keyboard::H;
		keysMap["I"] = sf::Keyboard::I;
		keysMap["J"] = sf::Keyboard::J;
		keysMap["K"] = sf::Keyboard::K;
		keysMap["L"] = sf::Keyboard::L;
		keysMap["M"] = sf::Keyboard::M;
		keysMap["N"] = sf::Keyboard::N;
		keysMap["O"] = sf::Keyboard::O;
		keysMap["P"] = sf::Keyboard::P;
		keysMap["Q"] = sf::Keyboard::Q;
		keysMap["R"] = sf::Keyboard::R;
		keysMap["S"] = sf::Keyboard::S;
		keysMap["T"] = sf::Keyboard::T;
		keysMap["U"] = sf::Keyboard::U;
		keysMap["V"] = sf::Keyboard::V;
		keysMap["W"] = sf::Keyboard::W;
		keysMap["X"] = sf::Keyboard::X;
		keysMap["Y"] = sf::Keyboard::Y;
		keysMap["Z"] = sf::Keyboard::Z;
		keysMap["Num0"] = sf::Keyboard::Num0;
		keysMap["Num1"] = sf::Keyboard::Num1;
		keysMap["Num2"] = sf::Keyboard::Num2;
		keysMap["Num3"] = sf::Keyboard::Num3;
		keysMap["Num4"] = sf::Keyboard::Num4;
		keysMap["Num5"] = sf::Keyboard::Num5;
		keysMap["Num6"] = sf::Keyboard::Num6;
		keysMap["Num7"] = sf::Keyboard::Num7;
		keysMap["Num8"] = sf::Keyboard::Num8;
		keysMap["Num9"] = sf::Keyboard::Num9;
		keysMap["Escape"] = sf::Keyboard::Escape;
		keysMap["LControl"] = sf::Keyboard::LControl;
		keysMap["LShift"] = sf::Keyboard::LShift;
		keysMap["LAlt"] = sf::Keyboard::LAlt;
		keysMap["LSystem"] = sf::Keyboard::LSystem;
		keysMap["RControl"] = sf::Keyboard::RControl;
		keysMap["RShift"] = sf::Keyboard::RShift;
		keysMap["RAlt"] = sf::Keyboard::RAlt;
		keysMap["RSystem"] = sf::Keyboard::RSystem;
		keysMap["Menu"] = sf::Keyboard::Menu;
		keysMap["LBracket"] = sf::Keyboard::LBracket;
		keysMap["RBracket"] = sf::Keyboard::RBracket;
		keysMap["SemiColon"] = sf::Keyboard::SemiColon;
		keysMap["Comma"] = sf::Keyboard::Comma;
		keysMap["Period"] = sf::Keyboard::Period;
		keysMap["Quote"] = sf::Keyboard::Quote;
		keysMap["Slash"] = sf::Keyboard::Slash;
		keysMap["BackSlash"] = sf::Keyboard::BackSlash;
		keysMap["Tilde"] = sf::Keyboard::Tilde;
		keysMap["Equal"] = sf::Keyboard::Equal;
		keysMap["Dash"] = sf::Keyboard::Dash;
		keysMap["Space"] = sf::Keyboard::Space;
		keysMap["Return"] = sf::Keyboard::Return;
		keysMap["BackSpace"] = sf::Keyboard::BackSpace;
		keysMap["Tab"] = sf::Keyboard::Tab;
		keysMap["PageUp"] = sf::Keyboard::PageUp;
		keysMap["PageDown"] = sf::Keyboard::PageDown;
		keysMap["End"] = sf::Keyboard::End;
		keysMap["Hone"] = sf::Keyboard::Home;
		keysMap["Insert"] = sf::Keyboard::Insert;
		keysMap["Delete"] = sf::Keyboard::Delete;
		keysMap["Add"] = sf::Keyboard::Add;
		keysMap["Subtract"] = sf::Keyboard::Subtract;
		keysMap["Multiply"] = sf::Keyboard::Multiply;
		keysMap["Divide"] = sf::Keyboard::Divide;
		keysMap["Left"] = sf::Keyboard::Left;
		keysMap["Right"] = sf::Keyboard::Right;
		keysMap["Up"] = sf::Keyboard::Up;
		keysMap["Down"] = sf::Keyboard::Down;
		keysMap["Numpad0"] = sf::Keyboard::Numpad0;
		keysMap["Numpad1"] = sf::Keyboard::Numpad1;
		keysMap["Numpad2"] = sf::Keyboard::Numpad2;
		keysMap["Numpad3"] = sf::Keyboard::Numpad3;
		keysMap["Numpad4"] = sf::Keyboard::Numpad4;
		keysMap["Numpad5"] = sf::Keyboard::Numpad5;
		keysMap["Numpad6"] = sf::Keyboard::Numpad6;
		keysMap["Numpad7"] = sf::Keyboard::Numpad7;
		keysMap["Numpad8"] = sf::Keyboard::Numpad8;
		keysMap["Numpad9"] = sf::Keyboard::Numpad9;
		keysMap["F1"] = sf::Keyboard::F1;
		keysMap["F2"] = sf::Keyboard::F2;
		keysMap["F3"] = sf::Keyboard::F3;
		keysMap["F4"] = sf::Keyboard::F4;
		keysMap["F5"] = sf::Keyboard::F5;
		keysMap["F6"] = sf::Keyboard::F6;
		keysMap["F7"] = sf::Keyboard::F7;
		keysMap["F8"] = sf::Keyboard::F8;
		keysMap["F9"] = sf::Keyboard::F9;
		keysMap["F10"] = sf::Keyboard::F10;
		keysMap["F11"] = sf::Keyboard::F11;
		keysMap["F12"] = sf::Keyboard::F12;
		keysMap["F13"] = sf::Keyboard::F13;
		keysMap["F14"] = sf::Keyboard::F14;
		keysMap["F15"] = sf::Keyboard::F15;
		keysMap["Pause"] = sf::Keyboard::Pause;
	}

	void ObjectPool::InitializeDirectionsMap() noexcept
	{
		directionsMap["UP"] = Direction::UP;
		directionsMap["DOWN"] = Direction::DOWN;
		directionsMap["LEFT"] = Direction::LEFT;
		directionsMap["RIGHT"] = Direction::RIGHT;
	}

	sf::Keyboard::Key ObjectPool::StrToInput(const std::string & str) throw(std::invalid_argument)
	{
		if (keysMap.empty())
			InitializeKeysMap();
		try
		{
			return (keysMap.at(str));
		}
		catch (const std::out_of_range & e)
		{
			throw (e);
		}
	}

	Direction ObjectPool::StrToDirection(const std::string & str) throw(std::invalid_argument)
	{
		if (directionsMap.empty())
			InitializeDirectionsMap();
		try
		{
			return (directionsMap.at(str));
		}
		catch (const std::out_of_range & e)
		{
			throw (e);
		}
	}
}

#include "SchmupMainGame.hpp"
#include "my_graph_lib/ResourcesLoader.hpp"
#include "my_graph_lib/InputsManager.hpp"
#include "my_graph_lib/XMLParser.hpp"
#include "my_objects_lib/ObjectPool.hpp"

#include <iostream>

const std::string my::schmup::SchmupMainGame::MAIN_NODE_NAME = "main";
const std::string my::schmup::SchmupMainGame::PLAY_NODE_NAME = "play";
const std::string my::schmup::SchmupMainGame::CRAFTING_NODE_NAME = "crafting";
const std::string my::schmup::SchmupMainGame::SELECT_STAGE_NODE_NAME = "selectStage";
const std::string my::schmup::SchmupMainGame::NODE_NAMES[my::schmup::SchmupMainGame::GAME_STATES::GAME_STATES_COUNT] =
{
	my::schmup::SchmupMainGame::MAIN_NODE_NAME,
	my::schmup::SchmupMainGame::PLAY_NODE_NAME,
	my::schmup::SchmupMainGame::CRAFTING_NODE_NAME,
	my::schmup::SchmupMainGame::SELECT_STAGE_NODE_NAME
};

my::schmup::SchmupMainGame::SchmupMainGame()
	: m_saveSlot(-1), m_score(0), m_maxScore(0), m_playerLevel(1), m_playerCurExp(0), m_playerLevelUpExp(10), m_gameState(MAIN)
{
}

void my::schmup::SchmupMainGame::Initialize(XMLNode::XMLNodePtr sceneRoot) throw (std::out_of_range, std::invalid_argument)
{
	try
	{
		m_gameRoot = sceneRoot;
		for (int i = 0; i < GAME_STATES::GAME_STATES_COUNT; ++i)
			m_nodes[i] = sceneRoot->GetChild(NODE_NAMES[i]);
		SchmupScene::Initialize(m_nodes[m_gameState]);
	}
	catch (const std::out_of_range & e)
	{
		throw (std::out_of_range("SchmupMainGame: Initialize: " + std::string(e.what())));
	}
	catch (const std::invalid_argument & e)
	{
		throw (std::invalid_argument("SchmupMainGame: Initialize: " + std::string(e.what())));
	}
}

void	my::schmup::SchmupMainGame::LoadSavingData(int slot) throw (std::out_of_range, std::invalid_argument)
{
	if (slot < 0)
		throw (std::invalid_argument("SchmupMainGame: LoadSavingData: invalid slot: " + std::to_string(slot)));
	m_saveSlot = slot;
	InitializePlayer();
	InitializeGameValues();
}

void my::schmup::SchmupMainGame::Reset() throw (std::out_of_range, std::invalid_argument)
{
	sf::Vector2i mousePos;

	if (m_cursor)
		mousePos = sf::Vector2i(m_cursor->getPosition());
	m_root = m_gameRoot;
	SchmupScene::Reset();
	InputsManager::ClearInputs();
	Update(sf::Vector2i(mousePos));
}

void my::schmup::SchmupMainGame::TriggerEnemyIsDamaged(Shooter::ShootList::iterator & bulletIt, EnemiesPool::EnemiesList::iterator & enemyIt) noexcept
{
	if (!(*enemyIt)->IsAlive())
		return;
	SchmupScene::TriggerEnemyIsDamaged(bulletIt, enemyIt);
	if (!(*enemyIt)->IsAlive())
	{
		m_score += 1;
		AddExperience(1);
	}
}

const my::SceneReturnValue my::schmup::SchmupMainGame::UpdateMain(const sf::Vector2i & mousePos) throw (std::exception)
{
	SceneReturnValue returnValue;
	Panel::SpriteButtons panelButtons;	
	Panel::TextList panelTexts;

	try
	{
		returnValue = MainMenu::Update(mousePos);
		if (returnValue.value != STATE_RETURN::NOTHING)
			return (returnValue);
		panelButtons = m_panels[0]->GetSpriteButtons();
		for (unsigned i = 0; i < panelButtons.size(); ++i)
		{
			if (panelButtons[i]->IsMouseOvered() && InputsManager::IsButtonReleasedOne(sf::Mouse::Left))
			{
				switch (i)
				{
				case MAIN_BUTTONS::PLAY_BTN:
					m_gameState = GAME_STATES::SELECT_STAGE;
					Reset();
					return (returnValue);

				case MAIN_BUTTONS::UPDATE_BTN:
					m_gameState = GAME_STATES::CRAFTING;
					Reset();
					return (returnValue);

				case MAIN_BUTTONS::MAIN_MENU_BTN:
					returnValue.value = STATE_RETURN::MENU;
					return (returnValue);
						
				default:
					break;
				}
			}
		}
		panelTexts = m_panels[1]->GetTexts();
		panelTexts[0]->SetText("Score: " + std::to_string(m_score));
		panelTexts[1]->SetText("Meilleur: " + std::to_string(m_maxScore));
	}
	catch (const std::exception & e) {
		throw (e);
	}
	return (returnValue);
}

const my::SceneReturnValue my::schmup::SchmupMainGame::UpdatePlay(const sf::Vector2i & mousePos) throw (std::exception)
{
	Panel::TextList panelTexts;
	SceneReturnValue returnValue;

	if (m_enemies.empty() && m_enemiesPool.IsWavesClear())
	{
		if (m_score > m_maxScore)
			m_maxScore = m_score;
		m_gameState = GAME_STATES::MAIN;
		Reset();
		return (SceneReturnValue());
	}
	panelTexts = m_panels[0]->GetTexts();
	panelTexts[0]->SetText("Score: " + std::to_string(m_score));
	panelTexts[1]->SetText("Meilleur: " + std::to_string(m_maxScore));
	returnValue = SchmupScene::Update(mousePos);
	UpdateLimitPosition();
	return (returnValue);
}

const my::SceneReturnValue my::schmup::SchmupMainGame::UpdateCrafting(const sf::Vector2i & mousePos) throw (std::exception)
{
	SceneReturnValue returnValue;
	Panel::SpriteButtons panelButtons;
	Panel::TextList panelTexts;

	try
	{
		returnValue = MainMenu::Update(mousePos);
		if (returnValue.value != STATE_RETURN::NOTHING)
			return (returnValue);
		panelButtons = m_panels[0]->GetSpriteButtons();
		for (unsigned i = 0; i < panelButtons.size(); ++i)
		{
			if (panelButtons[i]->IsMouseOvered() && InputsManager::IsButtonReleasedOne(sf::Mouse::Left))
			{
				switch (i)
				{
				case CRAFTING_BUTTONS::MORE_ATK_BTN:
					m_player->SetAtk(m_player->GetAtk() + 1);
					break;

				case CRAFTING_BUTTONS::MORE_DEF_BTN:
					m_player->SetDef(m_player->GetDef() + 1);
					break;

				case CRAFTING_BUTTONS::CRAFTING_BACK_BTN:
					m_gameState = GAME_STATES::MAIN;
					Reset();
					return (returnValue);
				}
			}
		}
		panelTexts = m_panels[1]->GetTexts();
		panelTexts[0]->SetText("Atk: " + std::to_string(m_player->GetAtk()));
		panelTexts[1]->SetText("Def: " + std::to_string(m_player->GetDef()));
		panelTexts[2]->SetText("Lvl: " + std::to_string(m_playerLevel));
		panelTexts[3]->SetText("Exp: " + std::to_string(m_playerCurExp) + " / " + std::to_string(m_playerLevelUpExp));
	}
	catch (const std::exception & e) {
		throw (e);
	}
	return (returnValue);
}

const my::SceneReturnValue my::schmup::SchmupMainGame::UpdateSelectStage(const sf::Vector2i & mousePos) throw (std::exception)
{
	SceneReturnValue returnValue;
	Panel::SpriteButtons panelButtons;

	try
	{
		returnValue = MainMenu::Update(mousePos);
		if (returnValue.value != STATE_RETURN::NOTHING)
			return (returnValue);
		panelButtons = m_panels[0]->GetSpriteButtons();
		for (unsigned i = 0; i < panelButtons.size(); ++i)
		{
			if (panelButtons[i]->IsMouseOvered() && InputsManager::IsButtonReleasedOne(sf::Mouse::Left))
			{
				if (i == 0)
				{
					m_gameState = GAME_STATES::MAIN;
					Reset();
				}
				else
				{
					m_gameState = GAME_STATES::PLAY;
					InitializeStage(i);
					Reset();
					m_panels[0]->GetProgressBars()[0]->SetBackgroundTexture(ResourcesLoader::GetTexture("button.png"));
					m_panels[0]->GetProgressBars()[0]->SetCurValue(&m_playerCurExp);
					m_panels[0]->GetProgressBars()[0]->SetMaxValue(&m_playerLevelUpExp);
					m_panels[0]->GetProgressBars()[0]->SetBackgroundSize(sf::IntRect(20, 20, 100, 20));
				}
			}
		}
	}
	catch (const std::exception & e) {
		throw (e);
	}
	return (returnValue);
}

const my::SceneReturnValue my::schmup::SchmupMainGame::Update(const sf::Vector2i & mousePos) throw(std::exception)
{
	SceneReturnValue returnValue;

	try
	{
		switch (m_gameState)
		{
		case my::schmup::SchmupMainGame::MAIN:
			returnValue = UpdateMain(mousePos);
			break;

		case my::schmup::SchmupMainGame::PLAY:
			returnValue = UpdatePlay(mousePos);
			break;

		case my::schmup::SchmupMainGame::CRAFTING:
			returnValue = UpdateCrafting(mousePos);
			break;

		case my::schmup::SchmupMainGame::SELECT_STAGE:
			returnValue = UpdateSelectStage(mousePos);
			break;

		default:
			break;
		}
	}
	catch (const std::exception & e)
	{
		throw (e);
	}
	return (returnValue);
}

void my::schmup::SchmupMainGame::draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept
{
	switch (m_gameState)
	{
	case my::schmup::SchmupMainGame::MAIN:
		drawMain(target, states);
		break;

	case my::schmup::SchmupMainGame::PLAY:
		drawPlay(target, states);
		break;

	case my::schmup::SchmupMainGame::CRAFTING:
		drawCrafting(target, states);
		break;

	case my::schmup::SchmupMainGame::SELECT_STAGE:
		drawSelectStage(target, states);
		break;

	default:
		break;
	}
}

void my::schmup::SchmupMainGame::drawMain(sf::RenderTarget & target, sf::RenderStates states) const noexcept
{
	MainMenu::draw(target, states);
	states.transform *= getTransform();
}

void my::schmup::SchmupMainGame::drawPlay(sf::RenderTarget & target, sf::RenderStates states) const noexcept
{
	SchmupScene::draw(target, states);
	states.transform *= getTransform();
}

void my::schmup::SchmupMainGame::drawCrafting(sf::RenderTarget & target, sf::RenderStates states) const noexcept
{
	MainMenu::draw(target, states);
	states.transform *= getTransform();
}

void my::schmup::SchmupMainGame::drawSelectStage(sf::RenderTarget & target, sf::RenderStates states) const noexcept
{
	MainMenu::draw(target, states);
	states.transform *= getTransform();
}

void my::schmup::SchmupMainGame::ClearStageScreen() noexcept
{
	m_enemies.clear();
	m_enemiesShoots.clear();
	m_playerShoots.clear();
	m_score = 0;
}

void my::schmup::SchmupMainGame::InitializeStage(unsigned levelIndex) throw (std::out_of_range, std::invalid_argument)
{
	XMLNode::XMLNodePtr paternNode;
	XMLNode::XMLNodePtr enemiesNode;

	try
	{
		ClearStageScreen();
		m_player->setPosition(200, 500); // Utiliser le fichier de conf du niveau pour ca
		paternNode = XMLParser::Load("level_" + std::to_string(levelIndex) + ".xml");
		enemiesNode = XMLParser::Load("level_" + std::to_string(levelIndex) + "_enemies.xml");
		m_enemiesPool.InitializeEnemies(enemiesNode);
		m_enemiesPool.InitializeStage(GenerateStage(paternNode));
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

void my::schmup::SchmupMainGame::InitializePlayer() throw (std::out_of_range, std::invalid_argument)
{
	try
	{
		m_playerNode = XMLParser::Load("default_player.xml");
		m_player = ObjectPool::CreatePlayer(m_playerNode);
	}
	catch (std::out_of_range & e)
	{
		throw (std::out_of_range("SchmupMainGame: InitializePlayer: " + std::string(e.what())));
	}
	catch (std::invalid_argument & e)
	{
		throw (std::invalid_argument("SchmupMainGame: InitializePlayer: " + std::string(e.what())));
	}
}

void my::schmup::SchmupMainGame::InitializeGameValues() throw (std::out_of_range, std::invalid_argument)
{
	m_score = 0;
	m_maxScore = 0;
}

my::XMLNode::XMLNodePtr my::schmup::SchmupMainGame::GenerateStage(XMLNode::XMLNodePtr paternNode) throw (std::out_of_range, std::invalid_argument)
{
	XMLNode::XMLNodePtr generatedStage;

	try
	{
		generatedStage = XMLNode::create();
		generatedStage->SetName("stage");
		for (unsigned i = 0; i < 30; ++i)
		{
			generatedStage->AddChild(paternNode->GetChilds()[rand() % paternNode->GetChilds().size()]);
		}
	}
	catch (const std::out_of_range & e)
	{
		throw (std::out_of_range("SchmupMainGame: GenerateStage: " + std::string(e.what())));
	}
	catch (const std::invalid_argument & e)
	{
		throw (std::invalid_argument("SchmupMainGame: GenerateStage: " + std::string(e.what())));
	}
	return (generatedStage);
}

bool my::schmup::SchmupMainGame::AddExperience(unsigned exp) noexcept
{
	bool isLevelUp;

	m_playerCurExp += exp;
	isLevelUp = m_playerCurExp >= m_playerLevelUpExp;
	while (m_playerCurExp >= m_playerLevelUpExp)
		AddLevel();
	return (isLevelUp);
}

void my::schmup::SchmupMainGame::AddLevel() noexcept
{
	m_playerLevel++;
	m_playerCurExp -= m_playerLevelUpExp;
}

void my::schmup::SchmupMainGame::UpdateLimitPosition() noexcept
{
	CorrectPlayerPosition();
	UnloadUnlimitEnemies();
	UnloadUnlimitShoots();
}

void my::schmup::SchmupMainGame::CorrectPlayerPosition() noexcept
{
	if (IsOutOfTopLimit(m_player))
		m_player->setPosition(m_player->getPosition().x, 0);
	else if (IsOutOfBottomLimit(m_player))
		m_player->setPosition(m_player->getPosition().x, 1050 - m_player->GetHitBox().height);
}

void my::schmup::SchmupMainGame::UnloadUnlimitEnemies() noexcept
{
	EnemiesPool::EnemiesList::iterator it;

	it = m_enemies.begin();
	while (it != m_enemies.end())
	{
		if (IsOutOfLeftLimit(*it) || IsOutOfTopLimit(*it) || IsOutOfBottomLimit(*it))
			it = m_enemies.erase(it);
		else
			it++;
	}
}

void my::schmup::SchmupMainGame::UnloadUnlimitShoots() noexcept
{
	Shooter::ShootList::iterator it;

	it = m_enemiesShoots.begin();
	while (it != m_enemiesShoots.end())
	{
		if (IsOutOfLimit(*it))
			it = m_enemiesShoots.erase(it);
		else
			it++;
	}
	it = m_playerShoots.begin();
	while (it != m_playerShoots.end())
	{
		if (IsOutOfLimit(*it))
			it = m_playerShoots.erase(it);
		else
			it++;
	}
}

bool my::schmup::SchmupMainGame::IsOutOfLimit(Node::NodePtr node) const noexcept
{
	return (IsOutOfLeftLimit(node) || IsOutOfRightLimit(node) || IsOutOfTopLimit(node) || IsOutOfBottomLimit(node));
}

bool my::schmup::SchmupMainGame::IsOutOfLeftLimit(Node::NodePtr node) const noexcept
{
	return (node->GetHitBox().left < 0);
}

bool my::schmup::SchmupMainGame::IsOutOfRightLimit(Node::NodePtr node) const noexcept
{
	sf::FloatRect nodeRect;
	
	nodeRect = node->GetHitBox();
	return (nodeRect.left + nodeRect.width > 1680);
}

bool my::schmup::SchmupMainGame::IsOutOfTopLimit(Node::NodePtr node) const noexcept
{
	return (node->GetHitBox().top < 0);
}

bool my::schmup::SchmupMainGame::IsOutOfBottomLimit(Node::NodePtr node) const noexcept
{
	sf::FloatRect nodeRect;

	nodeRect = node->GetHitBox();
	return (nodeRect.top + nodeRect.height > 1050);
}

void my::schmup::SchmupMainGame::PreparingPlayerBuller(Bullet::BulletPtr newBullet) noexcept
{
	sf::FloatRect playerBox;
	sf::FloatRect bulletBox;

	playerBox = m_player->GetHitBox();
	bulletBox = newBullet->GetHitBox();
	newBullet->setPosition(playerBox.left + playerBox.width, playerBox.top + playerBox.height / 2);
}
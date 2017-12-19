#include "SchmupMainGame.hpp"
#include "my_graph_lib/ResourcesLoader.hpp"
#include "my_graph_lib/InputsManager.hpp"

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
	: m_gameState(MAIN)
{
}

void my::schmup::SchmupMainGame::Initialize(XMLNode::XMLNodePtr sceneRoot) throw (std::out_of_range, std::invalid_argument)
{
	try
	{
		m_gameRoot = sceneRoot;
		for (int i = 0; i < GAME_STATES::GAME_STATES_COUNT; ++i)
			m_nodes[i] = sceneRoot->GetChild(NODE_NAMES[i]);
	}
	catch (const std::out_of_range & e)
	{
		throw (std::out_of_range("SchmupMainGame: Initialize: " + std::string(e.what())));
	}
	catch (const std::invalid_argument & e)
	{
		throw (std::invalid_argument("SchmupMainGame: Initialize: " + std::string(e.what())));
	}
	SchmupScene::Initialize(m_nodes[m_gameState]);
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

const my::SceneReturnValue my::schmup::SchmupMainGame::UpdateMain(const sf::Vector2i & mousePos) throw (std::exception)
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
				switch (i)
				{
				case MAIN_BUTTONS::PLAY_BTN:
					m_gameState = GAME_STATES::SELECT_STAGE;
					Reset();
					break;

				case MAIN_BUTTONS::UPDATE_BTN:
					m_gameState = GAME_STATES::CRAFTING;
					Reset();
					break;

				case MAIN_BUTTONS::MAIN_MENU_BTN:
					returnValue.value = STATE_RETURN::MENU;
					break;
				}
			}
		}
	}
	catch (const std::exception & e) {
		throw (e);
	}
	return (returnValue);
}

const my::SceneReturnValue my::schmup::SchmupMainGame::UpdatePlay(const sf::Vector2i & mousePos) throw (std::exception)
{
	return (SchmupScene::Update(mousePos));
}

const my::SceneReturnValue my::schmup::SchmupMainGame::UpdateCrafting(const sf::Vector2i & mousePos) throw (std::exception)
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
				switch (i)
				{
				case CRAFTING_BUTTONS::MORE_ATK_BTN:
					break;

				case CRAFTING_BUTTONS::MORE_DEF_BTN:
					break;

				case CRAFTING_BUTTONS::CRAFTING_BACK_BTN:
					m_gameState = GAME_STATES::MAIN;
					Reset();
					break;
				}
			}
		}
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

void my::schmup::SchmupMainGame::InitializeStage() noexcept
{
	m_player->setPosition(200, 500);
	// remettre les cooldown et scores a zero
}
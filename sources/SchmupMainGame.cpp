#include "SchmupMainGame.hpp"
#include "my_graph_lib/ResourcesLoader.hpp"
#include "SchmupPool.hpp"

my::schmup::SchmupMainGame::SchmupMainGame()
	: m_gameState(CRAFTING)
{
}

void my::schmup::SchmupMainGame::Initialize(XMLNode::XMLNodePtr sceneRoot) throw (std::out_of_range, std::invalid_argument)
{
	ShipModule::ShipModulePtr newModule;

	m_ship.setPosition(200, 200);
	newModule = ShipModule::ShipModulePtr(new ShipModule());
	newModule->SetTexture(ResourcesLoader::GetTexture("panel_border.png"));
	m_ship.AddModule(newModule);
}

const my::SceneReturnValue my::schmup::SchmupMainGame::Update(sf::RenderWindow & window) throw(std::exception)
{
	SceneReturnValue returnValue;
	try
	{
		switch (m_gameState)
		{
		case my::schmup::SchmupMainGame::PLAY:
			returnValue = SchmupScene::Update(window);
			break;

		case my::schmup::SchmupMainGame::CRAFTING:
			returnValue = MainMenu::Update(window);
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
	case my::schmup::SchmupMainGame::PLAY:
		SchmupScene::draw(target, states);
		break;

	case my::schmup::SchmupMainGame::CRAFTING:
		drawCrafting(target, states);
		break;

	default:
		break;
	}
}

void my::schmup::SchmupMainGame::drawCrafting(sf::RenderTarget & target, sf::RenderStates states) const noexcept
{
	MainMenu::draw(target, states);
	states.transform *= getTransform();

	target.draw(m_ship);
}
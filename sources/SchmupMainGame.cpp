#include "SchmupMainGame.hpp"

my::schmup::SchmupMainGame::SchmupMainGame()
	: m_gameState(CRAFTING)
{
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
			m_player->Update();
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

	target.draw(*m_player, states);
}
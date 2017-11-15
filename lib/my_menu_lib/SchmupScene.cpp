#include "SchmupScene.hpp"
#include "my_objects_lib/ObjectPool.hpp"

const std::string my::SchmupScene::SCENE_PLAYER_NODE = "player";

my::SchmupScene::SchmupScene()
{}

const my::SceneReturnValue my::SchmupScene::Update(sf::RenderWindow & window) throw(std::exception)
{
	SceneReturnValue returnValue;

	try
	{
		returnValue = MainMenu::Update(window);
		if (returnValue.value == STATE_RETURN::CLOSE)
			return (returnValue);
		m_player->Update();
	}
	catch (const std::exception & e)
	{
		throw (e);
	}
	return (returnValue);
}

void my::SchmupScene::Initialize(XMLNode::XMLNodePtr sceneRoot) throw(std::out_of_range, std::invalid_argument)
{
	try
	{
		m_initializationFunctions.push_back(MainMenu::InitFunctionPair(SCENE_PLAYER_NODE, static_cast<InitializationFunction>(&SchmupScene::InitializePlayer)));
		MainMenu::Initialize(sceneRoot);
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

void my::SchmupScene::Reset() throw(std::out_of_range, std::invalid_argument)
{
	try
	{
		MainMenu::Reset();
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

void	my::SchmupScene::InitializePlayer(XMLNode::XMLNodePtr playerNode) throw (std::out_of_range, std::invalid_argument)
{
	try
	{
		if (!(m_player = ObjectPool::CreatePlayer(playerNode)))
			throw (std::invalid_argument("SchmupScene: InitializePlayer: can't create player"));
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

void my::SchmupScene::draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept
{
	MainMenu::draw(target, states);
	states.transform *= getTransform();
	if (m_player)
		target.draw(*m_player, states);
}
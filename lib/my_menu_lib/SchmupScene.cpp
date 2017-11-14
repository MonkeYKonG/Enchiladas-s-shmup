#include "SchmupScene.hpp"

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

void my::SchmupScene::draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept
{
	MainMenu::draw(target, states);
}
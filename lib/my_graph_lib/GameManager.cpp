#include "GameManager.hpp"
#include "MessagesException.hpp"
#include "XMLParser.hpp"
#include "my_menu_lib/MainMenu.hpp"
#include <iostream>

namespace	my
{
	const std::string GameManager::MAIN_XML_PATH = "main.xml";
	const std::string GameManager::SCREEN_NODE = "screen";
	const std::string GameManager::SCREEN_VIDEOMODE_NODE = "videoMode";
	const std::string GameManager::SCREEN_VIDEOMODE_WIDTH_NODE = "width";
	const std::string GameManager::SCREEN_VIDEOMODE_HEIGHT_NODE = "height";
	const std::string GameManager::SCREEN_VIDEOMODE_BPP_NODE = "bitsPerPixel";
	const std::string GameManager::SCREEN_TITLE_NODE = "title";
	const std::string GameManager::SCENES_NODE = "scenes";

	void	GameManager::InitializeWindow(XMLNode::XMLNodePtr windowRoot) throw (std::out_of_range, std::invalid_argument)
	{
		sf::VideoMode vm;
		std::string windowName;
		XMLNode::XMLNodePtr videoModeNode;

		try
		{
			videoModeNode = windowRoot->GetChild(SCREEN_VIDEOMODE_NODE);
			vm.width = std::stoul(videoModeNode->GetChild(SCREEN_VIDEOMODE_WIDTH_NODE)->GetValue());
			vm.height = std::stoul(videoModeNode->GetChild(SCREEN_VIDEOMODE_HEIGHT_NODE)->GetValue());
			vm.bitsPerPixel = std::stoul(videoModeNode->GetChild(SCREEN_VIDEOMODE_BPP_NODE)->GetValue());
			windowName = windowRoot->GetChild(SCREEN_TITLE_NODE)->GetValue();
			m_window.create(vm, windowName);
			m_window.setFramerateLimit(60);
			m_window.curScene = 0;
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

	void	GameManager::Initialize() throw (std::out_of_range, std::invalid_argument)
	{
		XMLNode::XMLNodePtr initRoot;

		try
		{
			initRoot = XMLParser::Load(MAIN_XML_PATH);
			InitializeWindow(initRoot->GetChild(SCREEN_NODE));
			InitializeScenes(initRoot->GetChild(SCENES_NODE));
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

	void	GameManager::Update() throw (std::exception)
	{
		try
		{
			if (m_window.scenes.empty())
				throw (std::invalid_argument("scenes not initialized"));
			switch (m_window.scenes[m_window.curScene]->Update(m_window).value)
			{
			case CLOSE:
				m_window.close();
				break;

			default:
				break;
			}
		}
		catch (const std::exception &e)
		{
			m_window.close();
			throw (e);
		}
	}

	void	GameManager::Draw() noexcept
	{
		m_window.clear();
		if (m_window.scenes.size())
			m_window.draw(*(m_window.scenes[m_window.curScene]));
		m_window.display();
	}

	void	GameManager::Loop() throw (std::out_of_range, std::invalid_argument)
	{
		try
		{
			Initialize();
			while(m_window.isOpen())
			{
				Update();
				Draw();
			}
		}
		catch (const std::out_of_range &e)
		{
			throw (e);
		}
		catch (const std::invalid_argument & e)
		{
			throw (e);
		}
	}
}
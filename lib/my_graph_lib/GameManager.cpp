#include "GameManager.hpp"
#include "MessagesException.hpp"
#include "XMLParser.hpp"
#include <iostream>

namespace	my
{
	void	GameManager::InitializeWindow(XMLNode::XMLNodePtr windowRoot) throw (std::invalid_argument)
	{
		sf::VideoMode vm;
		std::string windowName;
		XMLNode::XMLNodePtr videoModePtr;

		try
		{
			videoModePtr = windowRoot->GetChild("videoMode");
			vm.width = std::stoul(videoModePtr->GetChild("width")->GetValue());
			vm.height = std::stoul(videoModePtr->GetChild("height")->GetValue());
			vm.bitsPerPixel = std::stoul(videoModePtr->GetChild("bitsPerPixel")->GetValue());
			windowName = windowRoot->GetChild("title")->GetValue();
			m_window = WindowBuffer::WindowBufferPtr(new WindowBuffer());
			m_window->create(vm, windowName);
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

	void	GameManager::Initialize() throw (std::invalid_argument)
	{
		XMLNode::XMLNodePtr initRoot;

		try
		{
			initRoot = XMLParser::Load("resources/xmls/main.xml");
			InitializeWindow(initRoot);
		}
		catch (const std::exception & e)
		{
			throw (e);
		}
	}

	void	GameManager::Update() throw (std::exception)
	{
		try
		{
			switch (m_window->scenes[m_window->curScene]->Update(*m_window).value)
			{
			case CLOSE:
				m_window->close();
				break;

			default:
				break;
			}
		}
		catch (const std::exception &e)
		{
			throw (e);
		}
	}

	void	GameManager::Draw() noexcept
	{
		m_window->clear();
		m_window->draw(*(m_window->scenes[m_window->curScene]));
		m_window->display();
	}

	void	GameManager::Loop() throw (std::exception)
	{
		try
		{
			Initialize();
			while(m_window && m_window->isOpen())
			{
				Update();
				Draw();
			}
		}
		catch (const std::exception &e)
		{
			throw (e);
		}
	}
}
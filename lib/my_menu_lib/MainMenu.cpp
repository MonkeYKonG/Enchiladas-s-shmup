#include "MainMenu.hpp"
#include "my_objects_lib/ObjectPool.hpp"

#include <iostream>

namespace	my
{
	const std::string	MainMenu::SCENE_BACKGROUND_NODE = "background";
	const std::string	MainMenu::SCENE_PANEL_NODE = "panel";
	const std::string	MainMenu::SCENE_CURSOR_NODE = "cursor";

	MainMenu::MainMenu()
	{
		InitializeFunctions();
	}

	MainMenu::~MainMenu()
	{}

	const SceneReturnValue	MainMenu::Update(sf::RenderWindow & window) throw (std::exception)
	{
		SceneReturnValue returnValue;

		PollEvents(window);
		for (unsigned i = 0; i < m_events.size(); ++i)
		{
			if (m_events[i].type == sf::Event::Closed)
			{
				window.close();
				returnValue.value = CLOSE;
				return (returnValue);
			}
			else if (m_events[i].type == sf::Event::KeyPressed && m_events[i].key.code == sf::Keyboard::Escape)
			{
				window.close();
				returnValue.value = CLOSE;
				return (returnValue);	
			}
		}
		m_cursor->setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
		return (returnValue);
	}

	void	MainMenu::InitializeFunctions() noexcept
	{
		m_initializationFunctions.push_back(InitFunctionPair(SCENE_BACKGROUND_NODE, &MainMenu::InitializeBackground));
		m_initializationFunctions.push_back(InitFunctionPair(SCENE_PANEL_NODE, &MainMenu::InitializePanel));
		m_initializationFunctions.push_back(InitFunctionPair(SCENE_CURSOR_NODE, &MainMenu::InitializeCursor));
	}

	void	MainMenu::InitializeCursor(XMLNode::XMLNodePtr cursorNode) throw (std::out_of_range, std::invalid_argument)
	{
		if (!(m_cursor = ObjectPool::CreateCursor(cursorNode)))
			throw (std::invalid_argument("InitializeCursor: can't create crusor: invalid node"));
	}

	void	MainMenu::InitializeBackground(XMLNode::XMLNodePtr backgroundNode) throw (std::out_of_range, std::invalid_argument)
	{
		if (!(m_background = ObjectPool::CreateSprite(backgroundNode)))
			throw (std::invalid_argument("InitializeBackground: can't create background: invalid node"));
		// set background to center of screen
	}

	void	MainMenu::InitializePanel(XMLNode::XMLNodePtr panelNode) throw (std::out_of_range, std::invalid_argument)
	{
		Panel::PanelPtr newPanel;

		if (!(newPanel = ObjectPool::CreatePanel(panelNode)))
			throw (std::invalid_argument("InitializePanel: can't create panel: invalid node"));
		m_panels.push_back(newPanel);
		// normaly panel is fully declared
	}

	void	MainMenu::Initialize(XMLNode::XMLNodePtr sceneRoot) throw (std::out_of_range, std::invalid_argument)
	{
		unsigned j;

		m_root = sceneRoot;
		try
		{
			for (unsigned i = 0; i < m_root->GetChilds().size(); ++i)
			{
				j = 0;
				while (j < m_initializationFunctions.size())
				{
					if (m_root->GetChilds()[i]->GetName() == m_initializationFunctions[j].first)
					{
						(this->*m_initializationFunctions[j].second)(m_root->GetChilds()[i]);
						break;
					}
					j++;
				}
				if (j >= m_initializationFunctions.size())
					throw (std::invalid_argument("unknow object: " + m_root->GetChilds()[i]->GetName()));
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

	void	MainMenu::Reset() throw (std::out_of_range, std::invalid_argument)
	{
		m_background = 0;
		try
		{
			Initialize(m_root);
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

	void	MainMenu::draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept
	{
		states.transform *= getTransform();
		if (m_background)
			target.draw(*m_background, states);
		for (unsigned i = 0; i < m_panels.size(); ++i)
			target.draw(*m_panels[i], states);
		if (m_cursor)
		target.draw(*m_cursor , states);
	}
}
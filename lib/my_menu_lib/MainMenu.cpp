#include "MainMenu.hpp"
#include "my_graph_lib/ResourcesLoader.hpp"

namespace	my
{
	const std::string	MainMenu::SCENE_BACKGROUND_NODE = "background";
	
	MainMenu::MainMenu()
	{}

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
	}

	void	MainMenu::Initialize(XMLNode::XMLNodePtr sceneRoot) throw (std::out_of_range, std::invalid_argument)
	{
		m_root = sceneRoot;

		try
		{
			for (unsigned i = 0; i < m_root->GetChilds().size(); ++i)
			{
				if (m_root->GetChilds()[i]->GetName() == SCENE_BACKGROUND_NODE)
				{
					m_background = SpriteObject::SpriteObjectPtr(new SpriteObject());
					m_background->SetTexture(ResourcesLoader::GetTexture(m_root->GetChilds()[i]->GetValue()));
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
	}
}
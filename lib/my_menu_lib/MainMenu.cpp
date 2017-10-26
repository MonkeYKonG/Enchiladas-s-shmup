#include "MainMenu.hpp"

namespace	my
{
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

	void	MainMenu::Initialize() noexcept
	{
		
	}

	void	MainMenu::Reset() noexcept
	{

	}

	void	MainMenu::draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept
	{

	}
}
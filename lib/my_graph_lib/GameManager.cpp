#include "GameManager.hpp"
#include "MessagesException.hpp"

namespace	my
{
	void	GameManager::Loop() throw (std::exception)
	{
		try
		{
			Initialize();
			while(!m_windows.empty())
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

	void	GameManager::Initialize() throw (std::invalid_argument)
	{
		for (auto it = m_windows.begin(); it != m_windows.end(); ++it)
		{
			(*it)->scenes[(*it)->curScene]->Initialize();
		}
	}

	void	GameManager::Update() throw (std::exception)
	{
		std::list<WindowBuffer::WindowBufferPtr>::iterator it;
		try
		{
			it = m_windows.begin();
			while (it != m_windows.end())
			{
				switch ((*it)->scenes[(*it)->curScene]->Update((*it)->window).value)
				{
				case CLOSE:
					it = m_windows.erase(it);
					break;

				default:
					it++;
					break;
				}
			}

		}
		catch (const std::exception &e)
		{
			throw (e);
		}
	}

	void	GameManager::Draw() noexcept
	{
		for (auto it = m_windows.begin(); it != m_windows.end(); ++it)
		{
			(*it)->window.clear();
			(*it)->window.draw(*(*it)->scenes[(*it)->curScene]);
			(*it)->window.display();
		}
	}

	void	GameManager::AddWindow(WindowBuffer::WindowBufferPtr newWindow) noexcept
	{
		m_windows.push_back(newWindow);
	}

	void	GameManager::CloseWindow(int index) throw (std::out_of_range)
	{
		auto it = m_windows.begin();

		while (index-- && it != m_windows.end())
			it++;
		if (index != 0)
			throw (std::out_of_range(MessagesException::InvalidIndex("GameManager::CloseWindow(int index)", "index", index)));
		(*it)->window.close();
		m_windows.remove(*it);
	}
}
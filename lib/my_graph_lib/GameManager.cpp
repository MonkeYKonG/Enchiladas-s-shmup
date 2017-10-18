#include "GameManager.hpp"
#include "MessagesException.hpp"

namespace	my
{
	void	GameManager::Loop() throw (std::exception)
	{
		try
		{
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

	void	GameManager::Update() throw (std::exception)
	{
		try
		{
			for (auto it = m_windows.begin(); it != m_windows.end(); ++it)
				(void)(*it)->scenes[(*it)->curScene]->Update((*it)->window);
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
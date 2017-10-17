#include "GameManager.hpp"

namespace	my
{
	void	GameManager::Loop()
	{
		while(!m_windows.empty())
		{
			Update();
			Draw();
		}
	}

	void	GameManager::Update()
	{
		for (auto it = m_windows.begin(); it != m_windows.end(); ++it)
			(void)(*it)->scenes[(*it)->curScene]->Update((*it)->window);
	}

	void	GameManager::Draw()
	{
		for (auto it = m_windows.begin(); it != m_windows.end(); ++it)
		{
			(*it)->window.clear();
			(*it)->window.draw(*(*it)->scenes[(*it)->curScene]);
			(*it)->window.display();
		}
	}

	void	GameManager::AddWindow(WindowBufferPtr newWindow)
	{
		m_windows.push_back(newWindow);
	}

	void	GameManager::CloseWindow(int index)
	{
		auto it = m_windows.begin();

		while (index--)
			it++;
		(*it)->window.close();
		m_windows.remove(*it);
	}
}
#pragma once

#include <list>
#include "WindowBuffer.hh"

namespace	my
{
	class 	GameManager
	{
	public:
		virtual ~GameManager() {}

		void			Loop();
		void			AddWindow(WindowBufferPtr newWindow);
		void			CloseWindow(int index);
		
	protected:
		virtual void	Update();
		virtual void	Draw();

		std::list<WindowBufferPtr>	m_windows;
	};
}
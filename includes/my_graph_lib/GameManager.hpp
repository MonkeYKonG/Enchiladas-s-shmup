#pragma once

#include <stdexcept>
#include <list>
#include "WindowBuffer.hh"

namespace	my
{
	class 	GameManager
	{
	public:
		virtual ~GameManager() noexcept {}

		void			Loop() throw (std::exception);
		void			AddWindow(WindowBuffer::WindowBufferPtr newWindow) noexcept;
		void			CloseWindow(int index) throw (std::out_of_range);
		
	protected:
		virtual void	Initialize() throw (std::invalid_argument);
		virtual void	Update() throw (std::exception);
		virtual void	Draw() noexcept;

		std::list<WindowBuffer::WindowBufferPtr>	m_windows;
	};
}
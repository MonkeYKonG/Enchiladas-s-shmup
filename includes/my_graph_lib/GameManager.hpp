#pragma once

#include <stdexcept>
#include <list>
#include "WindowBuffer.hh"
#include "XMLNode.hpp"

namespace	my
{
	class 	GameManager
	{
	public:
		virtual ~GameManager() noexcept {}

		void			Loop() throw (std::exception);
		
	protected:
		virtual void	InitializeWindow(XMLNode::XMLNodePtr windowRoot) throw (std::out_of_range, std::invalid_argument);
		virtual void	InitializeScenes(XMLNode::XMLNodePtr scenesRoot) throw (std::out_of_range, std::invalid_argument) = 0;
		virtual void	Initialize() throw (std::invalid_argument);
		virtual void	Update() throw (std::exception);
		virtual void	Draw() noexcept;

		WindowBuffer	m_window;
	};
}
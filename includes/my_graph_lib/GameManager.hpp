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

		void			Loop() throw (std::out_of_range, std::invalid_argument);
		
	protected:
		virtual void	InitializeWindow(XMLNode::XMLNodePtr windowRoot) throw (std::out_of_range, std::invalid_argument);
		virtual void	InitializeScenes(XMLNode::XMLNodePtr scenesRoot) throw (std::out_of_range, std::invalid_argument) = 0;
		virtual void	Initialize() throw (std::out_of_range, std::invalid_argument);
		virtual void	Update() throw (std::exception);
		virtual void	Draw() noexcept;

		WindowBuffer	m_window;

	private:
		static const std::string	MAIN_XML_PATH;

		static const std::string	SCREEN_NODE;
		static const std::string	SCREEN_VIDEOMODE_NODE;
		static const std::string	SCREEN_VIDEOMODE_WIDTH_NODE;
		static const std::string	SCREEN_VIDEOMODE_HEIGHT_NODE;
		static const std::string	SCREEN_VIDEOMODE_BPP_NODE;
		static const std::string	SCREEN_TITLE_NODE;

		static const std::string	SCENES_NODE;
	};
}
#pragma once

#include "my_menu_lib/MainMenu.hpp"

namespace my
{
	namespace schmup
	{
		class SchmupMainMenu : public MainMenu
		{
		public:
			SchmupMainMenu();
			~SchmupMainMenu();

			const SceneReturnValue	Update(sf::RenderWindow & window) throw (std::exception);
			void Initialize(XMLNode::XMLNodePtr sceneRoot) throw (std::out_of_range, std::invalid_argument);
			void Reset() throw (std::out_of_range, std::invalid_argument);

		private:
			typedef const SceneReturnValue(SchmupMainMenu::*UpdatePanelFunctions)();
			typedef std::map<unsigned, UpdatePanelFunctions> UpdatePanelFunctionsMap;
			enum
			{
				MAIN_PANEL = 0,
				PLAY_PANEL,
				OPTION_PANEL
			};
			enum
			{
				PLAY_BUTTON = 0,
				OPTION_BUTTON,
				QUIT_BUTTON
			};
			enum
			{
				SINGLE_PLAYER = 0,
				MULTI_PLAYER,
				PLAY_BACK
			};
			enum
			{
				OPTION_BACK = 0
			};

			void ChangeCurrentPanel(unsigned newIndex) throw (std::out_of_range);
			void InitializePanelFunctions();
			const SceneReturnValue UpdateMainPanel();
			const SceneReturnValue UpdatePlayPanel();
			const SceneReturnValue UpdateOptionPanel();
			const SceneReturnValue UpdatePanels() throw (std::out_of_range);

			unsigned m_curPanel;
			unsigned m_curButtonClicked;
			bool m_buttonCLicked;
			UpdatePanelFunctionsMap m_panelfunctions;
		};
	}
}
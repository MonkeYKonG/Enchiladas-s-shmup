#include "SchmupMainMenu.hpp"
#include "my_graph_lib/InputsManager.hpp"

my::schmup::SchmupMainMenu::SchmupMainMenu()
	: m_curPanel(MAIN_PANEL), m_curButtonClicked(0), m_buttonCLicked(false)
{}

my::schmup::SchmupMainMenu::~SchmupMainMenu()
{}

void my::schmup::SchmupMainMenu::ChangeCurrentPanel(unsigned newIndex) throw (std::out_of_range)
{
	try
	{
		if (newIndex >= m_panels.size())
			throw (std::out_of_range("index is upper than panel list size"));
		m_panels[m_curPanel]->SetVisible(false);
		m_curPanel = newIndex;
		m_panels[m_curPanel]->SetVisible(true);
	}
	catch (const std::out_of_range & e)
	{
		throw (std::out_of_range("SchmupMainMenu::ChangeCurrentPanel: " + std::string(e.what())));
	}
}

void my::schmup::SchmupMainMenu::InitializePanelFunctions()
{
	m_panelfunctions[MAIN_PANEL] = &SchmupMainMenu::UpdateMainPanel;
	m_panelfunctions[PLAY_PANEL] = &SchmupMainMenu::UpdatePlayPanel;
	m_panelfunctions[OPTION_PANEL] = &SchmupMainMenu::UpdateOptionPanel;
}

const my::SceneReturnValue my::schmup::SchmupMainMenu::UpdateMainPanel()
{
	SceneReturnValue returnValue;
	Panel::SpriteButtons panelButtons;

	panelButtons = m_panels[m_curPanel]->GetSpriteButtons();
	for (unsigned i = 0; i < panelButtons.size(); ++i)
	{
		if (panelButtons[i]->IsMouseOvered() && InputsManager::IsButtonReleasedOne(sf::Mouse::Left))
		{
			switch (i)
			{
			case PLAY_BUTTON:
				ChangeCurrentPanel(PLAY_PANEL);
				break;

			case OPTION_BUTTON:
				ChangeCurrentPanel(OPTION_PANEL);
				break;

			case QUIT_BUTTON:
				returnValue.value = STATE_RETURN::CLOSE;
				return (returnValue);
			}
		}
	}
	return SceneReturnValue();
}

const my::SceneReturnValue my::schmup::SchmupMainMenu::UpdatePlayPanel()
{
	SceneReturnValue returnValue;
	Panel::SpriteButtons panelButtons;

	panelButtons = m_panels[m_curPanel]->GetSpriteButtons();
	for (unsigned i = 0; i < panelButtons.size(); ++i)
	{
		if (panelButtons[i]->IsMouseOvered() && InputsManager::IsButtonReleasedOne(sf::Mouse::Left))
		{
			switch (i)
			{
			case SINGLE_PLAYER:
				ChangeCurrentPanel(PLAY_PANEL);
				break;

			case MULTI_PLAYER:
				ChangeCurrentPanel(PLAY_PANEL);
				break;

			case PLAY_BACK:
				ChangeCurrentPanel(MAIN_PANEL);
				break;
			}
		}
	}
	return SceneReturnValue();
}

const my::SceneReturnValue my::schmup::SchmupMainMenu::UpdateOptionPanel()
{
	SceneReturnValue returnValue;
	Panel::SpriteButtons panelButtons;

	panelButtons = m_panels[m_curPanel]->GetSpriteButtons();
	for (unsigned i = 0; i < panelButtons.size(); ++i)
	{
		if (panelButtons[i]->IsMouseOvered() && InputsManager::IsButtonReleasedOne(sf::Mouse::Left))
		{
			switch (i)
			{
			case OPTION_BACK:
				ChangeCurrentPanel(MAIN_PANEL);
				break;
			}
		}
	}
	return SceneReturnValue();
}

const my::SceneReturnValue	my::schmup::SchmupMainMenu::UpdatePanels() throw (std::out_of_range)
{
	try
	{
		return ((this->*m_panelfunctions.at(m_curPanel))());
	}
	catch (const std::out_of_range & e)
	{
		throw (e);
	}
}

const my::SceneReturnValue my::schmup::SchmupMainMenu::Update(sf::RenderWindow & window) throw (std::exception)
{
	SceneReturnValue returnValue;

	try
	{
		returnValue = MainMenu::Update(window);
		if (returnValue.value == STATE_RETURN::CLOSE)
			return (returnValue);
		returnValue = UpdatePanels();
	}
	catch (const std::exception & e)
	{
		throw (e);
	}
	return (returnValue);
}

void my::schmup::SchmupMainMenu::Initialize(my::XMLNode::XMLNodePtr sceneRoot) throw (std::out_of_range)
{
	try
	{
		MainMenu::Initialize(sceneRoot);
		for (unsigned i = 0; i < m_panels.size(); ++i)
		{
			if (i == MAIN_PANEL)
				m_panels[i]->SetVisible(true);
			else
				m_panels[i]->SetVisible(false);
		}
		InitializePanelFunctions();
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

void my::schmup::SchmupMainMenu::Reset() throw (std::out_of_range, std::invalid_argument)
{
	try
	{
		MainMenu::Reset();
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
#include "Panel.hpp"

#include <iostream>

namespace my
{
	Panel::Panel()
	{}

	Panel::~Panel()
	{}

	bool	Panel::IsIntersect(const sf::Vector2f & point) const noexcept
	{
		return (false);
	}

	bool	Panel::IsIntersect(const sf::FloatRect & square) const noexcept
	{
		return (false);
	}

	SpriteObject::SpriteObjectPtr	Panel::GetBackground() const noexcept
	{
		return (m_background);
	}

	Border::BorderPtr	Panel::GetBorder() const noexcept
	{
		return (m_border);
	}

	TextObject::TextObjectPtr	Panel::GetTitle() const noexcept
	{
		return (m_title);
	}

	const Panel::SpriteButtons &Panel::GetSpriteButtons() const noexcept
	{
		return (m_spriteButtons);
	}

	const Panel::TextButtons &Panel::GetTextButtons() const noexcept
	{
		return (m_textButtons);
	}

	void	Panel::SetBackground(SpriteObject::SpriteObjectPtr background) noexcept
	{
		m_background = background;
	}

	void	Panel::SetBorder(Border::BorderPtr border) noexcept
	{
		m_border = border;
	}

	void	Panel::SetTitle(TextObject::TextObjectPtr title) noexcept
	{
		m_title = title;
		m_title->SetOrigin(m_title->GetText().getGlobalBounds().width / 2, m_title->GetText().getGlobalBounds().height / 2);
		if (m_background)
			m_title->setPosition(0, -m_background->GetSprite().getGlobalBounds().height / 2 + m_title->GetText().getGlobalBounds().height);
	}

	void	Panel::SetSpriteButtons(const Panel::SpriteButtons & buttons) noexcept
	{
		m_spriteButtons = buttons;
	}

	void	Panel::AddSpriteButton(const Panel::SpriteButton & newButton) noexcept
	{
		m_spriteButtons.push_back(newButton);
	}

	void	Panel::SetTextButtons(const Panel::TextButtons & buttons) noexcept
	{
		m_textButtons.clear();
		for (unsigned i = 0; i < buttons.size(); ++i)
			AddTextButton(buttons[i]);
	}

	void	Panel::AddTextButton(const Panel::TextButton & newButton) noexcept
	{
		m_textButtons.push_back(newButton);
		newButton->SetOrigin(newButton->GetText().getGlobalBounds().width / 2, newButton->GetText().getGlobalBounds().height / 2);
	}

	void	Panel::UpdateBackground() noexcept
	{
		if (!m_background)
			return;
		m_background->Update();
	}

	void	Panel::UpdateBorder() noexcept
	{
		if (!m_border)
			return;
		m_border->Update();
	}

	void	Panel::UpdateTitle() noexcept
	{
		if (!m_title)
			return;
		m_title->Update();
	}

	void	Panel::UpdateSpriteButtons() noexcept
	{
		for (unsigned i = 0; i < m_spriteButtons.size(); ++i)
			m_spriteButtons[i]->Update();
	}

	void	Panel::UpdateTextButtons() noexcept
	{
		for (unsigned i = 0; i < m_textButtons.size(); ++i)
			m_textButtons[i]->Update();
	}

	void	Panel::UpdateButtons() noexcept
	{
		UpdateSpriteButtons();
		UpdateTextButtons();
	}

	void	Panel::Update(const sf::Vector2f & mousePos) noexcept
	{
		sf::Vector2f tranfromedMousePos;

		tranfromedMousePos = getTransform().getInverse().transformPoint(mousePos);
		UpdateBackground();
		UpdateBorder();
		UpdateTitle();
		UpdateButtons();
	}

	void	Panel::draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept
	{
		if (!m_visible)
			return;
		Node::draw(target, states);
		states.transform *= getTransform();
		if (m_background)
			target.draw(*m_background, states);
		if (m_border)
			target.draw(*m_border, states);
		if (m_title)
			target.draw(*m_title, states);
		for (unsigned i = 0; i < m_spriteButtons.size(); ++i)
			target.draw(*m_spriteButtons[i], states);
		for (unsigned i = 0; i < m_textButtons.size(); ++i)
			target.draw(*m_textButtons[i], states);
	}
}
#include "Panel.hpp"

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

	void	Panel::Update(const sf::Vector2f & mousePos) noexcept
	{

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
	}
}
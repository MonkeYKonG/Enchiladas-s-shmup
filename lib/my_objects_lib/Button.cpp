#include "Button.hpp"

namespace my
{
	Button::Button()
		: m_activate(true), m_isClicked(false)
	{}

	Button::~Button()
	{}

	bool Button::IsIntersect(const sf::Vector2f & point) const noexcept
	{
		if (m_sprite && m_sprite->IsIntersect(point))
			return (true);
		if (m_text && m_text->IsIntersect(point))
			return (true);
		return false;
	}

	bool Button::IsIntersect(const sf::FloatRect & square) const noexcept
	{
		if (m_sprite && m_sprite->IsIntersect(square))
			return (true);
		if (m_text && m_text->IsIntersect(square))
			return (true);
		return false;
	}

	void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept
	{
		if (!m_visible)
			return;
		Node::draw(target, states);
		states.transform *= getTransform();
		if (m_sprite)
			target.draw(*m_sprite, states);
		if (m_text)
			target.draw(*m_text, states);
	}
}
#include "Panel.hpp"

namespace my
{
	Panel::Panel()
	{}

	Panel::~Panel()
	{}

	bool	Panel::IsIntersect() const noexcept
	{
		return (false);
	}

	SpriteObject::SpriteObjectPtr	Panel::GetBackground() const noexcept
	{
		return (m_background);
	}

	SpriteObject::SpriteObjectPtr	Panel::GetBorder() const noexcept
	{
		return (m_border);
	}

	TextObject::TextObjectPtr	Panel::GetTitle() const noexcept
	{
		return (m_title);
	}

	const Panel::UpdatableList	&Panel::GetUpdatableObjects() const noexcept
	{
		return (m_updatableObjects);
	}

	void	Panel::SetBackground(SpriteObject::SpriteObjectPtr background) noexcept
	{
		m_background = background;
	}

	void	Panel::SetBorder(SpriteObject::SpriteObjectPtr border) noexcept
	{
		m_border = border;
	}

	void	Panel::SetTitle(TextObject::TextObjectPtr title) noexcept
	{
		m_title = title;
	}

	void	Panel::SetUpdatableList(const UpdatableList & updatableList) noexcept
	{
		m_updatableObjects = updatableList;
	}

	void	Panel::Update(const sf::Vector2f & mousePos) noexcept
	{

	}
}
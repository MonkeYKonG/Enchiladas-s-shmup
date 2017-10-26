#include "MousePointer.hpp"

namespace	my
{
	MousePointer::MousePointer()
	: m_onMoove(false), m_leftClick(false), m_rightClick(false)
	{}

	MousePointer::~MousePointer()
	{}

	bool	MousePointer::IsOnMoove() const noexcept
	{
		return (m_onMoove);
	}

	bool	MousePointer::IsLeftClick() const noexcept
	{
		return (m_leftClick);
	}

	bool	MousePointer::IsRightClick() const noexcept
	{
		return (m_rightClick);
	}

	void	MousePointer::SetOnMoove(bool onMoove) noexcept
	{
		m_onMoove = onMoove;
	}

	void	MousePointer::SetLeftClick(bool leftClick) noexcept
	{
		m_leftClick = leftClick;
	}

	void	MousePointer::SetRightClick(bool rightClick) noexcept
	{
		m_rightClick = rightClick;
	}

	void	MousePointer::SetMoovingAnimation(const AnimatedObject::Animation & animation) noexcept
	{

	}

	void	MousePointer::SetLeftClickAnimation(const AnimatedObject::Animation & animation) noexcept
	{
		
	}

	void	MousePointer::SetRightClickAnimation(const AnimatedObject::Animation & animation) noexcept
	{
		
	}
}
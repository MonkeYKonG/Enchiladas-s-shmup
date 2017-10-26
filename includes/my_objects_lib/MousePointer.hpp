#pragma once

#include "my_graph_lib/SpriteObject.hpp"
#include "my_graph_lib/AnimatedObject.hpp"

namespace	my
{
	class MousePointer : public SpriteObject, public AnimatedObject
	{
	public:
		typedef std::shared_ptr<MousePointer> MousePointerPtr;

		MousePointer();
		~MousePointer();

		bool	IsOnMoove() const noexcept;
		bool	IsLeftClick() const noexcept;
		bool	IsRightClick() const noexcept;
		void	SetOnMoove(bool onMoove) noexcept;
		void	SetLeftClick(bool leftClick) noexcept;
		void	SetRightClick(bool rightClick) noexcept;
		void	SetMoovingAnimation(const AnimatedObject::Animation & animation) noexcept;
		void	SetLeftClickAnimation(const AnimatedObject::Animation & animation) noexcept;
		void	SetRightClickAnimation(const AnimatedObject::Animation & animation) noexcept;
		
	private:
		bool	m_onMoove;
		bool	m_leftClick;
		bool	m_rightClick;
	};
}
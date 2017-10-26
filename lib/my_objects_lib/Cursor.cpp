#include "Cursor.hpp"

namespace	my
{
	Cursor::Cursor()
	: m_direction(LEFT)
	{}

	Cursor::~Cursor()
	{}

	Node::NodePtr Cursor::GetTarget() const noexcept
	{
		return (m_target);
	}

	Direction Cursor::GetDirection() const noexcept
	{
		return (m_direction);
	}

	void	Cursor::SetTarget(Node::NodePtr target) noexcept
	{
		m_target = target;
	}

	void 	Cursor::SetDirection(Direction direction) noexcept
	{
		m_direction = direction;
	}
}
#pragma once

#include "my_graph_lib/SpriteObject.hpp"
#include "Direction.hpp"

namespace	my
{
	class Cursor : public SpriteObject
	{
	public:
		typedef std::shared_ptr<Cursor> CursorPtr;

		Cursor();
		~Cursor();

		Node::NodePtr GetTarget() const noexcept;
		Direction GetDirection() const noexcept;
		void SetTarget(Node::NodePtr target) noexcept;
		void SetDirection(Direction direction) noexcept;
		
	private:
		Node::NodePtr	m_target;
		Direction		m_direction;
	};
}
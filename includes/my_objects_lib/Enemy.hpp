#pragma once

#include "my_graph_lib/SpriteObject.hpp"
#include "Shooter.hpp"

namespace my
{
	class Enemy : public SpriteObject, public Shooter
	{
	public:
		typedef std::shared_ptr<Enemy> EnemyPtr;

		Enemy();
		virtual ~Enemy() {}

	protected:

	};
}
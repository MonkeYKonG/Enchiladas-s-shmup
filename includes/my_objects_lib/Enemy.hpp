#pragma once

#include "my_graph_lib/SpriteObject.hpp"
#include "Shooter.hpp"
#include "AliveObject.hpp"

namespace my
{
	class Enemy : public SpriteObject, public Shooter, public AliveObject
	{
	public:
		typedef std::shared_ptr<Enemy> EnemyPtr;

		Enemy();
		virtual ~Enemy() {}

		virtual void Update() throw (std::out_of_range);

		bool IsFinish() const noexcept;

		void SetIsFinish(bool isFinish) noexcept;

	protected:
		virtual void UpdateAnimation() throw (std::out_of_range);

		bool m_isFinish;
	};
}
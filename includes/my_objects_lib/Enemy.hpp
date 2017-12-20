#pragma once

#include "my_graph_lib/SpriteObject.hpp"
#include "Shooter.hpp"

namespace my
{
	class Enemy : public SpriteObject, public Shooter, public AliveObject
	{
	public:
		typedef std::shared_ptr<Enemy> EnemyPtr;

		Enemy();
		virtual ~Enemy() {}

		virtual void Update() throw (std::out_of_range);
		virtual void TakeDamage(unsigned damage) noexcept;

		bool IsFinish() const noexcept;

		void SetIsFinish(bool isFinish) noexcept;

	protected:
		virtual void UpdateAnimation() throw (std::out_of_range);
		virtual unsigned ComputeBulletDamage(Bullet::BulletPtr bullet) const noexcept;

		bool m_isFinish;
	};
}
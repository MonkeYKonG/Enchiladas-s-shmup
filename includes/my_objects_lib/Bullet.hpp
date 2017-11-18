#pragma once

#include "my_graph_lib/SpriteObject.hpp"
#include "AliveObject.hpp"

namespace my
{
	class Bullet : public SpriteObject, public AliveObject
	{
	public:
		typedef std::shared_ptr<Bullet> BulletPtr;

		Bullet();
		virtual ~Bullet() {}

		virtual void Update() throw (std::out_of_range);
		virtual void TakeDamage(unsigned damage) noexcept;

		bool IsFinish() const noexcept;
		unsigned GetTravelTime() const noexcept;
		unsigned GetDamage() const noexcept;

		void SetTravelTime(unsigned travelTime) noexcept;
		void SetDamage(unsigned damage) noexcept;

	protected:
		virtual void UpdateAnimation() throw (std::out_of_range);

		unsigned	m_travelTime;
		unsigned	m_damage;

	private:
		unsigned	m_bulletFramerate;
	};
}
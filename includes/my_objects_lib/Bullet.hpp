#pragma once

#include "my_graph_lib/SpriteObject.hpp"

namespace my
{
	class Bullet : public SpriteObject
	{
	public:
		typedef std::shared_ptr<Bullet> BulletPtr;

		Bullet();
		virtual ~Bullet() {}

		virtual void Update() throw (std::out_of_range);

		bool IsFinish() const noexcept;
		unsigned GetTravelTime() const noexcept;

		void SetTravelTime(unsigned travelTime) noexcept;

	protected:
		virtual void UpdateAnimation() throw (std::out_of_range);

		unsigned	m_travelTime;

	private:
		unsigned	m_bulletFramerate;
	};
}
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

		unsigned GetTravelTime() const noexcept;

		void SetTravelTime(unsigned travelTime) noexcept;

	protected:
		unsigned	m_travelTime;

	private:
		unsigned	m_bulletFramerate;
	};
}
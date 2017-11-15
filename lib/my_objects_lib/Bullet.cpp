#include "Bullet.hpp"

my::Bullet::Bullet()
	: m_travelTime(0), m_bulletFramerate(0)
{}

void my::Bullet::Update() throw(std::out_of_range)
{
	try
	{
		if (m_bulletFramerate < m_travelTime)
			m_bulletFramerate++;
		SpriteObject::Update();
	}
	catch (const std::out_of_range & e)
	{
		throw (e);
	}
}

bool my::Bullet::IsFinish() const noexcept
{
	return (m_bulletFramerate >= m_travelTime);
}

unsigned my::Bullet::GetTravelTime() const noexcept
{
	return (m_travelTime);
}

void my::Bullet::SetTravelTime(unsigned travelTime) noexcept
{
	m_travelTime = travelTime;
}

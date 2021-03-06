#include "Bullet.hpp"

my::Bullet::Bullet()
	: m_travelTime(0), m_damage(0), m_bulletFramerate(0)
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

void	my::Bullet::TakeDamage(unsigned damage) noexcept
{
	AliveObject::TakeDamage(damage);
	if (!m_isAlive)
	{
		m_onAnimation = true;
		if (AnimationExist(DEATH_ANIM_NAME))
			SetAnimIndex(DEATH_ANIM_NAME);
	}
}

bool my::Bullet::IsFinish() const noexcept
{
	if (!m_isAlive)
	{
		if (AnimationExist(DEATH_ANIM_NAME))
			return (!m_onAnimation);
		return (true);
	}
	return (m_bulletFramerate >= m_travelTime);
}

unsigned my::Bullet::GetTravelTime() const noexcept
{
	return (m_travelTime);
}

unsigned	my::Bullet::GetDamage() const noexcept
{
	return (m_damage);
}

void my::Bullet::SetTravelTime(unsigned travelTime) noexcept
{
	m_travelTime = travelTime;
}

void	my::Bullet::SetDamage(unsigned damage) noexcept
{
	m_damage = damage;
}

void my::Bullet::UpdateAnimation() throw(std::out_of_range)
{
	try
	{
		if (!m_onAnimation)
		{
			if (AnimationExist(DEFAULT_ANIM_NAME))
				SetAnimIndex(DEFAULT_ANIM_NAME);
			m_onAnimation = true;
		}
		SpriteObject::UpdateAnimation();
		setOrigin(GetCurentRect().height / 2, GetCurentRect().width / 2);
	}
	catch (const std::out_of_range & e)
	{
		throw (e);
	}
}

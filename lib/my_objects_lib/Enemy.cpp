#include "Enemy.hpp"

my::Enemy::Enemy()
	: m_isFinish(false)
{
	m_onDeplacement = true;
}

void	my::Enemy::UpdateAnimation() throw (std::out_of_range)
{
	try
	{
		if (!m_onAnimation)
		{
			m_onAnimation = true;
			SetAnimIndex(DEFAULT_ANIM_NAME);
		}
		SpriteObject::UpdateAnimation();
	}
	catch (const std::out_of_range & e)
	{
		throw (e);
	}
}

void	my::Enemy::TakeDamage(unsigned damage) noexcept
{
	AliveObject::TakeDamage(damage);
	if (!m_isAlive && AnimationExist(DEATH_ANIM_NAME))
	{
		m_onAnimation = true;
		SetAnimIndex(DEATH_ANIM_NAME);
	}
}

void my::Enemy::Update() throw(std::out_of_range)
{
	try
	{
		SpriteObject::Update();
	}
	catch (const std::out_of_range & e)
	{
		throw (e);
	}
}

bool my::Enemy::IsFinish() const noexcept
{
	if (!m_isAlive)
	{
		if (AnimationExist(DEATH_ANIM_NAME))
			return (!m_onAnimation);
		return (true);
	}
	return m_isFinish;
}

void my::Enemy::SetIsFinish(bool isFinish) noexcept
{
	m_isFinish = isFinish;
}
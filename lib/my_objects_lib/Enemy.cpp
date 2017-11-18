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
	return m_isFinish;
}

void my::Enemy::SetIsFinish(bool isFinish) noexcept
{
	m_isFinish = isFinish;
}
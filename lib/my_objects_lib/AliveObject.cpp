#include "AliveObject.hpp"

my::AliveObject::AliveObject()
	: m_isAlive(true), m_HP(0), m_maxHP(0)
{}

bool	my::AliveObject::IsAlive() const noexcept
{
	return (m_isAlive);
}

unsigned	my::AliveObject::GetCurHP() const noexcept
{
	return (m_maxHP);
}

unsigned	my::AliveObject::GetMaxHP() const noexcept
{
	return (m_maxHP);
}

void	my::AliveObject::TakeDamage(unsigned damage) noexcept
{
	if (damage > m_HP)
		m_HP = 0;
	else
		m_HP -= damage;
	if (m_HP == 0)
		m_isAlive = false;
}
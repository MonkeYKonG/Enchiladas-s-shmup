#include "AliveObject.hpp"

const std::string my::AliveObject::DEATH_ANIM_NAME = "death";

my::AliveObject::AliveObject()
	: m_isAlive(true), m_HP(1), m_maxHP(1)
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

void	my::AliveObject::SetCurHP(unsigned curHP) throw (std::invalid_argument)
{
	try
	{
		if (curHP > m_maxHP)
			throw (std::invalid_argument("setting HP higher than maxHP"));
		m_HP = curHP;
	}
	catch (const std::invalid_argument & e)
	{
		throw  (std::invalid_argument("AliveObject::SetCurHP\n" + std::string(e.what())));
	}
}

void	my::AliveObject::SetMaxHP(unsigned maxHP) noexcept
{
	m_maxHP = maxHP;
}

void	my::AliveObject::TakeDamage(unsigned damage) noexcept
{
	if (damage > m_HP)
		m_HP = 0;
	else
		m_HP -= (damage / (m_def + 1));
	if (m_HP == 0)
		m_isAlive = false;
}
#include "StatsContainer.hpp"

my::StatsContainer::StatsContainer()
	: m_atk(0), m_def(0)
{
}

unsigned my::StatsContainer::GetAtk() const noexcept
{
	return (m_atk);
}

unsigned my::StatsContainer::GetDef() const noexcept
{
	return (m_def);
}

void my::StatsContainer::SetAtk(unsigned atk) noexcept
{
	m_atk = atk;
}

void my::StatsContainer::SetDef(unsigned def) noexcept
{
	m_def = def;
}
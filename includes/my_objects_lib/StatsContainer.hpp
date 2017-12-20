#pragma once

namespace my
{
	class StatsContainer
	{
	public:
		StatsContainer();
		virtual ~StatsContainer() {}

		unsigned	GetAtk() const noexcept;
		unsigned	GetDef() const noexcept;
		void		SetAtk(unsigned atk) noexcept;
		void		SetDef(unsigned def) noexcept;

	protected:
		unsigned m_atk;
		unsigned m_def;
	};
}
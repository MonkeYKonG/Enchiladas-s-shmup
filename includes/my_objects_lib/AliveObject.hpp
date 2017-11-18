#pragma once

#include <stdexcept>

namespace my
{
	class AliveObject
	{
	public:
		virtual ~AliveObject() {}

		bool IsAlive() const noexcept;
		unsigned GetCurHP() const noexcept;
		unsigned GetMaxHP() const noexcept;

		void SetCurHP(unsigned curHP) throw (std::invalid_argument);
		void SetMaxHP(unsigned maxHP) noexcept;

		virtual void TakeDamage(unsigned damage) noexcept;

	protected:
		AliveObject();

		bool m_isAlive;
		unsigned m_HP;
		unsigned m_maxHP;
	};
}
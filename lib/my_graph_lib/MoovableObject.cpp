#include "MoovableObject.hpp"

namespace	my
{
	template <typename T>
	sf::Vector2<T>	NormalizeVector(const sf::Vector2<T> & vector)
	{
		float length = sqrt((vector.x * vector.x) + (vector.y * vector.y));
		if (length != 0)
			return sf::Vector2f(vector.x / length, vector.y / length);
		else
			return vector;
	}

	MoovableObject::MoovableObject() noexcept
		: m_onDeplacement(false), m_canMove(false), m_speed(0), m_frameRate(0), m_deplacementRate(0), m_deplacementRepetition(-1), m_repetitionMax(-1), m_target(0)
	{}

	void	MoovableObject::UpdateMovement()
	{
		m_canMove = false;
		if (!m_onDeplacement)
			return;
		if (++m_frameRate < m_deplacementRate)
			return;
		m_frameRate = 0;
		if (m_target)
			m_direction = NormalizeVector(*m_target);
		if (m_repetitionMax != -1 && ++m_deplacementRepetition >= m_repetitionMax)
		{
			ResetDeplacement();
			return;
		}
		m_canMove = true;
	}

	void	MoovableObject::ResetDeplacement()
	{
		m_onDeplacement = false;
		m_frameRate = 0;
		m_deplacementRepetition = 0;
	}

	void	MoovableObject::ClearDeplacement()
	{
		ResetDeplacement();
		m_speed = 0;
		m_direction = sf::Vector2f();
		m_deplacementRate = 0;
		m_repetitionMax = -1;
		m_target = 0;
	}

	bool	MoovableObject::IsOnDeplacement() const noexcept
	{
		return (m_onDeplacement);
	}

	bool	MoovableObject::CanMove() const noexcept
	{
		return (m_canMove);
	}

	float	MoovableObject::GetSpeed() const noexcept
	{
		return (m_speed);
	}

	const sf::Vector2f&	MoovableObject::GetDirection() const noexcept
	{
		return (m_direction);
	}

	int		MoovableObject::GetFrameRate() const noexcept
	{
		return (m_frameRate);
	}

	int		MoovableObject::GetDeplacememtRate() const noexcept
	{
		return (m_deplacementRate);
	}

	int 	MoovableObject::GetDeplacementRepetition() const noexcept
	{
		return (m_deplacementRepetition);
	}

	int 	MoovableObject::GetRepetitionMax() const noexcept
	{
		return (m_repetitionMax);
	}

	sf::Vector2f	*MoovableObject::GetTarget() const noexcept
	{
		return (m_target);
	}

	void	MoovableObject::SetOnDeplacement(bool onDeplacement) noexcept
	{
		m_onDeplacement = onDeplacement;
	}

	void	MoovableObject::SetSpeed(float speed) noexcept
	{
		m_speed = speed;
	}

	void	MoovableObject::SetDirection(const sf::Vector2f & direction) noexcept
	{
		m_direction = direction;
	}

	void	MoovableObject::SetFrameRate(int framerate) noexcept
	{
		m_frameRate = framerate;
	}

	void	MoovableObject::SetDeplacementRate(int deplacementRate) noexcept
	{
		m_deplacementRate = deplacementRate;
	}

	void	MoovableObject::SetDeplacementRepetition(int deplacementRepetition) noexcept
	{
		m_deplacementRepetition = deplacementRepetition;
	}

	void	MoovableObject::SetRepetitionMax(int repetitionMax) noexcept
	{
		m_repetitionMax = repetitionMax;
	}

	void	MoovableObject::SetTarget(sf::Vector2f * target) noexcept
	{
		m_target = target;
	}
}

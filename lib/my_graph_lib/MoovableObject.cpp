#include "MoovableObject.hpp"

namespace	my
{
	MoovableObject::MoovableObject() noexcept
		: m_onDeplacement(false), m_speed(0), m_frameRate(0), m_deplacementRepetition(0), m_repetitionMax(0)
	{}

	bool	MoovableObject::IsOnDeplacement() const noexcept
	{
		return (m_onDeplacement);
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

	int 	MoovableObject::GetDeplacementRepetition() const noexcept
	{
		return (m_deplacementRepetition);
	}

	int 	MoovableObject::GetRepetitionMax() const noexcept
	{
		return (m_repetitionMax);
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

	void	MoovableObject::SetDeplacementRepetition(int deplacementRepetition) noexcept
	{
		m_deplacementRepetition = deplacementRepetition;
	}

	void	MoovableObject::SetRepetitionMax(int repetitionMax) noexcept
	{
		m_repetitionMax = repetitionMax;
	}
}
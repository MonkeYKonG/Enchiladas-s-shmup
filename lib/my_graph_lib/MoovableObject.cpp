#include "MoovableObject.hpp"

namespace	my
{
	MoovableObject::MoovableObject()
	{}

	void	MoovableObject::Update()
	{
		
	}

	bool	MoovableObject::IsOnDeplacement() const
	{
		return (m_onDeplacement);
	}

	float	MoovableObject::GetSpeed() const
	{
		return (m_speed);
	}

	const sf::Vector2f&	MoovableObject::GetDirection() const
	{
		return (m_direction);
	}

	int		MoovableObject::GetFrameRate() const
	{
		return (m_frameRate);
	}

	int 	MoovableObject::GetDeplacementRepetition() const
	{
		return (m_deplacementRepetition);
	}

	int 	MoovableObject::GetRepetitionMax() const
	{
		return (m_repetitionMax);
	}

	void	MoovableObject::SetSpeed(float speed)
	{
		m_speed = speed;
	}

	void	MoovableObject::SetDirection(const sf::Vector2f & direction)
	{
		m_direction = direction;
	}

	void	MoovableObject::SetFrameRate(int framerate)
	{
		m_frameRate = framerate;
	}

	void	MoovableObject::SetDeplacementRepetition(int deplacementRepetition)
	{
		m_deplacementRepetition = deplacementRepetition;
	}

	void	MoovableObject::SetRepetitionMax(int repetitionMax)
	{
		m_repetitionMax = repetitionMax;
	}
}
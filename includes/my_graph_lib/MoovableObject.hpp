#pragma once

#include <SFML/Graphics.hpp>
#include "IUpdatableObject.hh"

namespace               my
{
  class		            MoovableObject : public IUpdatableObject
  {
  public:
	MoovableObject() noexcept;
	virtual ~MoovableObject() noexcept {}

	virtual void	    Update() = 0;

	bool		        IsOnDeplacement() const noexcept;
	float		        GetSpeed() const noexcept;
	const sf::Vector2f& GetDirection() const noexcept;
	int			        GetFrameRate() const noexcept;
	int			        GetDeplacementRepetition() const noexcept;
	int			        GetRepetitionMax() const noexcept;

	void                SetOnDeplacement(bool onDeplacement) noexcept;
	void		        SetSpeed(float speed) noexcept;
	void		        SetDirection(const sf::Vector2f & direction) noexcept;
	void		        SetFrameRate(int frameRate) noexcept;
	void		        SetDeplacementRepetition(int deplacementRepetition) noexcept;
	void		        SetRepetitionMax(int repetitionMax) noexcept;

  protected:
	bool		  m_onDeplacement;
	float		  m_speed;
	sf::Vector2f  m_direction;
	int			  m_frameRate;
	int			  m_deplacementRepetition;
	int			  m_repetitionMax;
  };
}

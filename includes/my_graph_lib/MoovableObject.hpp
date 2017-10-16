#pragma once

#include "IUpgradableObject.hh"

namespace	my
{
  class		MoovableObject : public IUpdatableObject
  {
  public:
    MoovableObject();
    virtual ~MoovableObject(){}

    virtual void	Update();

    bool		IsOnDeplacement() const;
    float		GetSpeed() const;
    int			GetFrameRate() const;
    int			GetDeplacementRepetition() const;
    int			GetRepetitionMax() const;

    void		SetSpeed(float speed);
    void		SetDirection(const sf::Vector2f & direction);
    void		SetFrameRate(int frameRate);
    void		SetDeplacementRepetition(int deplacementRepetition);
    void		SetRepetitionMax(int repetitionMax);

  protected:
    bool		m_onDeplacement;
    float		m_speed;
    sf::Vector2f	m_direction;
    int			m_frameRate;
    int			m_deplacementRepetition;
    int			m_repetitionMax;
  }
}

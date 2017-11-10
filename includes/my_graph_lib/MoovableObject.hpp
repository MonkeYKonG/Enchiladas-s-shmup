#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

namespace               my
{
  class		            MoovableObject
  {
  public:
  	typedef std::shared_ptr<MoovableObject> MoovableObjectPtr;
  	
	MoovableObject() noexcept;
	virtual ~MoovableObject() noexcept {}

	void				ResetDeplacement();
	void				ClearDeplacement();

	bool		        IsOnDeplacement() const noexcept;
	bool				CanMove() const noexcept;
	float		        GetSpeed() const noexcept;
	const sf::Vector2f	&GetDirection() const noexcept;
	int			        GetFrameRate() const noexcept;
	int					GetDeplacememtRate() const noexcept;
	int			        GetDeplacementRepetition() const noexcept;
	int			        GetRepetitionMax() const noexcept;
	sf::Vector2f		*GetTarget() const noexcept;

	void                SetOnDeplacement(bool onDeplacement) noexcept;
	void		        SetSpeed(float speed) noexcept;
	void		        SetDirection(const sf::Vector2f & direction) noexcept;
	void		        SetFrameRate(int frameRate) noexcept;
	void				SetDeplacementRate(int deplacementRate) noexcept;
	void		        SetDeplacementRepetition(int deplacementRepetition) noexcept;
	void		        SetRepetitionMax(int repetitionMax) noexcept;
	void				SetTarget(sf::Vector2f *target) noexcept;

  protected:
	  virtual void	    UpdateMovement();

	bool		  m_onDeplacement;
	bool			m_canMove;
	float		  m_speed;
	sf::Vector2f  m_direction;
	int			  m_frameRate;
	int			  m_deplacementRate;
	int			  m_deplacementRepetition;
	int			  m_repetitionMax;
	sf::Vector2f	*m_target;
  };

  template <typename T>
  sf::Vector2<T> NormalizeVector(const sf::Vector2<T>& vector);
}

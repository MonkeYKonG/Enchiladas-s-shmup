#pragma once

#include "IUpdatableObject.hh"

namespace	my
{
  class		AnimatedObject : public IUpdatableObject
  {
  public:
    typedef std::vector<sf::intRect>	Animation;

    AnimatedObject();
    virtual ~AnimatedObject(){}

    virtual void		Update();

    sf::intRect			GetCurentTile() const;
    Animated			GetCurentAnimation() const;
    std::vector<Animation>	GetAnimations() const;

    void			SetAnimations();
    void			SetAnimIndex(int index);
    void			SetAnimTileIndex(int tileIndex);

  protected:
    bool			m_onAnimation;
    std::vector<Animation>	m_animations;
    int				m_animIndex;
    int				m_animTileIndex;
  };
}

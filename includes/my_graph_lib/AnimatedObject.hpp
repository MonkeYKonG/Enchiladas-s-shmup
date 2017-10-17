#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "IUpdatableObject.hh"

namespace	my
{
  class		AnimatedObject : public IUpdatableObject
  {
  public:
    typedef std::vector<sf::IntRect>	Animation;

    AnimatedObject();
    virtual ~AnimatedObject(){}

    virtual void		    Update();

    const sf::IntRect&			    GetCurentTile() const;
    const Animation&                GetCurentAnimation() const;
    const std::vector<Animation>&	GetAnimations() const;

    void			                SetAnimations(const std::vector<Animation> & animations);
    void			                SetAnimIndex(int index);
    void			                SetAnimTileIndex(int tileIndex);

  protected:
    bool			         m_onAnimation;
    std::vector<Animation>	 m_animations;
    int			          	 m_animIndex;
    int				         m_animTileIndex;
  };
}

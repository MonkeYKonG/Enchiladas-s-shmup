#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include "IUpdatableObject.hh"

namespace	my
{
  class		AnimatedObject : public IUpdatableObject
  {
  public:
    typedef std::vector<sf::IntRect>	Animation;

    AnimatedObject() noexcept;
    virtual ~AnimatedObject() noexcept {}

    virtual void		    Update();

    const sf::IntRect&			    GetCurentTile() const noexcept;
    const Animation&                GetCurentAnimation() const noexcept;
    const std::vector<Animation>&	GetAnimations() const noexcept;

    void			                SetAnimations(const std::vector<Animation> & animations) noexcept;
    void			                SetAnimIndex(int index) throw (std::out_of_range);
    void			                SetAnimTileIndex(int tileIndex) throw (std::out_of_range);

  protected:
    bool			         m_onAnimation;
    std::vector<Animation>	 m_animations;
    int			          	 m_animIndex;
    int				         m_animTileIndex;
  };
}

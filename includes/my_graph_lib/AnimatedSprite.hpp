#pragma once

#include "SpriteObject.hpp"
#include "AnimatedObject.hpp"

namespace	my
{
  class		AnimatedSprite : public SpriteObject, public AnimatedObject
  {
  public:
    AnimatedSprite();
    virtual ~AnimatedSprite(){}

    virtual void Update();
  };
}

#pragma once

#include "AnimatedObject.hpp"
#include "MoovableObject.hpp"
#include "SpriteObject.hpp"

namespace	my
{
  class		HybridSprite : public AnimatedObject, public MoovableObject, public SpriteObject
  {
  public:
    HybridSprite();
    virtual ~HybridSprite(){}

    virtual void Update();
  };
}
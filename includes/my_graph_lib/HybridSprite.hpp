#pragma once

#include "AnimatedSprite.hpp"
#include "MoovableSprite.hpp"

namespace	my
{
  class		HybridSprite : public AnimatedSprite, public MoovableSprite
  {
  public:
    HybridSprite();
    virtual ~HybridSprite(){}

    virtual void Update();
  };
}

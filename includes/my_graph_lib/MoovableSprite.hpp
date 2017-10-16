#pragma once

#include "SpriteObject.hpp"
#include "MoovableObject.hpp"

namespace	my
{
  class		MoovableSprite : public SpriteObject, public MoovableObject
  {
  public:
    MoovableSprite();
    virtual ~MoovableSprite(){}

    virtual void Update();
  };
}

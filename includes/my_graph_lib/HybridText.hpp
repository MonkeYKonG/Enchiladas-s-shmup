#pragma once

#include "AnimatedObject.hpp"
#include "MoovableObject.hpp"
#include "TextObject.hpp"

namespace	my
{
  class		HybridText : public AnimatedObject, public MoovableObject, public TextObject
  {
  public:
    HybridText();
    virtual ~HybridText(){}

    virtual void Update();
  };
}
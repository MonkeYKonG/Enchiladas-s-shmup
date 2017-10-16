#pragma once

#include "TextObject.hpp"
#include "AnimatedObject.hpp"

namespace	my
{
  class		AnimatedText : public TextObject, public AnimatedObject
  {
  public:
    AnimatedText();
    virtual ~AnimatedText(){}

    virtual void Update();
  };
}

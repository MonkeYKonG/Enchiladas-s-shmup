#pragma once

#include "TextObject.hpp"
#include "MoovableObject.hpp"

namespace	my
{
  class		MoovableText : public TextObject, public MoovableObject
  {
  public:
    MoovableText();
    virtual ~MoovableText(){}

    virtual void Update();
  };
}

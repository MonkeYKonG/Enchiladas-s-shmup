#pragma once

#include "AnimatedObject.hpp"
#include "MoovableObject.hpp"

namespace	my
{
  class		HybridObject : public AnimatedObject, public MoovableObject
  {
  public:
	HybridObject();
	virtual ~HybridObject(){}

	virtual void Update();
  };
}
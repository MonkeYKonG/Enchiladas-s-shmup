#pragma once

#include "AnimatedObject.hpp"
#include "MoovableObject.hpp"

namespace	my
{
  class		HybridObject : public AnimatedObject, public MoovableObject
  {
  public:
  	typedef std::shared_ptr<HybridObject> HybridObjectPtr;

	HybridObject();
	virtual ~HybridObject(){}

	virtual void Update();
  };
}
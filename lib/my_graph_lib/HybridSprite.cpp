#include "HybridSprite.hpp"

namespace	my
{
	HybridSprite::HybridSprite()
	{}

	void	HybridSprite::Update()
	{
		AnimatedObject::Update();
		MoovableObject::Update();
	}
}
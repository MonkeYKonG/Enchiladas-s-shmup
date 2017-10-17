#include "HybridText.hpp"

namespace	my
{
	HybridText::HybridText()
	{}

	void	HybridText::Update()
	{
		AnimatedObject::Update();
		MoovableObject::Update();
	}
}
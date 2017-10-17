#include "AnimatedObject.hpp"

namespace	my
{
	AnimatedObject::AnimatedObject()
	{}

	void	AnimatedObject::Update()
	{}

	const sf::IntRect&	AnimatedObject::GetCurentTile() const
	{
		return (m_animations[m_animIndex][m_animTileIndex]);
	}

	const AnimatedObject::Animation&	AnimatedObject::GetCurentAnimation() const
	{
		return (m_animations[m_animIndex]);
	}

	const std::vector<AnimatedObject::Animation>&	AnimatedObject::GetAnimations() const
	{
		return (m_animations);
	}

	void	AnimatedObject::SetAnimations(const std::vector<AnimatedObject::Animation>& animations)
	{
		m_animations = animations;
	}

	void	AnimatedObject::SetAnimIndex(int index)
	{
		m_animIndex = index;
	}

	void	AnimatedObject::SetAnimTileIndex(int tileIndex)
	{
		m_animTileIndex = tileIndex;
	}
}
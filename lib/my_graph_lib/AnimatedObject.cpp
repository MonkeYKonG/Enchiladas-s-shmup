#include "AnimatedObject.hpp"
#include "MessagesException.hpp"

namespace	my
{
	AnimatedObject::AnimatedObject() noexcept
	{}

	void	AnimatedObject::Update()
	{}

	const sf::IntRect&	AnimatedObject::GetCurentTile() const noexcept
	{
		return (m_animations[m_animIndex][m_animTileIndex]);
	}

	const AnimatedObject::Animation&	AnimatedObject::GetCurentAnimation() const noexcept
	{
		return (m_animations[m_animIndex]);
	}

	const std::vector<AnimatedObject::Animation>&	AnimatedObject::GetAnimations() const noexcept
	{
		return (m_animations);
	}

	void	AnimatedObject::SetAnimations(const std::vector<AnimatedObject::Animation>& animations) noexcept
	{
		m_animations = animations;
	}

	void	AnimatedObject::SetAnimIndex(int index) throw (std::out_of_range)
	{
		if (index < 0 || index >= m_animations.size())
			throw (std::out_of_range(MessagesException::InvalidIndex("AnimatedObject::SetAnimIndex(int index)", "index", index)));
		m_animIndex = index;
	}

	void	AnimatedObject::SetAnimTileIndex(int tileIndex) throw (std::out_of_range)
	{
		m_animTileIndex = tileIndex;
	}
}
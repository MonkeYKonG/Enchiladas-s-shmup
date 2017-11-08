#include "AnimatedObject.hpp"
#include "MessagesException.hpp"

namespace	my
{
	AnimatedObject::AnimatedObject() noexcept
	{}

	void	AnimatedObject::UpdateAnimation()
	{}

	bool	AnimatedObject::IsOnAnimation() const noexcept
	{
		return (m_onAnimation);
	}

	const sf::IntRect&	AnimatedObject::GetCurentTile() const throw (std::out_of_range)
	{
		if (AnimInvalidIndex())
			throw (std::out_of_range(MessagesException::InvalidIndex("AnimatedObject::GetCurentTile()", "m_animIndex", m_animIndex)));
		if (InvalidIndexs(m_animTileIndex))
			throw (std::out_of_range(MessagesException::InvalidIndex("AnimatedObject::GetCurentTile()", "m_animTileIndex", m_animTileIndex)));
		return (m_animations[m_animIndex][m_animTileIndex]);
	}

	const AnimatedObject::Animation&	AnimatedObject::GetCurentAnimation() const throw (std::out_of_range)
	{
		if (AnimInvalidIndex())
			throw (std::out_of_range(MessagesException::InvalidIndex("AnimatedObject::GetCurentAnimation()", "m_animIndex", m_animIndex)));
		return (m_animations[m_animIndex]);
	}

	const std::vector<AnimatedObject::Animation>&	AnimatedObject::GetAnimations() const noexcept
	{
		return (m_animations);
	}

	void	AnimatedObject::SetOnAnimation(bool onAnimation) noexcept
	{
		m_onAnimation = onAnimation;
	}

	void	AnimatedObject::SetAnimations(const std::vector<AnimatedObject::Animation>& animations) noexcept
	{
		m_animations = animations;
	}

	void	AnimatedObject::SetAnimIndex(int index, int tileIndex) throw (std::out_of_range)
	{
		if (AnimInvalidIndex(index))
			throw (std::out_of_range(MessagesException::InvalidIndex("AnimatedObject::SetAnimIndex(int index, int tileIndex)", "index", index)));
		m_animIndex = index;
		try
		{
			SetAnimTileIndex(tileIndex);
		}
		catch (const std::out_of_range &e)
		{
			throw (e);
		}
	}

	void	AnimatedObject::SetAnimTileIndex(int tileIndex) throw (std::out_of_range)
	{
		if (InvalidIndexs(tileIndex))
			throw (std::out_of_range(MessagesException::InvalidIndex("AnimatedObject::SetAnimTileIndex(int tileIndex)", "tileIndex", tileIndex)));
		m_animTileIndex = tileIndex;
	}

	bool	AnimatedObject::AnimInvalidIndex(int animIndex) const noexcept
	{
		return (animIndex < 0 || animIndex >= m_animations.size());
	}

	bool	AnimatedObject::AnimInvalidIndex() const noexcept
	{
		return (AnimInvalidIndex(m_animIndex));
	}

	bool	AnimatedObject::InvalidIndexs(int tileIndex) const noexcept
	{
		return (AnimInvalidIndex() || tileIndex < 0 || tileIndex >= m_animations[m_animIndex].size());
	}
}
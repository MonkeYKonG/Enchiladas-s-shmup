#include "AnimatedObject.hpp"
#include "MessagesException.hpp"

namespace	my
{
	AnimatedObject::AnimatedObject() noexcept
		: m_onAnimation(false), m_animIndex(-1), m_animTileIndex(-1), m_curFramerate(0)
	{}

	void	AnimatedObject::UpdateAnimation() throw (std::out_of_range)
	{
		if (!m_onAnimation)
			return;
		if (InvalidIndexs(m_animIndex))
			throw (std::out_of_range("AnimatedObject: UpdateAnimation: indexs is out of range"));
		if (m_curFramerate++ >= m_animations[m_animIndex].framerateMax)
		{
			m_curFramerate = 0;
			if (++m_animTileIndex >= m_animations[m_animIndex].rects.size())
			{
				if (m_animations[m_animIndex].loop)
					m_animTileIndex = 0;
				else
					m_onAnimation = false;
			}
		}
	}

	bool	AnimatedObject::IsOnAnimation() const noexcept
	{
		return (m_onAnimation);
	}

	const sf::IntRect&	AnimatedObject::GetCurentRect() const throw (std::out_of_range)
	{
		if (AnimInvalidIndex())
			throw (std::out_of_range(MessagesException::InvalidIndex("AnimatedObject::GetCurentTile()", "m_animIndex", m_animIndex)));
		if (InvalidIndexs(m_animTileIndex))
			throw (std::out_of_range(MessagesException::InvalidIndex("AnimatedObject::GetCurentTile()", "m_animTileIndex", m_animTileIndex)));
		return (m_animations[m_animIndex].rects[m_animTileIndex]);
	}

	const AnimatedObject::Animation&	AnimatedObject::GetCurentAnimation() const throw (std::out_of_range)
	{
		if (AnimInvalidIndex())
			throw (std::out_of_range(MessagesException::InvalidIndex("AnimatedObject::GetCurentAnimation()", "m_animIndex", m_animIndex)));
		return (m_animations[m_animIndex]);
	}

	unsigned	AnimatedObject::GetCurFramerate() const noexcept
	{
		return (m_curFramerate);
	}

	const AnimatedObject::Animations&	AnimatedObject::GetAnimations() const noexcept
	{
		return (m_animations);
	}

	void	AnimatedObject::SetOnAnimation(bool onAnimation) noexcept
	{
		m_onAnimation = onAnimation;
	}

	void	AnimatedObject::SetAnimations(const AnimatedObject::Animations& animations) noexcept
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

	void	AnimatedObject::SetCurFrameRate(unsigned curFramerate) noexcept
	{
		m_curFramerate = curFramerate;
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
		return (AnimInvalidIndex() || tileIndex < 0 || tileIndex >= m_animations[m_animIndex].rects.size());
	}
}
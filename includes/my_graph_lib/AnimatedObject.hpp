#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <memory>

namespace	my
{
  class		AnimatedObject
  {
	public:
		struct Animation
		{
			typedef std::vector<sf::IntRect>	AnimationRects;

			Animation() : framerateMax(0), loop(false) {}

			AnimationRects rects;
			unsigned framerateMax;
			std::string key;
			bool loop;
		};

		typedef std::shared_ptr<AnimatedObject> AnimatedObjectPtr;
		typedef std::vector<Animation> Animations;

		AnimatedObject() noexcept;
		virtual ~AnimatedObject() noexcept {}

		bool                            IsOnAnimation() const noexcept;
		bool							AnimationExist(const std::string & key) const noexcept;
		const sf::IntRect&			    GetCurentRect() const throw (std::out_of_range);
		const Animation&                GetCurentAnimation() const throw (std::out_of_range);
		const Animations&				GetAnimations() const noexcept;
		unsigned						GetCurFramerate() const noexcept;

		void                            SetOnAnimation(bool onAnimation) noexcept;
		void			                SetAnimations(const Animations & animations) noexcept;
		void							AddAnimation(const Animation & animation) noexcept;
		void			                SetAnimIndex(int index, int tileIndex = 0) throw (std::out_of_range);
		void							SetAnimIndex(const std::string & key, int tileIndex = 0) throw (std::out_of_range);
		void			                SetAnimTileIndex(int tileIndex) throw (std::out_of_range);
		void							SetCurFrameRate(unsigned curFramerate) noexcept;

	protected:
		static const std::string	DEFAULT_ANIM_NAME;

		virtual void		    UpdateAnimation() throw (std::out_of_range);

		bool		m_onAnimation;
		Animations	m_animations;
		int			m_animIndex;
		int			m_animTileIndex;
		unsigned	m_curFramerate;

	private:
		bool AnimInvalidIndex(int animIndex) const noexcept;
		bool AnimInvalidIndex() const noexcept;
		bool InvalidIndexs(int tileIndex) const noexcept;
		bool InvalidIndexs() const noexcept;
	};
}

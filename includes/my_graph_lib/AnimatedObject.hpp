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
		typedef std::shared_ptr<AnimatedObject> AnimatedObjectPtr;
		typedef std::vector<sf::IntRect>	Animation;

		AnimatedObject() noexcept;
		virtual ~AnimatedObject() noexcept {}

		virtual void		    UpdateAnimation();

		bool                            IsOnAnimation() const noexcept;
		const sf::IntRect&			    GetCurentTile() const throw (std::out_of_range);
		const Animation&                GetCurentAnimation() const throw (std::out_of_range);
		const std::vector<Animation>&	GetAnimations() const noexcept;

		void                            SetOnAnimation(bool onAnimation) noexcept;
		void			                SetAnimations(const std::vector<Animation> & animations) noexcept;
		void			                SetAnimIndex(int index, int tileIndex = 0) throw (std::out_of_range);
		void			                SetAnimTileIndex(int tileIndex) throw (std::out_of_range);

	protected:
		bool			         m_onAnimation;
		std::vector<Animation>	 m_animations;
		int			          	 m_animIndex;
		int				         m_animTileIndex;

	private:
		bool AnimInvalidIndex(int animIndex) const noexcept;
		bool AnimInvalidIndex() const noexcept;
		bool InvalidIndexs(int tileIndex) const noexcept;
	};
}

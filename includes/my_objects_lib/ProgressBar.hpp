#pragma once

#include "my_graph_lib/SpriteObject.hpp"

namespace my
{
	class ProgressBar : public SpriteObject
	{
	public:
		typedef std::shared_ptr<ProgressBar> ProgressBarPtr;

		ProgressBar();
		virtual ~ProgressBar() {}

		unsigned GetCurValue() const noexcept;
		unsigned GetMaxValue() const noexcept;
		const sf::Sprite &GetBackgroundSprite() const noexcept;
		void SetCurValue(unsigned * curValue) noexcept;
		void SetMaxValue(unsigned * maxValue) noexcept;
		void SetValues(unsigned * curValue, unsigned * MaxValue) noexcept;
		void SetBackgroundTexture(const sf::Texture & texture) noexcept;
		void SetBackgroundSize(const sf::IntRect & rect) noexcept;

		virtual void Update() throw (std::exception);

	protected:
		void draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept;

		unsigned *m_curValue;
		unsigned *m_maxValue;
		sf::Sprite m_background;
	};
}
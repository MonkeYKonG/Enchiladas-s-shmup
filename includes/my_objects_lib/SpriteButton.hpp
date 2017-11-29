#pragma once

#include "my_graph_lib/SpriteObject.hpp"
#include "my_graph_lib/TextObject.hpp"

namespace my
{
	class SpriteButton : public SpriteObject
	{
	public:
		typedef std::shared_ptr<SpriteButton> SpriteButtonPtr;

		SpriteButton();
		virtual ~SpriteButton();

		virtual const sf::FloatRect GetHitBox() const noexcept;

		virtual void Update(const sf::Vector2f & mousePos) throw (std::out_of_range);
		bool IsMouseOvered() const noexcept;
		bool IsClicked() const noexcept;

		TextObject::TextObjectPtr GetText() const noexcept;
		void SetText(TextObject::TextObjectPtr newText) noexcept;

	protected:
		static const std::string	ON_CLICK_ANIM_NAME;
		static const std::string	ON_MOUSE_OVER_ANIM_NAME;

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept;

		virtual void Update() throw (std::out_of_range);
		virtual void UpdateMouse(const sf::Vector2f & mousePos);
		virtual void UpdateAnimation() throw (std::out_of_range);

		bool m_isMouseOvered;
		bool m_isClicked;
		TextObject::TextObjectPtr m_text;
	};
}
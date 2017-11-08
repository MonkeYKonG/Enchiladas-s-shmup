#pragma once

#include "my_graph_lib/SpriteObject.hpp"
#include "my_graph_lib/TextObject.hpp"
#include "my_graph_lib/AnimatedObject.hpp"

namespace my
{
	class Button : public Node, public AnimatedObject
	{
	public:
		typedef std::shared_ptr<Button> ButtonPtr;

		Button();
		~Button();

		virtual bool IsIntersect(const sf::Vector2f & point) const noexcept;
		virtual bool IsIntersect(const sf::FloatRect & square) const noexcept;

	private:
		void draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept;

		SpriteObject::SpriteObjectPtr m_sprite;
		TextObject::TextObjectPtr m_text;
		bool m_activate;
		bool m_isClicked;
	};
}
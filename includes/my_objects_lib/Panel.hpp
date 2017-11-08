#pragma once

#include "my_graph_lib/SpriteObject.hpp"
#include "my_graph_lib/TextObject.hpp"
#include "Border.hpp"

namespace	my
{
	class Panel : public Node
	{
	public:
		typedef std::shared_ptr<Panel> PanelPtr;

		Panel();
		~Panel();

		virtual bool IsIntersect(const sf::Vector2f & point) const noexcept;
		virtual bool IsIntersect(const sf::FloatRect & square) const noexcept;
		SpriteObject::SpriteObjectPtr GetBackground() const noexcept;
		Border::BorderPtr GetBorder() const noexcept;
		TextObject::TextObjectPtr GetTitle() const noexcept;
		void SetBackground(SpriteObject::SpriteObjectPtr background) noexcept;
		void SetBorder(Border::BorderPtr border) noexcept;
		void SetTitle(TextObject::TextObjectPtr title) noexcept;
		void Update(const sf::Vector2f & mousePos) noexcept;
	
	private:
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept;

		SpriteObject::SpriteObjectPtr m_background;
		Border::BorderPtr m_border;
		TextObject::TextObjectPtr m_title;
	};
}
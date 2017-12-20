#pragma once

#include "my_graph_lib/SpriteObject.hpp"
#include "my_graph_lib/TextObject.hpp"
#include "Border.hpp"
#include "SpriteButton.hpp"

namespace	my
{
	class Panel : public Node
	{
	public:
		typedef std::shared_ptr<Panel> PanelPtr;
		typedef SpriteButton::SpriteButtonPtr PanelSpriteButton;
		typedef TextObject::TextObjectPtr TextButton;
		typedef std::vector<PanelSpriteButton> SpriteButtons;
		typedef std::vector<TextButton> TextButtons;
		typedef std::vector<TextObject::TextObjectPtr> TextList;

		Panel();
		~Panel();

		virtual bool IsIntersect(const sf::Vector2f & point) const noexcept;
		virtual bool IsIntersect(const sf::FloatRect & square) const noexcept;
		virtual const sf::FloatRect GetHitBox() const noexcept;

		SpriteObject::SpriteObjectPtr GetBackground() const noexcept;
		Border::BorderPtr GetBorder() const noexcept;
		TextObject::TextObjectPtr GetTitle() const noexcept;
		const SpriteButtons &GetSpriteButtons() const noexcept;
		const TextButtons &GetTextButtons() const noexcept;
		const TextList &GetTexts() const noexcept;
		void SetBackground(SpriteObject::SpriteObjectPtr background) noexcept;
		void SetBorder(Border::BorderPtr border) noexcept;
		void SetTitle(TextObject::TextObjectPtr title) noexcept;
		void SetSpriteButtons(const SpriteButtons & buttons) noexcept;
		void AddSpriteButton(const PanelSpriteButton & newButton) noexcept;
		void SetTextButtons(const TextButtons & buttons) noexcept;
		void AddTextButton(const TextButton & newButton) noexcept;
		void SetTexts(const TextList & texts) noexcept;
		void AddText(const TextObject::TextObjectPtr & newText) noexcept;

		void Update(const sf::Vector2f & mousePos) noexcept;

	private:
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept;
		void UpdateBackground() noexcept;
		void UpdateBorder() noexcept;
		void UpdateTitle() noexcept;
		void UpdateButtons(const sf::Vector2f & mousePos) noexcept;
		void UpdateSpriteButtons(const sf::Vector2f & mousePos) noexcept;
		void UpdateTextButtons(const sf::Vector2f & mousePos) noexcept;

		SpriteObject::SpriteObjectPtr m_background;
		Border::BorderPtr m_border;
		TextObject::TextObjectPtr m_title;
		SpriteButtons	m_spriteButtons;
		TextButtons		m_textButtons;
		TextList		m_texts;
	};
}

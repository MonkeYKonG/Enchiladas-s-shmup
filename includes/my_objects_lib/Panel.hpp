#pragma once

#include "my_graph_lib/SpriteObject.hpp"
#include "my_graph_lib/TextObject.hpp"
#include "my_graph_lib/IUpdatableObject.hh"

namespace	my
{
	class Panel : public Node
	{
	public:
		typedef std::shared_ptr<Panel> PanelPtr;
		typedef std::list<IUpdatableObject::IUpdatableObjectPtr> UpdatableList;

		Panel();
		~Panel();

		virtual bool IsIntersect() const noexcept;
		SpriteObject::SpriteObjectPtr GetBackground() const noexcept;
		SpriteObject::SpriteObjectPtr GetBorder() const noexcept;
		TextObject::TextObjectPtr GetTitle() const noexcept;
		const UpdatableList & GetUpdatableObjects() const noexcept;
		void SetBackground(SpriteObject::SpriteObjectPtr background) noexcept;
		void SetBorder(SpriteObject::SpriteObjectPtr border) noexcept;
		void SetTitle(TextObject::TextObjectPtr title) noexcept;
		void SetUpdatableList(const UpdatableList & updatableList) noexcept;
		void Update(const sf::Vector2f & mousePos) noexcept;
	
	private:
		SpriteObject::SpriteObjectPtr m_background;
		SpriteObject::SpriteObjectPtr m_border;
		TextObject::TextObjectPtr m_title;
		UpdatableList m_updatableObjects;
	};
}
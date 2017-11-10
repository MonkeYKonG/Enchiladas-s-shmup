#pragma once

#include "my_graph_lib/SpriteObject.hpp"
#include "Direction.hpp"

namespace	my
{
	class Cursor : public SpriteObject
	{
	public:
		typedef std::shared_ptr<Cursor> CursorPtr;

		Cursor();
		virtual ~Cursor();

		void Update(const sf::Vector2f & mousePos) throw (std::out_of_range);
		
	private:
		static const std::string	LEFT_CLICK_ANIM_NAME;
		static const std::string	RIGHT_CLICK_ANIM_NAME;

		virtual void Update() throw (std::out_of_range);
	};
}
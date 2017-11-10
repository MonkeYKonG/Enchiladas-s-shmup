#pragma once

#include "my_graph_lib/SpriteObject.hpp"

namespace my
{
	class SpriteButton : public SpriteObject
	{
	public:
		typedef std::shared_ptr<SpriteButton> SpriteButtonPtr;

		SpriteButton();
		virtual ~SpriteButton();

		virtual void Update() throw (std::out_of_range);

	private:

	};
}
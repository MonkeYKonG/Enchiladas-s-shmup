#pragma once

#include "my_graph_lib/SpriteObject.hpp"

namespace my
{
	class Player : public SpriteObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Update() throw (std::out_of_range);

	private:

	};
}
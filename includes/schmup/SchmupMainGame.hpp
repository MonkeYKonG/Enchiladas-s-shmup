#pragma once

#include "my_menu_lib/SchmupScene.hpp"

namespace my
{
	namespace schmup
	{
		class SchmupMainGame : public SchmupScene
		{
		public:
			SchmupMainGame();

			virtual const SceneReturnValue Update(sf::RenderWindow & window) throw (std::exception);

		private:
			enum GAME_SATES
			{
				PLAY,
				CRAFTING
			};

			virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept;
			void drawCrafting(sf::RenderTarget & target, sf::RenderStates states) const noexcept;

			GAME_SATES m_gameState;
		};
	}
}
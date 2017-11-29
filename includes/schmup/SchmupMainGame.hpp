#pragma once

#include "my_menu_lib/SchmupScene.hpp"
#include "Ship.hpp"

namespace my
{
	namespace schmup
	{
		class SchmupMainGame : public SchmupScene
		{
		public:
			SchmupMainGame();

			virtual void Initialize(XMLNode::XMLNodePtr sceneRoot) throw (std::out_of_range, std::invalid_argument);
			virtual const SceneReturnValue Update(sf::RenderWindow & window) throw (std::exception);

		private:
			enum GAME_SATES
			{
				PLAY,
				CRAFTING
			};

			virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept;
			void drawCrafting(sf::RenderTarget & target, sf::RenderStates states) const noexcept;

			Ship m_ship;

			GAME_SATES m_gameState;
		};
	}
}
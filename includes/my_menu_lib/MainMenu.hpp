#pragma once

#include "my_graph_lib/Scene.hpp"
#include "my_graph_lib/SpriteObject.hpp"

namespace	my
{
	class MainMenu : public Scene
	{
	public:
		MainMenu();
		~MainMenu();

		const SceneReturnValue	Update(sf::RenderWindow & window) throw (std::exception);
		void Initialize() noexcept;
		void Reset() noexcept;

	private:
		void draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept;

		SpriteObject m_test;
	};
}
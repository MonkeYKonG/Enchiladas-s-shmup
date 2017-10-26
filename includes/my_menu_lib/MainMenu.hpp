#pragma once

#include "my_graph_lib/Scene.hpp"

namespace	my
{
	class MainMenu : public Scene
	{
	public:
		MainMenu();
		~MainMenu();

		const SceneReturnValue	& Update(const sf::RenderWindow & window) throw (std::exception);
		void Initialize() noexcept;
		void Reset() noexcept;

	private:
		void draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept;
	};
}
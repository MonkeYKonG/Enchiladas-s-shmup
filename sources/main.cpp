//============================================================================
// Name        : Enchiladas-s-schmup.cpp
// Author      : Alexis craye
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>
#include "my_graph_lib/XMLParser.hpp"
#include "my_graph_lib/GameManager.hpp"
#include "my_menu_lib/MainMenu.hpp"

int main(void) {
	my::GameManager gm;
	my::WindowBuffer::WindowBufferPtr windowPtr;

	try
	{
		windowPtr = my::WindowBuffer::WindowBufferPtr(new my::WindowBuffer());
		windowPtr->windowSize = sf::Vector2u(800, 600);
		windowPtr->bitsPerPixel = 64;
		windowPtr->window.create(sf::VideoMode(800, 600, 64), "my window");
		windowPtr->scenes.push_back(my::Scene::ScenePtr(new my::MainMenu()));
		windowPtr->curScene = 0;
		gm.AddWindow(windowPtr);
		gm.Loop();
	}
	catch (const std::exception & e)
	{
		std::cerr << "An error occured: " <<  e.what() << std::endl;
		return (1);
	}

	return (0);
}

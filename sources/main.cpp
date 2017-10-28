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
		gm.Loop();
	}
	catch (const std::exception & e)
	{
		std::cerr << "An error occured: " <<  e.what() << std::endl;
		return (1);
	}

	return (0);
}

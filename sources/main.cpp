//============================================================================
// Name        : Enchiladas-s-schmup.cpp
// Author      : Alexis craye
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>
#include "schmup/SchmupGameManager.hpp"

int main(void) {
	my::schmup::SchmupGameManager gm;

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

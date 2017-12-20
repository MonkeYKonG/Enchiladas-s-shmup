//============================================================================
// Name        : Enchiladas-s-schmup.cpp
// Author      : Alexis craye
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>
#include "schmup/SchmupGameManager.hpp"

#include "my_graph_lib/OperationEvaluator.hpp"

int main(void) {
	my::schmup::SchmupGameManager gm;

	srand(time(0));
	try
	{
		gm.Loop();
	}
	catch (const std::exception & e)
	{
		int a;
		std::cerr << "An error occured: " <<  e.what() << std::endl;
		std::cin >> a;
		return (1);
	}
	return (0);
}

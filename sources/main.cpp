//============================================================================
// Name        : Enchiladas-s-schmup.cpp
// Author      : Alexis craye
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>
#include "my_graph_lib/XMLParser.hpp"

int main(void) {
	my::XMLNode::XMLNodePtr node;

	try
	{
		node = my::XMLParser::Load("resources/test.xml");
		std::cout << node->ToString() << std::endl;
	}
	catch (const std::exception & e)
	{
		std::cerr << "An error occured: " <<  e.what() << std::endl;
		return (1);
	}

	return (0);
}

#include <fstream>
#include "XMLParser.hpp"

namespace	my
{
	XMLNode::XMLNodePtr	XMLParser::Load(const std::string &fileName) throw (std::invalid_argument)
	{
		std::ifstream fs(fileName);

		if (fs)
			;
	}
}
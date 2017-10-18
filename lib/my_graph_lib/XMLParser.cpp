#include <fstream>
#include "XMLParser.hpp"

namespace	my
{
	XMLNodePtr	XMLParser::Load(const std::string &fileName)
	{
		std::ifstream fs(fileName);

		if (fs)
			;
	}
}
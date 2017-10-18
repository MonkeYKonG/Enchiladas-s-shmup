#pragma once

#include "XMLNode.hpp"

namespace	my
{
	class 	XMLParser
	{
	public:
		static XMLNode::XMLNodePtr Load(const std::string & fileName) throw (std::invalid_argument);

	private:
		XMLParser();
		~XMLParser();
	};
}